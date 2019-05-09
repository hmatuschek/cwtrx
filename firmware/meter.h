#ifndef __METER_H__
#define __METER_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void meter_init();
void meter_start();
void meter_poll();
void meter_update();

/** Returns signal strength in 6dB voltages. */
uint8_t meter_sig();

#endif // __METER_H__
