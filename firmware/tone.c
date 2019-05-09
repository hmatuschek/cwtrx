#include "tone.h"
#include <avr/pgmspace.h>

volatile uint16_t _tone_lutidx = 0;
volatile uint16_t _tone_lutinc = 0;

const uint8_t _prg_lut[64] PROGMEM = {
  127, 139, 151, 163, 175, 186, 197, 207,
  216, 225, 232, 239, 244, 248, 251, 253,
  254, 253, 251, 248, 244, 239, 232, 225,
  216, 207, 197, 186, 175, 163, 151, 139,
  127, 114, 102,  90,  78,  67,  56,  46,
   37,  28,  21,  14,   9,   5,   2,   1,
    1,   1,   2,   5,   9,  14,  21,  28,
   37,  46,  56,  67,  78,  90, 102, 114 };

static uint8_t _tone_lut[64] = {
  127, 139, 151, 163, 175, 186, 197, 207,
  216, 225, 232, 239, 244, 248, 251, 253,
  254, 253, 251, 248, 244, 239, 232, 225,
  216, 207, 197, 186, 175, 163, 151, 139,
  127, 114, 102,  90,  78,  67,  56,  46,
   37,  28,  21,  14,   9,   5,   2,   1,
    1,   1,   2,   5,   9,  14,  21,  28,
   37,  46,  56,  67,  78,  90, 102, 114 };


void tone_init() {
  DDRB |= (1<<PB1);
  TCCR1A |= ( (1<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (1<<WGM10) );
  TCCR1B |= ( (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10) );
  TCCR1C |= ( (0<<FOC1A) | (0<<FOC1B) );
  OCR1A  = 125;
  TIMSK1 |= (1<<OCIE1A);
}

void tone_set_frequency(uint16_t freq) {
  // update LUT increment
  _tone_lutinc = (((uint64_t)freq)<<24)/F_CPU;
}

void tone_set_volume(uint8_t level) {
  memcpy_P(_tone_lut, _prg_lut, 64);
  for (uint8_t i=0; i<64; i++) {
    _tone_lut[i] = (level*((uint16_t) _tone_lut[i]))/255;
  }
}

void tone_on() {
  // clear clock selection bits
  TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
  // set & enable timer
  TCCR1B |= ((0<<CS12) | (0<<CS11) | (1<<CS10));
}

void tone_off() {
  // clear clock selection bits -> stop timer/counter
  TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
}

ISR(TIMER1_COMPA_vect) {
  _tone_lutidx += _tone_lutinc;
  OCR1A = _tone_lut[_tone_lutidx>>10];
}

