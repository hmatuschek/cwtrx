#ifndef __TRX_H__
#define __TRX_H__

#include <avr/io.h>
#include <stdint.h>
#include "band.h"
#include "keyer.h"
#include "meter.h"
#include "rot.h"

#define TRX_TX_PORT PORTB
#define TRX_TX_DDR  DDRB
#define TRX_TX_BIT  PB6

#define TRX_KEY_PORT PORTB
#define TRX_KEY_DDR  DDRB
#define TRX_KEY_BIT  PB7

typedef enum {
  TRX_RX,
  TRX_TX,
  TRX_HOLD_TX,
  TRX_MENU
} TRXState;

typedef enum {
  TRX_USB = 0,
  TRX_LSB = 1
} TRXSideband;

typedef enum {
  TRX_STEP_10,
  TRX_STEP_25,
  TRX_STEP_50,
  TRX_STEP_100,
  TRX_STEP_250,
  TRX_STEP_500,
  TRX_STEP_1k,
  TRX_STEP_2_5k,
  TRX_STEP_5k,
  TRX_STEP_10k
} TRXStepSize;

/** VFO mode for the TRX. */
typedef enum {
  VFO_MODE_A,
  VFO_MODE_B,
  VFO_MODE_SPLIT
} VFOMode;

typedef enum {
  TRX_QS_NONE,
  TRX_QS_RIT,
  TRX_QS_STEP,
  TRX_QS_SPEED,
  TRX_QS_BAND
} TRXQuickSet;

#define TRX_RIT_MIN -100
#define TRX_RIT_MAX  100
#define TRX_CWTEXT_MAXLEN 64
#define TRX_GREET_MAXLEN  8

void trx_init();
void trx_factory_reset();
void trx_tx();
void trx_rx();
VFOMode  trx_vfo_mode();
void trx_set_vfo_mode(VFOMode mode);
TRXState trx_state();
void trx_set_state(TRXState state);

void trx_tune(int8_t delta);
uint32_t trx_dial_freq();

TRXQuickSet trx_quickset();
void trx_set_quickset(TRXQuickSet quickset);

int8_t trx_rit();
uint8_t trx_rit_sym();
void trx_set_rit(int8_t off);

void trx_set_vfo();

TRXStepSize trx_tune_step();
void trx_set_tune_step(TRXStepSize step);

Band trx_band();
void trx_set_band(Band band);

KeyerType trx_keyer_type();
void trx_keyer_set_type(KeyerType type);

KeyerIambicMode trx_keyer_iambic_mode();
void trx_keyer_set_iambic_mode(KeyerIambicMode mode);

uint8_t trx_keyer_paddle_reversed();
void trx_keyer_set_paddle_reversed(uint8_t reversed);

uint16_t trx_cw_tone();
void trx_set_cw_tone(uint16_t freq);

uint8_t trx_cw_level();
void trx_set_cw_level(uint8_t level);

uint8_t trx_cw_speed();
void trx_set_cw_speed(uint8_t idx);

uint8_t *trx_cwtext();
void trx_clear_cwtext();
void trx_update_cwtext();

void trx_set_meter_type(MeterType type);
MeterType trx_meter_type();

uint16_t trx_tx_hold();
void trx_set_tx_hold(uint16_t delay);

uint8_t trx_tx_enabled();
void trx_set_tx_enabled(uint8_t enabled);

uint8_t *trx_greet();
void trx_update_greet();

TRXSideband trx_sideband();
void trx_set_sideband(TRXSideband sideband);

EncoderType trx_rot_type();
void trx_set_rot_type(EncoderType type);

int32_t trx_pll_correction();
void trx_set_pll_correction(int32_t pptm);

void trx_poll();

#endif // __TRX_H__
