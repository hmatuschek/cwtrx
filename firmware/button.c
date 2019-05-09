#include "button.h"

void buttons_init() {
  // set as input
  TRXMODE_BUTTON_DDR  &= ~(1 << TRXMODE_BUTTON_BIT);
  // Enable pullup
  TRXMODE_BUTTON_PORT |= (1 << TRXMODE_BUTTON_BIT);
}

TRXMode button_mode() {
  if (TRXMODE_BUTTON_PIN & (1<<TRXMODE_BUTTON_BIT))
    return TRX_SSB;
  return TRX_CW;
}
