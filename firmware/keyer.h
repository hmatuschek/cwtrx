#ifndef __KEYER_H__
#define __KEYER_H__

#include <avr/io.h>
#include <inttypes.h>

#define KEYER_A_PORT PORTD
#define KEYER_A_PIN  PIND
#define KEYER_A_DDR  DDRD
#define KEYER_A_BIT  PD4

#define KEYER_B_PORT PORTD
#define KEYER_B_PIN  PIND
#define KEYER_B_DDR  DDRD
#define KEYER_B_BIT  PD4

#define KEYER_NUM_SPEED 25

/** Possible states of the state machine. */
typedef enum {
  KEYER_IDLE,         ///< Idle, wait for keys.
  KEYER_SEND_DIT,     ///< Send a dit.
  KEYER_SEND_DAH,     ///< Send a dah.
  KEYER_SEND          ///< Just enable TX for straight key or PTT
} KeyerState;

typedef enum {
  KEYER_MODE_PADDLE,
  KEYER_MODE_STRAIGHT
} KeyerMode;

void keyer_init(KeyerMode mode, uint8_t speed);

uint8_t keyer_speed_wpm();
void keyer_set_speed_idx(uint8_t idx);

uint8_t keyer_read_paddle();

KeyerMode keyer_mode();
void keyer_set_mode(KeyerMode mode);

void keyer_poll();
void keyer_tick();

#endif // __KEYER_H__
