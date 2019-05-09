#ifndef __TONE_H__
#define __TONE_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void tone_init();
void tone_set_frequency(uint16_t freq);
void tone_set_volume(uint8_t level);

void tone_on();
void tone_off();

#endif // __TONE_H__
