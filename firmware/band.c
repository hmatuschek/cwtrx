#include "band.h"

void band_init() {
  // set output
  BAND_DDR |= ( (1 << BAND_80_BIT) | (1 << BAND_60_40_BIT) | (1 << BAND_30_20BIT) |
                (1 << BAND_17_15_12_10_BIT) );
  // clear bits
  BAND_PORT &= ~( (1 << BAND_80_BIT) | (1 << BAND_60_40_BIT) | (1 << BAND_30_20BIT) |
                  (1 << BAND_17_15_12_10_BIT) );
}

void band_set(Band band) {
  // clear bits
  BAND_PORT &= ~( (1 << BAND_80_BIT) | (1 << BAND_60_40_BIT) | (1 << BAND_30_20BIT) |
                  (1 << BAND_17_15_12_10_BIT) );

  // Enable relais for each band
  switch (band) {
    case BAND_80:
      BAND_PORT |= (1 << BAND_80_BIT);
      break;
    case BAND_60:
    case BAND_40:
      BAND_PORT |= (1 << BAND_60_40_BIT);
      break;
    case BAND_30:
    case BAND_20:
      BAND_PORT |= (1 << BAND_30_20BIT);
      break;
    case BAND_17:
    case BAND_15:
      BAND_PORT |= (1 << BAND_17_15_12_10_BIT);
      break;
  }
}
