#include "rot.h"
#include <stdbool.h>


volatile bool _last_a;
volatile bool _last_b;
volatile bool _last_m;

volatile int8_t    _delta;
volatile bool      _button_down;
volatile uint16_t  _button_count;
volatile RotButton _button;
EncoderType _type = ROT_TYPE_A;

#define read_a ( (ROT_PIN & (1 << ROT_A_BIT)) ? true : false )
#define read_b ( (ROT_PIN & (1 << ROT_B_BIT)) ? true : false )
#define read_m ( (ROT_PIN & (1 << ROT_M_BIT)) ? true : false )

#define _DEBOUNCE_TIMEOUT    200
#define _LONGPRESS_DURATION  2000



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
  bool a = read_a, b = read_b, button = read_m;
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
    // On falling edge
    _button_down = true;
    _button_count = 0;
  } else if (_button_down && button) {
    // On rising edge
    _button_down = false;
    if (_button_count < _DEBOUNCE_TIMEOUT) {
      // ignore (bounce)
      _button = ROT_BUTTON_NONE;
    } else if ((_button_count < _LONGPRESS_DURATION) && (ROT_BUTTON_NONE == _button)){
      // click (hold less than LONGPRESS_DURATION)
      _button = ROT_BUTTON_CLICK;
    } else if (ROT_BUTTON_HOLD_TUNE == _button) {
      _button = ROT_BUTTON_HOLD_TUNE_DONE;
    }
  } else if (_button_down) {
    // While button pressed
    if (_button_count < _DEBOUNCE_TIMEOUT) {
      // Ingore everything within debounce interval
      _button_count++;
      _delta = 0;
    } else if (_button_count < _LONGPRESS_DURATION) {
      // Was turned within long-press interval ...
      if (_delta)
        _button = ROT_BUTTON_HOLD_TUNE;
      // ... otherwise increment counter
      if (ROT_BUTTON_NONE == _button)
        _button_count++;
    } else if (_button_count == _LONGPRESS_DURATION) {
      // until LONGPRESS_DURATION  -> button hold event
      _button_count++;
      _button = ROT_BUTTON_LONG;
    }
    // t > LONGPRESS_DURATION -> stop counting
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


