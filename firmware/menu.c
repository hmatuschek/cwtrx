#include "menu.h"
#include "lcd.h"
#include "display.h"

MenuState _menu_state = MENU_STEP;

MenuState menu_state() {
  return _menu_state;
}

void menu_update(uint8_t button_up, int8_t delta)
{
  // Quick exit
  if ((0 == button_up) && (0 == delta))
    return;

  if (MENU_STEP == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_STEP;
    } else if (delta > 0) {
      _menu_state = MENU_VFO;
    } else {
      _menu_state = MENU_SETUP;
    }
  } else if (MENU_SET_STEP == _menu_state) {
    if (button_up) {
      trx_set_state(TRX_RX);
      _menu_state = MENU_STEP;
    } else if ((delta > 0) && (trx_tune_step() < TRX_STEP_10k)) {
      trx_set_tune_step(trx_tune_step()+1);
    } else if ((delta < 0) && (trx_tune_step() > TRX_STEP_10)) {
      trx_set_tune_step(trx_tune_step()-1);
    }
  } else if (MENU_VFO == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_VFO;
    } else if (delta > 0) {
      _menu_state = MENU_BAND;
    } else {
      _menu_state = MENU_STEP;
    }
  } else if (MENU_SET_VFO == _menu_state) {
    if (button_up) {
      trx_set_state(TRX_RX);
      _menu_state = MENU_VFO;
    } else if ((delta > 0) && (trx_vfo_mode() < VFO_MODE_SPLIT)) {
      trx_set_vfo_mode(trx_vfo_mode()+1);
    } else if ((delta < 0) && (trx_vfo_mode() > VFO_MODE_A)) {
      trx_set_vfo_mode(trx_vfo_mode()-1);
    }
  } else if (MENU_BAND == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_BAND;
    } else if (delta > 0) {
      _menu_state = MENU_SETUP;
    } else {
      _menu_state = MENU_VFO;
    }
  } else if (MENU_SET_BAND == _menu_state) {
    if (button_up) {
      _menu_state = MENU_BAND;
      trx_set_state(TRX_RX);
    } else if ((delta > 0) && (trx_band() < BAND_15)) {
      trx_set_band(trx_band()+1);
    } else if ((delta < 0) && (trx_band() > BAND_80)) {
      trx_set_band(trx_band()-1);
    }
  } else if (MENU_SETUP == _menu_state) {
    if (button_up) {
      _menu_state = MENU_CW_MODE;
    } else if (delta > 0) {
      _menu_state = MENU_STEP;
    } else if (delta < 0) {
      _menu_state = MENU_BAND;
    }
  } else if (MENU_CW_MODE == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_CW_MODE;
    } else if (delta > 0) {
      _menu_state = MENU_CW_SPEED;
    } else {
      _menu_state = MENU_PLL_CORRECTION;
    }
  } else if (MENU_SET_CW_MODE == _menu_state) {
    if (button_up) {
      trx_set_state(TRX_RX);
      _menu_state = MENU_SETUP;
    } else if (KEYER_MODE_STRAIGHT == trx_cw_mode()) {
      trx_set_cw_mode(KEYER_MODE_PADDLE);
    } else {
      trx_set_cw_mode(KEYER_MODE_STRAIGHT);
    }
  } else if (MENU_CW_SPEED == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_CW_SPEED;
    } else if (delta > 0) {
      _menu_state = MENU_CW_TONE;
    } else {
      _menu_state = MENU_CW_MODE;
    }
  } else if (MENU_SET_CW_SPEED == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta > 0) && (trx_cw_speed()<(KEYER_NUM_SPEED-1))) {
      trx_set_cw_speed(trx_cw_speed()+1);
    } else if ((delta < 0) && (trx_cw_speed()>0)) {
      trx_set_cw_speed(trx_cw_speed()-1);
    }
  } else if (MENU_CW_TONE == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_CW_TONE;
    } else if (delta > 0) {
      _menu_state = MENU_CW_LEVEL;
    } else {
      _menu_state = MENU_CW_SPEED;
    }
  } else if (MENU_SET_CW_TONE == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_cw_tone()<1000)) {
      trx_set_cw_tone(trx_cw_tone()+10);
    } else if ((delta<0) && (trx_cw_tone()>10)) {
      trx_set_cw_tone(trx_cw_tone()-10);
    }
  } else if (MENU_CW_LEVEL == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_CW_LEVEL;
    } else if (delta > 0) {
      _menu_state = MENU_TX_HOLD;
    } else {
      _menu_state = MENU_CW_TONE;
    }
  } else if (MENU_SET_CW_LEVEL == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_cw_level()<255)) {
      trx_set_cw_level(trx_cw_level()+1);
    } else if ((delta<0) && (trx_cw_tone()>1)) {
      trx_set_cw_level(trx_cw_level()-1);
    }
  } else if (MENU_TX_HOLD == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_TX_HOLD;
    } else if (delta>0) {
      _menu_state = MENU_TX_ENABLE;
    } else {
      _menu_state = MENU_CW_LEVEL;
    }
  } else if (MENU_SET_TX_HOLD == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_tx_hold()<=990)) {
      trx_set_tx_hold(trx_tx_hold()+10);
    } else if ((delta<0) && (trx_tx_hold()>=10)) {
      trx_set_tx_hold(trx_tx_hold()-10);
    }
  } else if (MENU_TX_ENABLE == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_TX_ENABLE;
    } else if (delta > 0) {
      _menu_state = MENU_PLL_CORRECTION;
    } else {
      _menu_state = MENU_TX_HOLD;
    }
  } else if (MENU_SET_TX_ENABLE == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if (delta) {
      trx_set_tx_enabled(trx_tx_enabled() ? 0 : 1);
    }
  } else if (MENU_PLL_CORRECTION == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SET_PLL_CORRECTION;
    } else if (delta > 0) {
      _menu_state = MENU_CW_MODE;
    } else {
      _menu_state = MENU_TX_ENABLE;
    }
  } else if (MENU_SET_PLL_CORRECTION == _menu_state) {
    if (button_up) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_pll_correction()<1000L)) {
      trx_set_pll_correction(trx_pll_correction()+delta);
    } else if ((delta<0) && (trx_pll_correction()>-1000L)) {
      trx_set_pll_correction(trx_pll_correction()+delta);
    }
  }
  display_update();
}


