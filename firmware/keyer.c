#include "keyer.h"
#include "trx.h"
#include "button.h"
#include <avr/pgmspace.h>

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

// The default dit length and derived keyer timing
#define DEFAULT_DIT_LEN 60
typedef struct {
  uint16_t dit_len;
  uint16_t dah_len;
  uint16_t iambic_dit_latch_delay;
  uint16_t iambic_dah_latch_delay;
  uint16_t latch_delay;
} KeyerTiming;

KeyerTiming _keyer_timing = {
  DEFAULT_DIT_LEN,
  3*DEFAULT_DIT_LEN,
  DEFAULT_DIT_LEN/4,
  3*DEFAULT_DIT_LEN/2,
  DEFAULT_DIT_LEN/2
};


/* Possible states of the state machine. */
typedef enum {
  KEYER_IDLE,         ///< Idle, wait for any input.
  KEYER_SEND_DIT,     ///< Send a dit.
  KEYER_SEND_DAH,     ///< Send a dah.
  KEYER_PAUSE,        ///< Inter-symbol pause (i.e. between dits).
  KEYER_SEND,         ///< Just enable TX for straight key.
  KEYER_SEND_TEXT     ///< Sends a programmed text.
} KeyerState;

// The state variable
volatile KeyerState _keyer_state = KEYER_IDLE;
volatile KeyerState _keyer_last_state = KEYER_IDLE;

/* Latching states. */
typedef enum {
  KEYER_NO_LATCH     = 0, ///< Do not latch any input.
  KEYER_LATCH_LEFT   = KEYER_KEY_LEFT,  ///< Latch only left paddle
  KEYER_LATCH_RIGHT  = KEYER_KEY_RIGHT, ///< Latch only right paddle
  KEYER_LATCH        = (KEYER_LATCH_LEFT|KEYER_LATCH_RIGHT)  ///< Latch all inputs
} KeyerLatch;

volatile KeyerLatch _keyer_latch_state = KEYER_NO_LATCH;
// Holds the currently latched key
uint8_t _paddle_latch = 0;

// The key type and keyer mode
volatile KeyerType _keyer_type              = KEYER_TYPE_STRAIGHT;
volatile KeyerIambicMode _keyer_iambic_mode = KEYER_IAMBIC_B;
volatile uint8_t _keyer_is_reversed         = 0;

// Auto text variables
volatile uint8_t   _text_len        = 0;
const    uint8_t   *_text           = 0;
volatile uint8_t   _current_sym_len = 0;
volatile uint32_t  _current_sym     = 0;


uint8_t
keyer_speed_wpm() {
  return ditlen_idx+10;
}

void
keyer_update_timing(uint16_t ditlen) {
  _keyer_timing.dit_len                = ditlen;
  _keyer_timing.dah_len                = 3*ditlen;
  _keyer_timing.iambic_dit_latch_delay = ditlen/4;
  _keyer_timing.iambic_dah_latch_delay = 3*ditlen/2;
  _keyer_timing.latch_delay            = ditlen/2;
}

void
keyer_set_speed_idx(uint8_t idx) {
  if (idx >= KEYER_NUM_SPEED)
    idx = KEYER_NUM_SPEED-1;
  ditlen_idx = idx;
  keyer_update_timing(dit_len_lut[ditlen_idx]);
}

KeyerType
keyer_type() {
  return _keyer_type;
}
void
keyer_set_type(KeyerType type) {
  _keyer_type = type;
}

KeyerIambicMode
keyer_iambic_mode() {
  return _keyer_iambic_mode;
}
void
keyer_set_iambic_mode(KeyerIambicMode mode) {
  _keyer_iambic_mode = mode;
}

uint8_t
keyer_paddle_reversed() {
  return _keyer_is_reversed;
}
void
keyer_set_paddle_reversed(uint8_t reversed) {
  if (reversed)
    _keyer_is_reversed = 1;
  else
    _keyer_is_reversed = 0;
}


// Util function for modes
inline uint8_t keyer_is_idle() {
  return (KEYER_IDLE == _keyer_state);
}
inline uint8_t keyer_is_pausing() {
  return (KEYER_PAUSE == _keyer_state);
}
inline void keyer_state_reset() {
  _keyer_last_state = _keyer_state = KEYER_IDLE;
}
inline void keyer_state_shift(KeyerState state) {
  _keyer_last_state = _keyer_state;
  _keyer_state = state;
}

inline uint8_t keyer_is_straight() {
  return KEYER_TYPE_STRAIGHT == _keyer_type;
}
inline uint8_t keyer_is_iambic() {
  return KEYER_TYPE_IAMBIC == _keyer_type;
}
inline uint8_t keyer_is_iambic_B() {
  return keyer_is_iambic() && (KEYER_IAMBIC_B == _keyer_iambic_mode);
}


/// Initializes the keyer and PTT interface and timer
void
keyer_init(KeyerType type, KeyerIambicMode mode, uint8_t reverse, uint8_t speed) {
  // config keyer inputs
  KEYER_A_DDR &= ~(1 << KEYER_A_BIT);
  KEYER_B_DDR &= ~(1 << KEYER_B_BIT);
  // enable pullups on inputs
  KEYER_A_PORT |= (1 << KEYER_A_BIT);
  KEYER_B_PORT |= (1 << KEYER_B_BIT);

  keyer_set_type(type);
  keyer_set_iambic_mode(mode);
  keyer_set_paddle_reversed(reverse);
  keyer_set_speed_idx(speed);

  keyer_state_reset();
}

inline uint8_t
keyer_read_paddle() {
  uint8_t key = ( (((~KEYER_B_PIN) & (1<<KEYER_B_BIT)) ? KEYER_KEY_RIGHT: KEYER_KEY_NONE) |
                  (((~KEYER_A_PIN) & (1<<KEYER_A_BIT)) ? KEYER_KEY_LEFT : KEYER_KEY_NONE) );
  // handle reversal (left dah, right dit)
  if (_keyer_is_reversed)
    return ((key >> 1) & 1) | ((key & 1) << 1);
  return key;
}

inline uint8_t
keyer_latch() {
  _paddle_latch |= (_keyer_latch_state & keyer_read_paddle());
  return _paddle_latch;
}

inline uint8_t
keyer_unlatch() {
  uint8_t tmp = keyer_latch();
  // clear latched input
  _paddle_latch = 0;
  // also stop latching
  _keyer_latch_state = KEYER_NO_LATCH;
  return tmp;
}

inline uint8_t keyer_sym2char(uint8_t sym) {
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
    keyer_state_shift(KEYER_SEND_TEXT);
  }
}

inline void
keyer_poll_send_text() {
  // On any input
  //  -> stop sending
  if ( (keyer_is_straight() && (KEYER_KEY_LEFT & keyer_read_paddle())) ||
       ((! keyer_is_straight()) && keyer_read_paddle()) )
    keyer_state_reset();

  // otherwise continue sending text...
  return;
}

inline void
keyer_poll_straight() {
  // If key down -> send, otherwise not
  if (KEYER_KEY_DOWN & keyer_read_paddle())
    keyer_state_shift(KEYER_SEND);
  else
    keyer_state_shift(KEYER_IDLE);
}

inline void
keyer_poll_paddle() {
  // Decide on idle what to do
  if (! keyer_is_idle())
    return;

  switch (keyer_unlatch()) {
  case KEYER_KEY_LEFT:
    keyer_state_shift(KEYER_SEND_DIT);
    break;

  case KEYER_KEY_RIGHT:
    keyer_state_shift(KEYER_SEND_DAH);
    break;

  case KEYER_KEY_NONE:
    _keyer_latch_state = KEYER_LATCH;
    break;
  }
}


inline void
keyer_poll_iambic() {
  // Decide on idle what to do
  if (! keyer_is_idle())
    return;

  // ... dispatch by latched paddle state
  // (left -> dit, right -> dah, both -> alternate dit & dah)
  switch (keyer_unlatch()) {
  case KEYER_KEY_LEFT:
    keyer_state_shift(KEYER_SEND_DIT);
    break;

  case KEYER_KEY_RIGHT:
    keyer_state_shift(KEYER_SEND_DAH);
    break;

  // On both paddles alternate dit & dah
  case (KEYER_KEY_LEFT | KEYER_KEY_RIGHT):
    if (KEYER_SEND_DIT == _keyer_last_state)
      keyer_state_shift(KEYER_SEND_DAH);
    else
      keyer_state_shift(KEYER_SEND_DIT);
    break;

  case KEYER_KEY_NONE:
    _keyer_latch_state = KEYER_LATCH;
    break;
  }
}

inline void
keyer_poll() {
  // If keyer sends a text
  if (KEYER_TYPE_STRAIGHT == _keyer_type) {
    keyer_poll_straight();
  } else if (KEYER_TYPE_IAMBIC == _keyer_type) {
    keyer_poll_iambic();
  } else if (KEYER_TYPE_PADDLE == _keyer_type) {
    keyer_poll_paddle();
  }

  if (KEYER_SEND_TEXT == _keyer_state) {
    keyer_poll_send_text();
  }
}


void
keyer_tick()
{
  static uint16_t count = 0;

  if (KEYER_TYPE_STRAIGHT != keyer_type())
    keyer_latch();

  if (keyer_is_idle()) {
    // Stop sending...
    trx_rx(); count = 0;
    // Wait for any input
    _keyer_latch_state = KEYER_LATCH;
  } else if (KEYER_SEND_DIT == _keyer_state) {
    // Send a dit (1)
    if (0 == count) {
      trx_tx(); count++;
    } else if (_keyer_timing.dit_len == count) {
      trx_rx();
      keyer_state_shift(KEYER_PAUSE);
      count=0;
    } else {
      count++;
    }
    // control latch
    if (keyer_is_iambic_B() && (count >= _keyer_timing.iambic_dit_latch_delay)) {
      _keyer_latch_state = KEYER_LATCH_RIGHT;
    }
  } else if (KEYER_SEND_DAH == _keyer_state) {
    // Send a dah (111)
    if (0 == count) {
      trx_tx(); count++;
    } else if (_keyer_timing.dah_len == count) {
      trx_rx();
      keyer_state_shift(KEYER_PAUSE);
      count = 0;
    } else {
      count++;
    }
    // control latch
    if (keyer_is_iambic_B() && (count >= _keyer_timing.iambic_dah_latch_delay)) {
      _keyer_latch_state = KEYER_LATCH_LEFT;
    }
  } else if (KEYER_PAUSE == _keyer_state) {
    // Send pause
    if (0 == count) {
      trx_rx(); count++;
    } else if (_keyer_timing.dit_len == count) {
      // Do not shift idle here to maintain last DIT or DAH
      _keyer_state = KEYER_IDLE;
      _keyer_latch_state = KEYER_LATCH;
      count = 0;
    } else {
      count++;
    }
    // control latch
    if (count >= _keyer_timing.latch_delay) {
      _keyer_latch_state = KEYER_LATCH;
    }
  } else if (KEYER_SEND == _keyer_state) {
    trx_tx();
  } else if (KEYER_SEND_TEXT == _keyer_state) {
    if (_keyer_timing.dit_len == count) {
      // If a dit-length has passed and ...
      // ... there is no symbol nor further text to send ...
      if ((0 == _text_len) && (0 == _current_sym_len)) {
        // Set keyer to idle
        keyer_state_reset();
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
