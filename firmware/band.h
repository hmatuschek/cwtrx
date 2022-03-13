#ifndef __BAND_H__
#define __BAND_H__

#include <avr/io.h>

#define BAND_80_60_PORT          PORTB
#define BAND_80_60_DDR           DDRB
#define BAND_80_60_BIT           PB0
#define BAND_40_30_PORT       PORTD
#define BAND_40_30_DDR        DDRD
#define BAND_40_30_BIT        PD7
#define BAND_20_17_PORT       PORTD
#define BAND_20_17_DDR        DDRD
#define BAND_20_17_BIT        PD6
#define BAND_15_12_10_PORT PORTD
#define BAND_15_12_10_DDR  DDRD
#define BAND_15_12_10_BIT  PD5

typedef enum {
  BAND_80 = 0,
  BAND_60,
  BAND_40,
  BAND_30,
  BAND_20,
  BAND_17,
  BAND_15,
  BAND_12,
  BAND_10
} Band;

void band_init();
void band_set(Band band);

#endif // __BAND_H__
