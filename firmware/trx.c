#include "trx.h"
#include "band.h"
#include "keyer.h"
#include "tone.h"
#include "rot.h"
#include "si5351.h"
#include "lcd.h"
#include "display.h"
#include "meter.h"
#include "menu.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <string.h>

// AVR comp for QtCreator
#ifndef ISR
#define ISR(x) void x()
#endif
#ifndef EEMEM
#define EEMEM
#endif

#define TRX_DEFAULT_CW_TONE        700
#define TRX_DEFAULT_CW_LEVEL       255
#define TRX_DEFAULT_CW_SPEED       10
#define TRX_DEFAULT_CW_MODE        KEYER_MODE_STRAIGHT
#define TRX_DEFAULT_METER_TYPE     METER_SIG
#define TRX_DEFAULT_TX_HOLD        50
#define TRX_DEFAULT_PLL_CORRECTION 0
#define TRX_DEFAULT_RIT            0
#define TRX_UPDATE_PERIOD          500
#define TRX_SAVE_PERIOD            10000UL

#define TRX_80_MIN   3500000UL
#define TRX_80_MAX   3800000UL
#define TRX_60_MIN   5351500UL
#define TRX_60_MAX   5366500UL
#define TRX_40_MIN   7000000UL
#define TRX_40_MAX   7200000UL
#define TRX_30_MIN  10100000UL
#define TRX_30_MAX  10150000UL
#define TRX_20_MIN  14000000UL
#define TRX_20_MAX  14350000UL
#define TRX_17_MIN  18068000UL
#define TRX_17_MAX  18168000UL
#define TRX_15_MIN  21000000UL
#define TRX_15_MAX  21450000UL
#define TRX_12_MIN  24890000UL
#define TRX_12_MAX  24990000UL
#define TRX_10_MIN  28000000UL
#define TRX_10_MAX  29690000UL

#define MINMAX(x, a, b) ( (x<a) ? a : ((x>b) ? b : x))

/** Contains the VFO settings. That is band, current dial frequency for each band and the selected
 * sideband. */
typedef struct {
  Band      band;
  uint32_t  band_freq[7];
} VFOSettings;

/** Holds the entire settings for the TRX in memory. */
typedef struct {
  /** Holds the current VFO mode, that is A, B and A/B split. */
  VFOMode     vfo_mode;
  /** Settings for the VFO A. */
  VFOSettings vfo_a;
  /** Settings for the VFO B. */
  VFOSettings vfo_b;
  /** Tuing stepsize. */
  TRXStepSize step;
  /** RIT */
  int8_t      rit;
  /** If true, TX is enabled. */
  uint8_t     tx_enabled;
  /** The frequency of the CW sidetone. */
  uint16_t    cw_tone;
  /** CW tone level. */
  uint8_t     cw_level;
  /** Speed in WPM of the CW keyer. */
  uint8_t     cw_speed;
  /** Mode of the CW keyer (straight or paddle). */
  KeyerMode   cw_mode;
  MeterType   meter_type;
  /** TX hold delay in ms. */
  uint16_t    tx_hold;
  /** PLL reference frequeny correction in 0.1ppm. */
  int32_t     pll_correction;
  uint8_t     cwtext[TRX_CWTEXT_MAXLEN];
  uint8_t     greet[8];
} TRXSettings;


TRXSettings _ee_trx EEMEM = {
  VFO_MODE_A,
  { BAND_80,
    {TRX_80_MIN, TRX_60_MIN, TRX_40_MIN, TRX_30_MIN, TRX_20_MIN, TRX_17_MIN, TRX_15_MIN} },
  { BAND_80,
    {TRX_80_MIN, TRX_60_MIN, TRX_40_MIN, TRX_30_MIN, TRX_20_MIN, TRX_17_MIN, TRX_15_MIN} },
  TRX_STEP_50,
  TRX_DEFAULT_RIT,
  1,
  TRX_DEFAULT_CW_TONE,
  TRX_DEFAULT_CW_LEVEL,
  TRX_DEFAULT_CW_SPEED,
  TRX_DEFAULT_CW_MODE,
  TRX_DEFAULT_METER_TYPE,
  TRX_DEFAULT_TX_HOLD,
  TRX_DEFAULT_PLL_CORRECTION,
  {},
  {' ','D','M','3','M','A','T',' '}
};

TRXSettings _trx;

volatile TRXState _state;
TRXState _display_state;

uint16_t _tx_hold_count;
uint16_t _trx_tick_count;
uint16_t _trx_save_count;
volatile uint8_t _trx_update_vfo;
volatile uint8_t _trx_tuned;
volatile uint8_t _trx_save_freq;


void trx_init() {
  // Config tx pin & clear output (RX)
  TRX_TX_DDR |= (1 << TRX_TX_BIT);
  TRX_TX_PORT &= ~(1 << TRX_TX_BIT);
  // Config key pin & clear output
  TRX_KEY_DDR |= (1 << TRX_KEY_BIT);
  TRX_KEY_PORT &= ~(1 << TRX_KEY_BIT);

  lcd_init();
  rot_init();

  // Load settings from eeprom
  eeprom_read_block(&_trx, &_ee_trx, sizeof(TRXSettings));

  meter_init(_trx.meter_type);

  lcd_clear();
  lcd_home();
  lcd_string(" CW TRX");
  lcd_setcursor(0,2);
  for (uint8_t i=0; i<8; i++)
    lcd_data(_trx.greet[i]);

  keyer_init(_trx.cw_mode, _trx.cw_speed);
  _delay_ms(100);
  if (0x02 == keyer_read_paddle())
    trx_set_cw_mode(KEYER_MODE_STRAIGHT);

  tone_init();
  tone_set_frequency(_trx.cw_tone);
  tone_set_volume(_trx.cw_level);
  si5351_init();

  _display_state = _state = TRX_RX;
  _tx_hold_count = 0;

  // Set Timer on Compare Match (CTC) mode, clock source CLK/32
  TCCR2A = (1 << WGM21) | (0 << WGM20) | (0 << COM2A1) | (0 << COM2A0) |
      (0 << COM2B1) | (0 << COM2B0);
  TCCR2B = (0 << WGM22) | (0 << CS22) | (1 << CS21) | (1 << CS20) |
      (0 << FOC2A) | (0<<FOC2B);
  // -> 1ms
  OCR2A  = 250-1;
  // enable interrupt (OC 0A)
  TIMSK2  |= (1<<OCIE2A);
  _trx_tick_count = 0;

  si5351_drive_strength(SI5351_CLK0, SI5351_DRIVE_2MA);
  si5351_clock_enable(SI5351_CLK0, 0);
  si5351_drive_strength(SI5351_CLK1, SI5351_DRIVE_2MA);
  si5351_clock_enable(SI5351_CLK1, 0);
  si5351_drive_strength(SI5351_CLK2, SI5351_DRIVE_2MA);
  si5351_clock_enable(SI5351_CLK2, 0);

  band_init();

  // Set current band and set VFO/BFO
  if ((VFO_MODE_A == _trx.vfo_mode) || (VFO_MODE_SPLIT == _trx.vfo_mode))
    band_set(_trx.vfo_a.band);
  else
    band_set(_trx.vfo_b.band);
  trx_set_vfo();
  _trx_update_vfo = 0;
  _trx_tuned = 0;
  _trx_save_freq = 0;

  _delay_ms(2000);

  display_update();

  // Power reduction, disable Timer 0, UART 0, SPI
  //PRR |= ( (1 << PRTIM0) | (1 << PRUSART0) | (1 << PRSPI));
}


uint32_t trx_dial_freq() {
  if ((VFO_MODE_A == _trx.vfo_mode) || ((TRX_RX == _state) && (VFO_MODE_SPLIT == _trx.vfo_mode))) {
    return _trx.vfo_a.band_freq[_trx.vfo_a.band];
  }
  return _trx.vfo_b.band_freq[_trx.vfo_b.band];
}

uint8_t trx_rit_sym() {
  if (_trx.rit==0)
    return 'R';
  else if (_trx.rit>0)
    return '+';
  return '-';
}

int8_t trx_rit() {
  return _trx.rit;
}

void trx_set_rit(int8_t off) {
  _trx.rit = MINMAX(off, TRX_RIT_MIN, TRX_RIT_MAX);
  trx_set_vfo();
  cli();
  eeprom_write_block(&(_trx.rit), &(_ee_trx.rit), sizeof(int8_t));
  sei();
}

TRXState trx_state() {
  return _state;
}

void trx_set_state(TRXState state) {
  _state = state;
}

void trx_tx() {
  if (_trx.tx_enabled && ((TRX_RX == _state) || (TRX_HOLD_TX == _state)) ) {
    _state = TRX_TX;
    // Check if band needs to be changed -> change band
    if ( (VFO_MODE_SPLIT == trx_vfo_mode()) && (_trx.vfo_a.band != _trx.vfo_b.band))
      band_set(_trx.vfo_b.band);
    // update VFO frequencies
    _trx_update_vfo = 1;
    // Enable tx
    TRX_TX_PORT |= (1 << TRX_TX_BIT);
    TRX_KEY_PORT |= (1 << TRX_KEY_BIT);
    tone_on();
  } else if ((TRX_RX == _state) || (TRX_HOLD_TX == _state)) {
    // Just simulate TX, that is switch to TX state and send side-tone if mode is CW
    // but do not actually update VFO and do not switch hardware into TX.
    _state = TRX_TX;
    tone_on();
  }
}

void trx_rx() {
  // turn side tone off anyway
  tone_off();
  // Disable key pin
  TRX_KEY_PORT &= ~(1 << TRX_KEY_BIT);
  // if state is TX -> swtich to HOLD_TX and reset hold counter
  if (TRX_TX == _state) {
    _tx_hold_count = 0;
    _state = TRX_HOLD_TX;
  }
}


inline void trx_save_settings() {
  cli();
  eeprom_write_block(&_trx, &_ee_trx, sizeof(TRXSettings));
  sei();
}


void trx_set_vfo() {
  // Get VFO A settings:
  Band band = _trx.vfo_a.band;
  uint32_t dialf = _trx.vfo_a.band_freq[band];

  // If VFO B is active -> update
  if ((VFO_MODE_B == _trx.vfo_mode) || ((TRX_TX == _state) && (VFO_MODE_SPLIT == _trx.vfo_mode))) {
    band     = _trx.vfo_b.band;
    dialf    = _trx.vfo_b.band_freq[band];
  }

  uint32_t vfo = 4*(dialf-((int16_t)_trx.cw_tone)+10*((int16_t)_trx.rit));
  if ((TRX_TX == _state)) {
    //si5351_set_freq(0,     SI5351_PLL_FIXED, SI5351_CLK1);
    si5351_set_freq(dialf, SI5351_PLL_FIXED, SI5351_CLK0);
    si5351_clock_enable(SI5351_CLK2, 0);
    si5351_clock_enable(SI5351_CLK0, 1);
  } else {
    si5351_set_freq(vfo, SI5351_PLL_FIXED, SI5351_CLK2);
    //si5351_set_freq(0,   SI5351_PLL_FIXED, SI5351_CLK2);
    si5351_clock_enable(SI5351_CLK2, 1);
    si5351_clock_enable(SI5351_CLK0, 0);
  }
}

VFOMode trx_vfo_mode() {
  return _trx.vfo_mode;
}

void trx_set_vfo_mode(VFOMode mode) {
  _trx.vfo_mode = mode;
  if ( (VFO_MODE_A == _trx.vfo_mode) || ((TRX_RX == _state) && (VFO_MODE_SPLIT == _trx.vfo_mode)) )
    band_set(_trx.vfo_a.band);
  else
    band_set(_trx.vfo_b.band);
  trx_set_vfo();
}


void trx_tune(int8_t delta) {
  // Get VFO A settings:
  Band band = _trx.vfo_a.band;
  uint32_t dialf = _trx.vfo_a.band_freq[band];

  // If VFO B is active -> update
  if ((VFO_MODE_B == _trx.vfo_mode) || ((TRX_TX == _state) && (VFO_MODE_SPLIT == _trx.vfo_mode))) {
    band     = _trx.vfo_b.band;
    dialf    = _trx.vfo_b.band_freq[band];
  }

  // Update dial frequency
  switch(_trx.step) {
    case TRX_STEP_10:   dialf += 10UL*((int32_t)delta); break;
    case TRX_STEP_25:   dialf += 25UL*((int32_t)delta); break;
    case TRX_STEP_50:   dialf += 50UL*((int32_t)delta); break;
    case TRX_STEP_100:  dialf += 100UL*((int32_t)delta); break;
    case TRX_STEP_250:  dialf += 250UL*((int32_t)delta); break;
    case TRX_STEP_500:  dialf += 500UL*((int32_t)delta); break;
    case TRX_STEP_1k:   dialf += 1000UL*((int32_t)delta); break;
    case TRX_STEP_2_5k: dialf += 2500UL*((int32_t)delta); break;
    case TRX_STEP_5k:   dialf += 5000UL*((int32_t)delta); break;
    case TRX_STEP_10k:  dialf += 10000UL*((int32_t)delta); break;
  }

  // Check for limits
  switch (band) {
    case BAND_80:  dialf = MINMAX(dialf, TRX_80_MIN, TRX_80_MAX); break;
    case BAND_60:  dialf = MINMAX(dialf, TRX_60_MIN, TRX_60_MAX); break;
    case BAND_40:  dialf = MINMAX(dialf, TRX_40_MIN, TRX_40_MAX); break;
    case BAND_30:  dialf = MINMAX(dialf, TRX_30_MIN, TRX_30_MAX); break;
    case BAND_20:  dialf = MINMAX(dialf, TRX_20_MIN, TRX_20_MAX); break;
    case BAND_17:  dialf = MINMAX(dialf, TRX_17_MIN, TRX_17_MAX); break;
    case BAND_15:  dialf = MINMAX(dialf, TRX_15_MIN, TRX_15_MAX); break;
    case BAND_12:  dialf = MINMAX(dialf, TRX_12_MIN, TRX_12_MAX); break;
    case BAND_10:  dialf = MINMAX(dialf, TRX_10_MIN, TRX_10_MAX); break;
  }

  // Store dial frequency in current TRX Object
  if ((VFO_MODE_A == _trx.vfo_mode) || ((TRX_RX == _state) && (VFO_MODE_SPLIT == _trx.vfo_mode))) {
    _trx.vfo_a.band_freq[band] = dialf;
  } else {
    _trx.vfo_b.band_freq[band] = dialf;
  }

  // Tune
  trx_set_vfo();
  _trx_tuned = 1;
}

TRXStepSize trx_tune_step() {
  return _trx.step;
}

void trx_set_tune_step(TRXStepSize step) {
  _trx.step = step;
  cli();
  eeprom_write_block(&(_trx.step), &(_ee_trx.step), sizeof(TRXStepSize));
  sei();
}

Band trx_band() {
  if ((VFO_MODE_A == _trx.vfo_mode) || ((TRX_RX == _state) && (VFO_MODE_SPLIT == _trx.vfo_mode))) {
    return _trx.vfo_a.band;
  }
  return _trx.vfo_b.band;
}

void trx_set_band(Band band) {
  // Select band and store in EEPROM
  cli();
  if ((VFO_MODE_A == _trx.vfo_mode) || ((TRX_RX == _state) && (VFO_MODE_SPLIT == _trx.vfo_mode))) {
    _trx.vfo_a.band = band;
    eeprom_write_block(&(_trx.vfo_a.band), &(_ee_trx.vfo_a.band), sizeof(Band));
  } else {
    _trx.vfo_b.band = band;
    eeprom_write_block(&(_trx.vfo_b.band), &(_ee_trx.vfo_b.band), sizeof(Band));
  }
  sei();
  // Set band
  band_set(band);
  // Update VFO freq
  trx_set_vfo();
}

uint16_t trx_tx_hold() {
  return _trx.tx_hold;
}

void trx_set_tx_hold(uint16_t delay) {
  if (delay > 1000)
    delay=1000;
  _trx.tx_hold = delay;
  cli();
  eeprom_write_block(&(_trx.tx_hold), &(_ee_trx.tx_hold), sizeof(uint16_t));
  sei();
}

uint8_t trx_tx_enabled() {
  return _trx.tx_enabled;
}

void trx_set_tx_enabled(uint8_t enable) {
  _trx.tx_enabled = enable;
  cli();
  eeprom_write_block(&(_trx.tx_enabled), &(_ee_trx.tx_enabled), sizeof(uint8_t));
  sei();
}

KeyerMode trx_cw_mode() {
  return _trx.cw_mode;
}

void trx_set_cw_mode(KeyerMode mode) {
  _trx.cw_mode = mode;
  keyer_set_mode(_trx.cw_mode);
  cli();
  eeprom_write_block(&(_trx.cw_mode), &(_ee_trx.cw_mode), sizeof(KeyerMode));
  sei();
}

uint16_t trx_cw_tone() {
  return _trx.cw_tone;
}

void trx_set_cw_tone(uint16_t freq) {
  if (freq > 1000) freq = 1000;
  _trx.cw_tone = freq;
  tone_set_frequency(_trx.cw_tone);
  // Update VFO frequency from dial, BFO and CW tone frequency
  trx_set_vfo();
  // Store CW tone freq in EEPROM
  cli();
  eeprom_write_block(&(_trx.cw_tone), &(_ee_trx.cw_tone), sizeof(uint16_t));
  sei();
}

uint8_t trx_cw_level() {
  return _trx.cw_level;
}

void trx_set_cw_level(uint8_t level) {
  if (level > 255) level = 255;
  _trx.cw_level = level;
  tone_set_volume(_trx.cw_level);
  // Store CW level in EEPROM
  cli();
  eeprom_write_block(&(_trx.cw_level), &(_ee_trx.cw_level), sizeof(uint8_t));
  sei();
}

uint8_t trx_cw_speed() {
  return _trx.cw_speed;
}

void trx_set_cw_speed(uint8_t idx) {
  _trx.cw_speed = (idx>=KEYER_NUM_SPEED) ? (KEYER_NUM_SPEED-1) : idx;
  keyer_set_speed_idx(_trx.cw_speed);
  cli();
  eeprom_write_block(&(_trx.cw_speed), &(_ee_trx.cw_speed), sizeof(uint8_t));
  sei();
}

uint8_t *trx_cwtext() {
  return _trx.cwtext;
}

void trx_clear_cwtext() {
  memset(_trx.cwtext, 0, TRX_CWTEXT_MAXLEN);
}

void trx_update_cwtext() {
  cli();
  eeprom_write_block(&(_trx.cwtext), &(_ee_trx.cwtext), TRX_CWTEXT_MAXLEN);
  sei();
}

uint8_t *trx_greet() {
  return _trx.greet;
}

void trx_update_greet() {
  cli();
  eeprom_write_block(&(_trx.greet), &(_ee_trx.greet), TRX_GREET_MAXLEN);
  sei();
}

int32_t trx_pll_correction() {
  return _trx.pll_correction;
}

MeterType trx_meter_type() {
  return _trx.meter_type;
}

void trx_set_meter_type(MeterType type) {
  _trx.meter_type = type;
  meter_set_type(type);
  cli();
  eeprom_write_block(&(_trx.meter_type), &(_ee_trx.meter_type), sizeof(MeterType));
  sei();
}

void trx_set_pll_correction(int32_t val) {
  if (val > 1000000L)
    val = 1000000L;
  if (val < -1000000L)
    val = -1000000L;
  _trx.pll_correction = val;
  cli();
  si5351_set_correction(val);
  trx_set_vfo();
  eeprom_write_block(&(_trx.pll_correction), &_ee_trx.pll_correction, sizeof(int32_t));
  sei();
}

void trx_save_frequency() {
  if (_trx_save_freq) {
    // Store dial frequency in EEPROM
    cli();
    eeprom_write_block(&(_trx.vfo_a.band_freq[_trx.vfo_a.band]),
        &(_ee_trx.vfo_a.band_freq[_trx.vfo_a.band]), sizeof(uint32_t));
    eeprom_write_block(&(_trx.vfo_b.band_freq[_trx.vfo_b.band]),
        &(_ee_trx.vfo_b.band_freq[_trx.vfo_b.band]), sizeof(uint32_t));
    sei();
    _trx_save_freq = 0;
  }
}

void trx_poll()
{
  // First things first, update VFO if needed.
  if (_trx_update_vfo) {
    trx_set_vfo();
    _trx_update_vfo = 0;
  }

  keyer_poll();

  // Get rotary encoder and center button state
  int8_t delta = rot_delta();
  RotButton button = rot_button();

  // If TRX state has changed -> update display
  if ((TRX_MENU != _state) && (_display_state != _state)) {
    _display_state = _state;
    display_trx_state();
  }

  // quick exit
  if ((0 == delta) && (ROT_BUTTON_NONE == button) && (TRX_RX==_state)) {
    meter_poll();
    return;
  }

  if (TRX_RX == _state) {
    if (ROT_BUTTON_CLICK == button) {
      // Save frequency if needed
      trx_save_frequency();
      _state = TRX_MENU;
      display_update();
    } else if (ROT_BUTTON_LONG == button) {
      uint8_t len = TRX_CWTEXT_MAXLEN;
      for (; (len>0) && (0==_trx.cwtext[len-1]); --len);
      keyer_send_text(_trx.cwtext, len);
    } else if (delta) {
      trx_tune(delta);
      display_frequency();
    } else if (_trx_save_freq) {
      trx_save_frequency();
    }
  } else if (TRX_MENU == _state) {
    menu_update(button, delta);
  }
}


ISR(TIMER2_COMPA_vect) {
  keyer_tick();
  rot_tick();

  if (TRX_HOLD_TX == _state) {
    _tx_hold_count++;
    // After TX hold delay -> actually switch to RX mode
    if (_trx.tx_hold <= _tx_hold_count) {
      // Disable tx
      TRX_TX_PORT &= ~(1 << TRX_TX_BIT);
      // check if band need to be changed
      if ( (VFO_MODE_SPLIT == _trx.vfo_mode) && (_trx.vfo_a.band != _trx.vfo_b.band) )
        band_set(_trx.vfo_a.band);
      // Go to RX state
      _state = TRX_RX;
      // update VFO frequencies
      _trx_update_vfo = 1;
      // reset hold count
      _tx_hold_count=0;
    }
  }

  _trx_tick_count++;
  if (TRX_UPDATE_PERIOD <= _trx_tick_count) {
    _trx_tick_count = 0;
    meter_update();
  }

  _trx_save_count++;
  if ((TRX_SAVE_PERIOD <= _trx_save_count)) {
    _trx_save_count = 0;
    if (_trx_tuned && (TRX_RX == _state)) {
      _trx_save_freq = 1;
      _trx_tuned = 0;
    }
  }
}


