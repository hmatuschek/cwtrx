#include "keyer.h"
#include "trx.h"
#include "button.h"
#include <avr/pgmspace.h>

/// Keep the delay short
#define MAX_DELAY (F_CPU/1000UL)
/// Helper macro to return the maximum of two values
#define max(a,b) (a<b ? b : a)

// LUT of 25 dit-lengths values (in 0.5ms),
// (approx) linear in WPM, from 10 to 34 WPM.
static const uint16_t dit_len_lut[] = {
  120, 109, 100,  92,  86,
   80,  75,  70,  67,  63,
   60,  57,  54,  52,  50,
   48,  46,  44,  43,  41,
   40,  39,  38,  37,  36 };

const uint32_t codetable[KEYER_NUM_SYMBOLS] PROGMEM = {
  ( 4UL<<24 |                   0b0UL), // SP
  ( 8UL<<24 |               0b11101UL), // A
  (12UL<<24 |           0b101010111UL), // B
  (14UL<<24 |         0b10111010111UL), // C
  (10UL<<24 |             0b1010111UL), // D
  ( 4UL<<24 |                   0b1UL), // E
  (12UL<<24 |           0b101110101UL), // F
  (12UL<<24 |           0b101110111UL), // G
  (10UL<<24 |             0b1010101UL), // H
  ( 6UL<<24 |                 0b101UL), // I
  (16UL<<24 |       0b1110111011101UL), // J
  (12UL<<24 |           0b111010111UL), // K
  (12UL<<24 |           0b101011101UL), // L
  (10UL<<24 |             0b1110111UL), // M
  ( 8UL<<24 |               0b10111UL), // N
  (14UL<<24 |         0b11101110111UL), // O
  (14UL<<24 |         0b10111011101UL), // P
  (16UL<<24 |       0b1110101110111UL), // Q
  (10UL<<24 |             0b1011101UL), // R
  ( 8UL<<24 |               0b10101UL), // S
  ( 6UL<<24 |                 0b111UL), // T
  (10UL<<24 |             0b1110101UL), // U
  (12UL<<24 |           0b111010101UL), // V
  (12UL<<24 |           0b111011101UL), // W
  (14UL<<24 |         0b11101010111UL), // X
  (16UL<<24 |       0b1110111010111UL), // Y
  (16UL<<24 |         0b10111010111UL), // Z
  (22UL<<24 | 0b1110111011101110111UL), // 0
  (20UL<<24 |   0b11101110111011101UL), // 1
  (18UL<<24 |     0b111011101110101UL), // 2
  (16UL<<24 |       0b1110111010101UL), // 3
  (14UL<<24 |         0b11101010101UL), // 4
  (12UL<<24 |           0b101010101UL), // 5
  (14UL<<24 |         0b10101010111UL), // 6
  (16UL<<24 |       0b1010101110111UL), // 7
  (18UL<<24 |     0b101011101110111UL), // 8
  (20UL<<24 |   0b10111011101110111UL), // 9
  (16UL<<24 |       0b1011101010111UL), // /
  (20UL<<24 |   0b11101011101011101UL), // .
};

const uint8_t symbol_table[KEYER_NUM_SYMBOLS] PROGMEM = {
  ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
  'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '/',
  '.' };


#define MIN_WPM    10
#define MAX_WPM    34

static uint8_t ditlen_idx = 10;

// The current dit length in ms.
#define DEFAULT_DIT_LEN 60
volatile uint16_t dit_len = DEFAULT_DIT_LEN;
// Precomputed multiples of ditlen
volatile uint16_t dit_2len = 2*DEFAULT_DIT_LEN;
volatile uint16_t dit_3len = 3*DEFAULT_DIT_LEN;
volatile uint16_t dit_4len = 4*DEFAULT_DIT_LEN;

/// The current state.
volatile KeyerState _keyer_state = KEYER_IDLE;
/// The last state.
volatile KeyerState _keyer_last_state = KEYER_IDLE;
/// The current mode
volatile KeyerMode _keyer_mode = KEYER_MODE_PADDLE;

volatile uint8_t   _text_len        = 0;
const    uint8_t   *_text           = 0;
volatile uint8_t   _current_sym_len = 0;
volatile uint32_t  _current_sym     = 0;

uint8_t
keyer_speed_wpm() {
  return ditlen_idx+10;
}

void
keyer_set_speed_idx(uint8_t idx) {
  if (idx >= KEYER_NUM_SPEED)
    idx = KEYER_NUM_SPEED-1;
  ditlen_idx = idx;

  // Update dit-lengths
  dit_len = dit_len_lut[ditlen_idx];
  dit_2len = 2*dit_len;
  dit_3len = 3*dit_len;
  dit_4len = 4*dit_len;
}


/// Initializes the keyer and PTT interface and timer
void
keyer_init(KeyerMode mode, uint8_t speed) {
  // config keyer inputs
  KEYER_A_DDR &= ~(1 << KEYER_A_BIT);
  KEYER_B_DDR &= ~(1 << KEYER_B_BIT);
  // enable pullups on inputs
  KEYER_A_PORT |= (1 << KEYER_A_BIT);
  KEYER_B_PORT |= (1 << KEYER_B_BIT);

  // set default values
  _keyer_state = KEYER_IDLE;
  _keyer_last_state = KEYER_IDLE;
  keyer_set_mode(mode);
  keyer_set_speed_idx(speed);
}

/// Read paddles, returns 0b00 if no paddle is touched,
/// 0b01 if only the left is touched, 0b10 if only the right is
/// touched and 0b11 if both are touched.
uint8_t
keyer_read_paddle() {
  return ( (((~KEYER_A_PIN) & (1<<KEYER_A_BIT)) ? 0x01 : 0x00) |
           (((~KEYER_B_PIN) & (1<<KEYER_B_BIT)) ? 0x02 : 0x00) );
}

void
keyer_set_mode(KeyerMode mode) {
  _keyer_mode = mode;
}

uint8_t keyer_sym2char(uint8_t sym) {
  if (sym >= KEYER_NUM_SYMBOLS)
    return 0;
  return pgm_read_byte(&(symbol_table[sym]));
}

void keyer_send_text(const uint8_t *text, uint8_t len) {
  if (0 == len)
    return;
  if (KEYER_IDLE == _keyer_state) {
    _current_sym_len = 0;
    _text = text;
    _text_len = len;
    _keyer_last_state = _keyer_state;
    _keyer_state = KEYER_SEND_TEXT;
  }
}

void
keyer_poll() {
  // If keyer sends a text
  if (KEYER_SEND_TEXT == _keyer_state) {
    // and the key is pressed:
    //  -> stop sending
    if (((_keyer_mode == KEYER_MODE_PADDLE) && keyer_read_paddle()) ||
        ((_keyer_mode == KEYER_MODE_STRAIGHT) && (0x01 & keyer_read_paddle())))
    {
      _keyer_last_state = KEYER_IDLE;
      _keyer_state = KEYER_IDLE;
    }
    // otherwise continue sending text...
    return;
  }

  // If waiting for the next symbol...
  if ((_keyer_mode == KEYER_MODE_PADDLE) && (KEYER_IDLE == _keyer_state)) {
    // ... dispatch by paddle state
    // (left -> dit, right -> dah, both -> alternate dit & dah)
    switch (keyer_read_paddle()) {
      // On right paddle
      case 0x01:
        _keyer_last_state = _keyer_state;
        _keyer_state = KEYER_SEND_DIT;
        break;

      // On left paddle
      case 0x02:
        _keyer_last_state = _keyer_state;
        _keyer_state = KEYER_SEND_DAH;
        break;

      // On both paddles alternate dit & dah
      case 0x03:
        if (KEYER_SEND_DIT == _keyer_last_state) {
          // If last state was a dit -> send dah
          _keyer_last_state = _keyer_state;
          _keyer_state = KEYER_SEND_DAH;
        } else {
          // If last state was a dah -> send dit
          _keyer_last_state = _keyer_state;
          _keyer_state = KEYER_SEND_DIT;
        }
        break;

      // Otherwise stay in idle
      default:
        break;
    }
  } else if (_keyer_mode == KEYER_MODE_STRAIGHT) {
    if (0x01 & keyer_read_paddle()) {
      _keyer_last_state = _keyer_state;
      _keyer_state = KEYER_SEND;
    } else {
      _keyer_last_state = _keyer_state;
      _keyer_state = KEYER_IDLE;
    }
  }
}


void
keyer_tick()
{
  static uint16_t count = 0;

  if (KEYER_IDLE == _keyer_state) {
    // Stop sending...
    trx_rx(); count = 0;
  } else if (KEYER_SEND_DIT == _keyer_state) {
    // Send a dit (10, with additional pause)
    if (0 == count) {
      trx_tx(); count++;
    } else if (dit_len == count) {
      trx_rx(); count++;
    } else if (dit_2len == count) {
      _keyer_last_state = _keyer_state;
      _keyer_state = KEYER_IDLE;
      count = 0;
    } else {
      count++;
    }
  } else if (KEYER_SEND_DAH == _keyer_state) {
    // Send a dah (1110, with additional pause)
    if (0 == count) {
      trx_tx(); count++;
    } else if (dit_3len == count) {
      trx_rx(); count++;
    } else if (dit_4len == count) {
      _keyer_last_state = _keyer_state;
      _keyer_state = KEYER_IDLE;
      count = 0;
    } else {
      count++;
    }
  } else if (KEYER_SEND == _keyer_state) {
    trx_tx();
  } else if (KEYER_SEND_TEXT == _keyer_state) {
    if (dit_len == count) {
      // If a dit-length has passed and ...
      // ... there is no symbol nor further text to send ...
      if ((0 == _text_len) && (0 == _current_sym_len)) {
        // Set keyer to idle
        _keyer_state = _keyer_last_state = KEYER_IDLE;
        // Reset count
        count = 0;
        // reset TRX to RX
        trx_rx();
      } else {
        // ... If there is further text but no current symbol to send...
        if (0 == _current_sym_len) {
          // Get next char from text and translate to symbol
          _current_sym = pgm_read_dword(&(codetable[*_text]));
          // decode symbol length
          _current_sym_len = (_current_sym>>24);
          // Update text length and pointer
          _text_len--; _text++;
        }

        // Send first/next dit or dah of current symbol
        if (_current_sym & 0x01)
          trx_tx();
        else
          trx_rx();
        _current_sym_len--;
        _current_sym = (_current_sym>>1);
        count = 0;
      }
    } else {
      // Otherwise increament counter...
      count++;
    }
  }
}
