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

/** Specifies possible rotary encoder types. */
typedef enum {
  ROT_TYPE_A = 0, ///< Type A, e.g. 15/30 types.
  ROT_TYPE_A_Rev, ///< Type A reverse encoding, e.g. 15/30 types.
  ROT_TYPE_B,     ///< Type B, e.g. 20/20 types.
  ROT_TYPE_B_Rev  ///< Type B reverse encoding, e.g. 20/20 types.
} EncoderType;

/** Init rotary encoder pins. */
void rot_init(EncoderType type);
/** Set the rotary encoder type. */
void rot_set_type(EncoderType type);

/** Possible "gestures". */
typedef enum {
  ROT_BUTTON_NONE = 0,       ///< No action at all.
  ROT_BUTTON_CLICK,          ///< A short press and release (a.k.a. click).
  ROT_BUTTON_HOLD_TUNE,      ///< Press and turn the encoder.
  ROT_BUTTON_HOLD_TUNE_DONE, ///< Release after press and turn.
  ROT_BUTTON_LONG            ///< Long press of the encoder.
} RotButton;

/** Returns the last gesture of the encoder. */
RotButton rot_button();
/** Direction and amount of the encoder rotation. */
int8_t rot_delta();
/** Gets called every 1ms to update the encoder. */
void rot_tick();

#endif // __ROT_H__
