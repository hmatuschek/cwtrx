#include "rot.h"


volatile uint8_t _last_a;
volatile uint8_t _last_b;
volatile uint8_t _last_m;

volatile int8_t    _delta;
volatile uint8_t   _button_down;
volatile uint16_t  _button_count;
volatile RotButton _button;


#define read_a ( (ROT_PIN & (1 << ROT_A_BIT)) ? 1 : 0 )
#define read_b ( (ROT_PIN & (1 << ROT_B_BIT)) ? 1 : 0 )
#define read_m ( (ROT_PIN & (1 << ROT_M_BIT)) ? 1 : 0 )


void rot_init() {
  // set pins as input
  ROT_DDR  &= ~( (1<<ROT_A_BIT) | (1<<ROT_B_BIT) | (1<<ROT_M_BIT) );
  // enable pullups on inputs
  ROT_PORT |= ( (1<<ROT_A_BIT) | (1<<ROT_B_BIT) | (1<<ROT_M_BIT) );

  _last_a = read_a;
  _last_b = read_b;
  _last_m = read_m;

  _delta = 0;
  _button_down  = 0;
  _button_count = 0;
  _button = ROT_BUTTON_NONE;
}

void rot_tick() {
  uint8_t a = read_a, b = read_b, button = read_m;

  if (_last_a!=a)
    _delta += ( (a == b) ? -1 : +1 );

  if ( (1==_last_m) && (0==button)) {
    // On button down
    _button_down = 1;
    _button_count = 0;
  } else if (_button_down && (1==button)) {
    // On button up
    _button_down = 0;
    if (_button_count < 100) {
      // ignore (bounce)
    } else if (_button_count < 2000) {
      // click (hold less than 2s)
      _button = ROT_BUTTON_CLICK;
    } else {
      // If was button hold -> ignore
    }
  } else if (_button_down) {
    // While button down count
    if (_button_count < 2000) {
      _button_count++;
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
  _button = ROT_BUTTON_NONE;
  return state;
}

int8_t rot_delta() {
  int8_t delta = _delta;
  _delta = 0;
  return delta;
}


