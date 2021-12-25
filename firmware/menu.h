#ifndef __MENU_H__
#define __MENU_H__

#include "trx.h"
#include "rot.h"

typedef enum {
  MENU_RIT,
  MENU_SET_RIT,

  MENU_CW_SPEED,
  MENU_SET_CW_SPEED,

  MENU_STEP,
  MENU_SET_STEP,

  MENU_VFO,
  MENU_SET_VFO,

  MENU_BAND,
  MENU_SET_BAND,

  MENU_SETUP,

  MENU_QUICK_SET,
  MENU_SET_QUICK_SET,

  MENU_KEY_TYPE,
  MENU_SET_KEY_TYPE,
  MENU_KEY_REVERSE,
  MENU_SET_KEY_REVERSE,
  MENU_IAMBIC_MODE,
  MENU_SET_IAMBIC_MODE,

  MENU_CW_TONE,
  MENU_SET_CW_TONE,
  MENU_CW_LEVEL,
  MENU_SET_CW_LEVEL,

  MENU_CW_TEXT,
  MENU_SET_CW_TEXT,
  MENU_SET_CW_TEXT_CHAR,
  MENU_CLEAR_CW_TEXT,
  MENU_CLEAR_CW_TEXT_NO,
  MENU_CLEAR_CW_TEXT_YES,

  MENU_METER,
  MENU_SET_METER,

  MENU_TX_HOLD,
  MENU_SET_TX_HOLD,

  MENU_TX_ENABLE,
  MENU_SET_TX_ENABLE,

  MENU_GREET,
  MENU_SET_GREET,
  MENU_SET_GREET_CHAR,

  MENU_ROT_TYPE,
  MENU_SET_ROT_TYPE,

  MENU_VERSION,

  MENU_SIDEBAND,
  MENU_SET_SIDEBAND,
  MENU_PLL_CORRECTION,
  MENU_SET_PLL_CORRECTION,

  MENU_RESET,
  MENU_RESET_DONE
} MenuState;


MenuState menu_state();
uint8_t menu_cursor();

void menu_update(RotButton button_up, int8_t delta);

#endif // __MENU_H__
