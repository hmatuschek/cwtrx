#include "keyer.h"
#include "trx.h"
#include "button.h"

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


void
keyer_poll() {
  // If waiting for the next symbol...
  if ((_keyer_mode == KEYER_MODE_PADDLE) && (KEYER_IDLE == _keyer_state)) {
    // ... dispatch by paddle state
    // (left -> dit, right -> dah, both -> alternate dit & dah)
    switch (keyer_read_paddle()) {
      // On right paddle
      case 0x01:
        _keyer_last_state = _keyer_state;
        _keyer_state = KEYER_SEND_DAH;
        break;

      // On left paddle
      case 0x02:
        _keyer_last_state = _keyer_state;
        _keyer_state = KEYER_SEND_DIT;
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
    if (0x02 & keyer_read_paddle()) {
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
  }
}
