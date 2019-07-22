#ifndef __METER_H__
#define __METER_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

typedef enum {
  METER_NONE,
  METER_SIG,
  METER_VOLTAGE,
  METER_TEMP
} MeterType;

void meter_init(MeterType type);
void meter_set_type(MeterType type);
void meter_start();
void meter_poll();
void meter_update();

#endif // __METER_H__
