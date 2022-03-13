#include "band.h"

void band_init() {
  // set output
  BAND_80_60_DDR     |= (1 << BAND_80_60_BIT);
  BAND_40_30_DDR     |= (1 << BAND_40_30_BIT);
  BAND_20_17_DDR     |= (1 << BAND_20_17_BIT);
  BAND_15_12_10_DDR  |= (1 << BAND_15_12_10_BIT);
  // clear bits
  BAND_80_60_PORT    &= ~(1 << BAND_80_60_BIT);
  BAND_40_30_PORT    &= ~(1 << BAND_40_30_BIT);
  BAND_20_17_PORT    &= ~(1 << BAND_20_17_BIT);
  BAND_15_12_10_PORT &= ~(1 << BAND_15_12_10_BIT);
}

void band_set(Band band) {
  // Enable relais for each band
  switch (band) {
  case BAND_80:
  case BAND_60:
    BAND_80_60_PORT    |= (1 << BAND_80_60_BIT);
    BAND_40_30_PORT    &= ~(1 << BAND_40_30_BIT);
    BAND_20_17_PORT    &= ~(1 << BAND_20_17_BIT);
    BAND_15_12_10_PORT &= ~(1 << BAND_15_12_10_BIT);
    break;
  case BAND_40:
  case BAND_30:
    BAND_80_60_PORT    &= ~(1 << BAND_80_60_BIT);
    BAND_40_30_PORT    |= (1 << BAND_40_30_BIT);
    BAND_20_17_PORT    &= ~(1 << BAND_20_17_BIT);
    BAND_15_12_10_PORT &= ~(1 << BAND_15_12_10_BIT);
    break;
  case BAND_20:
  case BAND_17:
    BAND_80_60_PORT    &= ~(1 << BAND_80_60_BIT);
    BAND_40_30_PORT    &= ~(1 << BAND_40_30_BIT);
    BAND_20_17_PORT    |= (1 << BAND_20_17_BIT);
    BAND_15_12_10_PORT &= ~(1 << BAND_15_12_10_BIT);
    break;
  case BAND_15:
  case BAND_12:
  case BAND_10:
    BAND_80_60_PORT    &= ~(1 << BAND_80_60_BIT);
    BAND_40_30_PORT    &= ~(1 << BAND_40_30_BIT);
    BAND_20_17_PORT    &= ~(1 << BAND_20_17_BIT);
    BAND_15_12_10_PORT |= (1 << BAND_15_12_10_BIT);
    break;
  }
}
