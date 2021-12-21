#ifndef __KEYER_H__
#define __KEYER_H__

#include <avr/io.h>
#include <inttypes.h>

#define KEYER_A_PORT PORTB
#define KEYER_A_PIN  PINB
#define KEYER_A_DDR  DDRB
#define KEYER_A_BIT  PB3

#define KEYER_B_PORT PORTB
#define KEYER_B_PIN  PINB
#define KEYER_B_DDR  DDRB
#define KEYER_B_BIT  PD2

#define KEYER_NUM_SPEED 25

/** Possible states of the state machine. */
typedef enum {
  KEYER_IDLE,         ///< Idle, wait for keys.
  KEYER_SEND_DIT,     ///< Send a dit.
  KEYER_SEND_DAH,     ///< Send a dah.
  KEYER_PAUSE,
  KEYER_SEND,         ///< Just enable TX for straight key or PTT
  KEYER_SEND_TEXT     ///< Sends a programmed text.
} KeyerState;

typedef enum {
  KEYER_MODE_A = 0,
  KEYER_MODE_B = 1,
  KEYER_MODE_A_REV = 2,
  KEYER_MODE_B_REV = 3,
  KEYER_MODE_STRAIGHT = 4
} KeyerMode;

#define KEYER_NUM_SYMBOLS 39

void keyer_init(KeyerMode mode, uint8_t speed);

uint8_t keyer_speed_wpm();
void keyer_set_speed_idx(uint8_t idx);

uint8_t keyer_read_paddle();

KeyerMode keyer_mode();
void keyer_set_mode(KeyerMode mode);

void keyer_send_text(const uint8_t *sym, uint8_t len);
uint8_t keyer_sym2char(uint8_t sym);

void keyer_poll();
void keyer_tick();

#endif // __KEYER_H__
