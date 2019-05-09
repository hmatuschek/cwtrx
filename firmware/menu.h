#ifndef __MENU_H__
#define __MENU_H__

#include "trx.h"
/*
 * Menu Structure:
 *
 * +-------------------------------------+
 * |                                     |
 * +-> Step <-> VFO <-> Band <-> Setup <-+
 *                                 |
 *                            +-> Key <-> CWSp <-> Tone <-> Lvl <-> Hld <-> TX En <-> PLL <-+
 *                            |                                                             |
 *                            +-------------------------------------------------------------+
 */

typedef enum {
  MENU_STEP,
  MENU_SET_STEP,
  MENU_VFO,
  MENU_SET_VFO,
  MENU_BAND,
  MENU_SET_BAND,
  MENU_SETUP,
  MENU_CW_MODE,
  MENU_SET_CW_MODE,
  MENU_CW_SPEED,
  MENU_SET_CW_SPEED,
  MENU_CW_TONE,
  MENU_SET_CW_TONE,
  MENU_CW_LEVEL,
  MENU_SET_CW_LEVEL,
  MENU_TX_HOLD,
  MENU_SET_TX_HOLD,
  MENU_TX_ENABLE,
  MENU_SET_TX_ENABLE,
  MENU_PLL_CORRECTION,
  MENU_SET_PLL_CORRECTION
} MenuState;


MenuState menu_state();
void menu_update(uint8_t button_up, int8_t delta);

#endif // __MENU_H__
