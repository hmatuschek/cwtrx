#include "rot.h"


volatile uint8_t _last_a;
volatile uint8_t _last_b;
volatile uint8_t _last_m;

volatile int8_t  _delta;
volatile uint8_t _button_up;


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
}

void rot_tick() {
  uint8_t a = read_a, b = read_b, button = read_m;

  if (_last_a!=a)
    _delta += ( (a == b) ? -1 : +1 );

  if ( (0==_last_m) && (1==button))
    _button_up = 1;

  _last_a = a;
  _last_b = b;
  _last_m = button;
}


uint8_t rot_button_read() {
  return _last_m;
}

uint8_t rot_button_up() {
  uint8_t up = _button_up;
  _button_up = 0;
  return up;
}

int8_t rot_delta() {
  int8_t delta = _delta;
  _delta = 0;
  return delta;
}


