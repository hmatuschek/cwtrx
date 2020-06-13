#include "band.h"

void band_init() {
  // set output
  BAND_80_DDR |= (1 << BAND_80_BIT);
  BAND_60_40_DDR |= (1 << BAND_60_40_BIT);
  BAND_30_20_DDR |= (1 << BAND_30_20_BIT);
  BAND_17_15_12_10_DDR |= (1 << BAND_17_15_12_10_BIT);
  // clear bits
  BAND_80_PORT &= ~(1 << BAND_80_BIT);
  BAND_60_40_PORT &= ~(1 << BAND_60_40_BIT);
  BAND_30_20_PORT &= ~(1 << BAND_30_20_BIT);
  BAND_17_15_12_10_PORT &= ~(1 << BAND_17_15_12_10_BIT);
}

void band_set(Band band) {
  // clear bits
  BAND_80_PORT &= ~(1 << BAND_80_BIT);
  BAND_60_40_PORT &= ~(1 << BAND_60_40_BIT);
  BAND_30_20_PORT &= ~(1 << BAND_30_20_BIT);
  BAND_17_15_12_10_PORT &= ~(1 << BAND_17_15_12_10_BIT);

  // Enable relais for each band
  switch (band) {
    case BAND_80:
    case BAND_60:
      BAND_80_PORT |= (1 << BAND_80_BIT);
      break;
    case BAND_40:
    case BAND_30:
      BAND_60_40_PORT |= (1 << BAND_60_40_BIT);
      break;
    case BAND_20:
    case BAND_17:
      BAND_30_20_PORT |= (1 << BAND_30_20_BIT);
      break;
    case BAND_15:
    case BAND_12:
    case BAND_10:
      BAND_17_15_12_10_PORT |= (1 << BAND_17_15_12_10_BIT);
      break;
  }
}
