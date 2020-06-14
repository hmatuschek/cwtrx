#include "rot.h"


volatile uint8_t _last_a;
volatile uint8_t _last_b;
volatile uint8_t _last_m;

volatile int8_t    _delta;
volatile uint8_t   _button_down;
volatile uint16_t  _button_count;
volatile RotButton _button;
EncoderType _type = ROT_TYPE_A;

#define read_a ( (ROT_PIN & (1 << ROT_A_BIT)) ? 1 : 0 )
#define read_b ( (ROT_PIN & (1 << ROT_B_BIT)) ? 1 : 0 )
#define read_m ( (ROT_PIN & (1 << ROT_M_BIT)) ? 1 : 0 )


void rot_init(EncoderType type) {
  // set pins as input
  ROT_DDR  &= ~( (1<<ROT_A_BIT) | (1<<ROT_B_BIT) | (1<<ROT_M_BIT) );
  // enable pullups on inputs
  ROT_PORT |= ( (1<<ROT_A_BIT) | (1<<ROT_B_BIT) | (1<<ROT_M_BIT) );

  _type = (type<ROT_TYPE_B_Rev) ? type : ROT_TYPE_B_Rev;

  _last_a = read_a;
  _last_b = read_b;
  _last_m = read_m;

  _delta = 0;
  _button_down  = 0;
  _button_count = 0;
  _button = ROT_BUTTON_NONE;
}

void rot_set_type(EncoderType type) {
  _type = type;
}

void rot_tick() {
  uint8_t a = read_a, b = read_b, button = read_m;
  if ((ROT_TYPE_A == _type) || (ROT_TYPE_A_Rev == _type)) {
    if (_last_a != a) {
      if (ROT_TYPE_A == _type)
        _delta += ( (a == b) ? -1 : +1 );
      else
        _delta += ( (a == b) ? +1 : -1 );
    }
  } else {
    if ((0 == _last_a) && (1 == a)) {
      if (ROT_TYPE_B == _type)
        _delta += ( (1 == b) ? -1 : +1 );
      else
        _delta += ( (1 == b) ? +1 : -1 );
    }
  }

  if ( _last_m && (0 == button)) {
    // On button down
    _button_down = 1;
    _button_count = 0;
  } else if (_button_down && button) {
    // On button up
    _button_down = 0;
    if (_button_count < 100) {
      // ignore (bounce)
    } else if ((_button_count < 2000) && (ROT_BUTTON_NONE == _button)){
      // click (hold less than 2s)
      _button = ROT_BUTTON_CLICK;
    } else if (ROT_BUTTON_HOLD_TUNE == _button) {
      _button = ROT_BUTTON_NONE;
    }
  } else if (_button_down) {
    // While button down count
    if (_button_count < 2000) {
      if (_delta) {
        _button = ROT_BUTTON_HOLD_TUNE;
      }
      if (ROT_BUTTON_NONE == _button) {
        _button_count++;
      }
    } else if (_button_count == 2000) {
      // until 2000 (2s) -> button hold event
      _button_count++;
      _button = ROT_BUTTON_LONG;
    }
    // over 2000 -> stop counting
  }

  _last_a = a;
  _last_b = b;
  _last_m = button;
}


RotButton rot_button() {
  RotButton state = _button;
  if (ROT_BUTTON_HOLD_TUNE != _button)
    _button = ROT_BUTTON_NONE;
  return state;
}

int8_t rot_delta() {
  int8_t delta = _delta;
  _delta = 0;
  return delta;
}


