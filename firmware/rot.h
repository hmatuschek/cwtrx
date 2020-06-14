#ifndef __ROT_H__
#define __ROT_H__

#include <avr/io.h>
#include <inttypes.h>


#define ROT_PIN    PINC
#define ROT_PORT   PORTC
#define ROT_DDR    DDRC
#define ROT_A_BIT  PC1
#define ROT_B_BIT  PC2
#define ROT_M_BIT  PC3

typedef enum {
  ROT_TYPE_A = 0,
  ROT_TYPE_A_Rev,
  ROT_TYPE_B,
  ROT_TYPE_B_Rev
} EncoderType;

void rot_init(EncoderType type);
void rot_set_type(EncoderType type);

typedef enum {
  ROT_BUTTON_NONE = 0,
  ROT_BUTTON_CLICK,
  ROT_BUTTON_HOLD_TUNE,
  ROT_BUTTON_LONG
} RotButton;

RotButton rot_button();
int8_t rot_delta();

void rot_tick();

#endif // __ROT_H__
