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
#define KEYER_NUM_SYMBOLS 39

typedef enum {
  KEYER_TYPE_IAMBIC   = 0,
  KEYER_TYPE_PADDLE   = 1,
  KEYER_TYPE_STRAIGHT = 2
} KeyerType;

KeyerType keyer_type();
void keyer_set_type(KeyerType type);


typedef enum {
  KEYER_IAMBIC_A = 0,
  KEYER_IAMBIC_B = 1
} KeyerIambicMode;

KeyerIambicMode keyer_iambic_mode();
void keyer_set_iambic_mode(KeyerIambicMode mode);


uint8_t keyer_paddle_reversed();
void keyer_set_paddle_reversed(uint8_t reversed);


uint8_t keyer_speed_wpm();
void keyer_set_speed_idx(uint8_t idx);


/** Possible Keys */
typedef enum {
  KEYER_KEY_NONE  = 0,
  KEYER_KEY_LEFT  = 1,
  KEYER_KEY_RIGHT = 2,
  KEYER_KEY_DOWN  = KEYER_KEY_LEFT
} KeyerKey;

uint8_t keyer_read_paddle();


void keyer_send_text(const uint8_t *sym, uint8_t len);
uint8_t keyer_sym2char(uint8_t sym);


void keyer_init(KeyerType type, KeyerIambicMode mode, uint8_t reverse, uint8_t speed);

void keyer_poll();

void keyer_tick();

#endif // __KEYER_H__
