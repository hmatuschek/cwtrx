#ifndef __BAND_H__
#define __BAND_H__

#include <avr/io.h>

#define BAND_PORT            PORTB
#define BAND_DDR             DDRB
#define BAND_80_BIT          PB2
#define BAND_60_40_BIT       PB3
#define BAND_30_20BIT        PB4
#define BAND_17_15_12_10_BIT PB5

typedef enum {
  BAND_80 = 0,
  BAND_60,
  BAND_40,
  BAND_30,
  BAND_20,
  BAND_17,
  BAND_15,
} Band;

void band_init();
void band_set(Band band);

#endif // __BAND_H__
