#include "menu.h"
#include "lcd.h"
#include "display.h"
#include "meter.h"

MenuState _menu_state = MENU_STEP;
uint8_t   _menu_cursor = 0;

MenuState menu_state() {
  return _menu_state;
}

uint8_t menu_cursor() {
  return _menu_cursor;
}

void menu_update(RotButton button, int8_t delta)
{
  // Quick exit
  if ((ROT_BUTTON_NONE == button) && (0 == delta))
    return;

  if (MENU_RIT == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_RIT;
    } else if (delta > 0) {
      _menu_state = MENU_CW_SPEED;
    } else {
      _menu_state = MENU_SETUP;
    }
  } else if (MENU_SET_RIT == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      trx_set_state(TRX_RX);
      _menu_state = MENU_RIT;
    } else if ((delta > 0) && (trx_rit() < TRX_RIT_MAX)) {
      trx_set_rit(trx_rit()+1);
    } else if ((delta < 0) && (trx_rit() > TRX_RIT_MIN)) {
      trx_set_rit(trx_rit()-1);
    }
  } else if (MENU_CW_SPEED == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_CW_SPEED;
    } else if (delta > 0) {
      _menu_state = MENU_STEP;
    } else {
      _menu_state = MENU_RIT;
    }
  } else if (MENU_SET_CW_SPEED == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_CW_SPEED;
      trx_set_state(TRX_RX);
    } else if ((delta > 0) && (trx_cw_speed()<(KEYER_NUM_SPEED-1))) {
      trx_set_cw_speed(trx_cw_speed()+1);
    } else if ((delta < 0) && (trx_cw_speed()>0)) {
      trx_set_cw_speed(trx_cw_speed()-1);
    }
  } else if (MENU_STEP == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_STEP;
    } else if (delta > 0) {
      _menu_state = MENU_VFO;
    } else {
      _menu_state = MENU_CW_SPEED;
    }
  } else if (MENU_SET_STEP == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      trx_set_state(TRX_RX);
      _menu_state = MENU_STEP;
    } else if ((delta > 0) && (trx_tune_step() < TRX_STEP_10k)) {
      trx_set_tune_step(trx_tune_step()+1);
    } else if ((delta < 0) && (trx_tune_step() > TRX_STEP_10)) {
      trx_set_tune_step(trx_tune_step()-1);
    }
  } else if (MENU_VFO == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_VFO;
    } else if (delta > 0) {
      _menu_state = MENU_BAND;
    } else {
      _menu_state = MENU_STEP;
    }
  } else if (MENU_SET_VFO == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      trx_set_state(TRX_RX);
      _menu_state = MENU_VFO;
    } else if ((delta > 0) && (trx_vfo_mode() < VFO_MODE_SPLIT)) {
      trx_set_vfo_mode(trx_vfo_mode()+1);
    } else if ((delta < 0) && (trx_vfo_mode() > VFO_MODE_A)) {
      trx_set_vfo_mode(trx_vfo_mode()-1);
    }
  } else if (MENU_BAND == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_BAND;
    } else if (delta > 0) {
      _menu_state = MENU_SETUP;
    } else {
      _menu_state = MENU_VFO;
    }
  } else if (MENU_SET_BAND == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_BAND;
      trx_set_state(TRX_RX);
    } else if ((delta > 0) && (trx_band() < BAND_10)) {
      trx_set_band(trx_band()+1);
    } else if ((delta < 0) && (trx_band() > BAND_80)) {
      trx_set_band(trx_band()-1);
    }
  } else if (MENU_SETUP == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_CW_MODE;
    } else if (delta > 0) {
      _menu_state = MENU_RIT;
    } else if (delta < 0) {
      _menu_state = MENU_BAND;
    }
  } else if (MENU_CW_MODE == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_CW_MODE;
    } else if (delta > 0) {
      _menu_state = MENU_CW_TONE;
    } else {
      _menu_state = MENU_PLL_CORRECTION;
    }
  } else if (MENU_SET_CW_MODE == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      trx_set_state(TRX_RX);
      _menu_state = MENU_SETUP;
    } else if (KEYER_MODE_STRAIGHT == trx_cw_mode()) {
      trx_set_cw_mode(KEYER_MODE_PADDLE);
    } else {
      trx_set_cw_mode(KEYER_MODE_STRAIGHT);
    }
  } else if (MENU_CW_TONE == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_CW_TONE;
    } else if (delta > 0) {
      _menu_state = MENU_CW_LEVEL;
    } else {
      _menu_state = MENU_CW_MODE;
    }
  } else if (MENU_SET_CW_TONE == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_cw_tone()<1000)) {
      trx_set_cw_tone(trx_cw_tone()+10);
    } else if ((delta<0) && (trx_cw_tone()>10)) {
      trx_set_cw_tone(trx_cw_tone()-10);
    }
  } else if (MENU_CW_LEVEL == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_CW_LEVEL;
    } else if (delta > 0) {
      _menu_state = MENU_CW_TEXT;
    } else {
      _menu_state = MENU_CW_TONE;
    }
  } else if (MENU_SET_CW_LEVEL == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_cw_level()<255)) {
      trx_set_cw_level(trx_cw_level()+1);
    } else if ((delta<0) && (trx_cw_tone()>1)) {
      trx_set_cw_level(trx_cw_level()-1);
    }
  } else if (MENU_CW_TEXT == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_CW_TEXT;
      _menu_cursor = 0;
    } else if (delta > 0) {
      _menu_state = MENU_CLEAR_CW_TEXT;
    } else {
      _menu_state = MENU_CW_LEVEL;
    }
  } else if (MENU_SET_CW_TEXT == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_CW_TEXT_CHAR;
    } else if (ROT_BUTTON_LONG == button) {
      trx_update_cwtext();
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (_menu_cursor<(TRX_CWTEXT_MAXLEN-1))) {
      _menu_cursor++;
    } else if ((delta<0) && (_menu_cursor>0)) {
      _menu_cursor--;
    }
  } else if (MENU_SET_CW_TEXT_CHAR == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_CW_TEXT;
      if (_menu_cursor<(TRX_CWTEXT_MAXLEN-1))
        _menu_cursor++;
    } else if ((delta>0) && (trx_cwtext()[_menu_cursor] < (KEYER_NUM_SYMBOLS-1))) {
      trx_cwtext()[_menu_cursor]++;
    } else if ((delta<0) && (trx_cwtext()[_menu_cursor] > 0)) {
      trx_cwtext()[_menu_cursor]--;
    }
  } else if (MENU_CLEAR_CW_TEXT == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_CLEAR_CW_TEXT_NO;
    } else if (delta>0) {
      _menu_state = MENU_METER;
    } else {
      _menu_state = MENU_CW_TEXT;
    }
  } else if (MENU_CLEAR_CW_TEXT_NO == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SETUP;
    } else if (delta) {
      _menu_state = MENU_CLEAR_CW_TEXT_YES;
    }
  } else if (MENU_CLEAR_CW_TEXT_YES == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      trx_clear_cwtext();
      _menu_state = MENU_SETUP;
    } else if (delta) {
      _menu_state = MENU_CLEAR_CW_TEXT_NO;
    }
  } else if (MENU_METER == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_METER;
    } else if (delta>0) {
      _menu_state = MENU_TX_HOLD;
    } else {
      _menu_state = MENU_CLEAR_CW_TEXT;
    }
  } else if (MENU_SET_METER == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_meter_type() != METER_TEMP)) {
      trx_set_meter_type(trx_meter_type()+1);
    } else if ((delta<0) && (trx_meter_type() != METER_NONE)) {
      trx_set_meter_type(trx_meter_type()-1);
    }
  } else if (MENU_TX_HOLD == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_TX_HOLD;
    } else if (delta>0) {
      _menu_state = MENU_GREET;
    } else {
      _menu_state = MENU_METER;
    }
  } else if (MENU_SET_TX_HOLD == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_tx_hold()<=990)) {
      trx_set_tx_hold(trx_tx_hold()+10);
    } else if ((delta<0) && (trx_tx_hold()>=10)) {
      trx_set_tx_hold(trx_tx_hold()-10);
    }
  } else if (MENU_GREET == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_GREET;
      _menu_cursor = 0;
    } else if (delta > 0) {
      _menu_state = MENU_ROT_TYPE;
    } else {
      _menu_state = MENU_TX_HOLD;
    }
  } else if (MENU_SET_GREET == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_GREET_CHAR;
    } else if (ROT_BUTTON_LONG == button) {
      trx_update_greet();
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (_menu_cursor<7)) {
      _menu_cursor++;
    } else if ((delta<0) && (_menu_cursor>0)) {
      _menu_cursor--;
    }
  } else if (MENU_SET_GREET_CHAR == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_GREET;
    } else if ((delta>0) && (trx_greet()[_menu_cursor] < 0x7f)) {
      trx_greet()[_menu_cursor]++;
    } else if ((delta<0) && (trx_greet()[_menu_cursor] > 0x20)) {
      trx_greet()[_menu_cursor]--;
    }
  } else if (MENU_ROT_TYPE == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_ROT_TYPE;
    } else if (delta>0) {
      _menu_state = MENU_PLL_CORRECTION;
    } else {
      _menu_state = MENU_SET_GREET;
    }
  } else if (MENU_SET_ROT_TYPE == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_rot_type() < ROT_TYPE_B_Rev)) {
      trx_set_rot_type(trx_rot_type()+1);
    } else if ((delta<0) && (trx_rot_type() > 0)) {
      trx_set_rot_type(trx_rot_type()-1);
    }
  } else if (MENU_PLL_CORRECTION == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SET_PLL_CORRECTION;
    } else if (delta > 0) {
      _menu_state = MENU_RESET;
    } else {
      _menu_state = MENU_ROT_TYPE;
    }
  } else if (MENU_SET_PLL_CORRECTION == _menu_state) {
    if (ROT_BUTTON_CLICK == button) {
      _menu_state = MENU_SETUP;
      trx_set_state(TRX_RX);
    } else if ((delta>0) && (trx_pll_correction()<1000L)) {
      trx_set_pll_correction(trx_pll_correction()+delta);
    } else if ((delta<0) && (trx_pll_correction()>-1000L)) {
      trx_set_pll_correction(trx_pll_correction()+delta);
    }
  } else if (MENU_RESET == _menu_state) {
    if (ROT_BUTTON_LONG == button) {
      _menu_state = MENU_RESET_DONE;
      trx_factory_reset();
    } else if (delta > 0) {
      _menu_state = MENU_CW_MODE;
    } else {
      _menu_state = MENU_PLL_CORRECTION;
    }
  } else if (MENU_RESET_DONE == _menu_state) {
    // trap.
  }
  display_update();
}


