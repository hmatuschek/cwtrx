#include "display.h"
#include "trx.h"
#include "menu.h"
#include "lcd.h"
#include "button.h"
#include "config.h"

void display_update() {
  lcd_clear();
  lcd_home();
  lcd_hidecursor();

  switch (trx_state()) {
    case TRX_RX:
    case TRX_TX:
    case TRX_HOLD_TX:
      display_rx();
      break;
    case TRX_MENU:
      display_menu(menu_state());
      break;
  }
}

void display_trx_state() {
  // Time: approx. 180us
  if (TRX_RX == trx_state()) {
    lcd_setcursor(7,2);
    lcd_data(trx_rit_sym());
  } else if (TRX_TX == trx_state()) {
    lcd_setcursor(7,2);
    lcd_data(0x05);
  } else if (TRX_HOLD_TX == trx_state()) {
    lcd_setcursor(7,2);
    lcd_data('T');
  }
}

void display_rx() {
  display_frequency();
  display_trx_state();
}

void display_frequency() {
  lcd_setcursor(0,1);
  lcd_freq(trx_dial_freq());
  lcd_setcursor(6,2);
  switch(trx_vfo_mode()) {
    case VFO_MODE_A: lcd_data('A'); break;
    case VFO_MODE_B: lcd_data('B'); break;
    case VFO_MODE_SPLIT: lcd_data('S'); break;
  }
}

void display_smeter(uint8_t s) {
  if (s > 5)
    s = 5;

  lcd_setcursor(0, 2);
  for (uint8_t i=0; i<s; i++)
    lcd_data(i);
  for (uint8_t i=s; i<5; i++)
    lcd_data(' ');
}

void display_voltage(uint8_t v) {
  lcd_setcursor(0, 2);
  uint8_t a = v/100;
  uint8_t b = (v%100)/10;
  uint8_t c = v%10;
  if (a) lcd_data('0'+a);
  else lcd_data(' ');
  lcd_data('0'+b);
  lcd_data('.');
  lcd_data('0'+c);
  lcd_data('V');
}

void display_temp(uint16_t v) {
  lcd_setcursor(0, 2);
  // sign
  uint8_t n = (v<0) ? '-' : ' ';
  // ABS
  v = (v<0) ? -v : v;
  v /= 10;
  if (v>99)
    v = 99;
  // digits
  uint8_t a = v/10;
  uint8_t b = '0'+(v%10);
  a = (0!=a) ? ('0'+a) : ' ';
  lcd_data(n);
  lcd_data(a);
  lcd_data(b);
  lcd_data(0xdf);
  lcd_data('C');
}

void display_menu(MenuState state);
void display_menu_rit();
void display_menu_step();
void display_menu_vfo();
void display_menu_band();
void display_menu_setup();
void display_menu_tx_enabled();
void display_menu_quickset();
void display_menu_key_type();
void display_menu_iambic_mode();
void display_menu_cw_speed();
void display_menu_cw_tone();
void display_menu_cw_level();
void display_menu_cw_text();
void display_menu_clear_cw_text();
void display_menu_meter();
void display_menu_tx_hold();
void display_menu_greet();
void display_menu_rot_type();
void display_menu_version();
void display_menu_sideband();
void display_menu_pll_correction();
void display_menu_reset();


void display_menu(MenuState state) {
  lcd_hidecursor();
  switch (state) {
  case MENU_RIT:
  case MENU_SET_RIT:
    display_menu_rit();
    break;
  case MENU_STEP:
  case MENU_SET_STEP:
    display_menu_step();
    break;
  case MENU_VFO:
  case MENU_SET_VFO:
    display_menu_vfo();
    break;
  case MENU_BAND:
  case MENU_SET_BAND:
    display_menu_band();
    break;
  case MENU_SETUP:
    display_menu_setup();
    break;
  case MENU_QUICK_SET:
  case MENU_SET_QUICK_SET:
    display_menu_quickset();
    break;
  case MENU_KEY_TYPE:
  case MENU_SET_KEY_TYPE:
    display_menu_key_type();
    break;
  case MENU_IAMBIC_MODE:
  case MENU_SET_IAMBIC_MODE:
    display_menu_iambic_mode();
    break;
  case MENU_CW_SPEED:
  case MENU_SET_CW_SPEED:
    display_menu_cw_speed();
    break;
  case MENU_CW_TONE:
  case MENU_SET_CW_TONE:
    display_menu_cw_tone();
    break;
  case MENU_CW_LEVEL:
  case MENU_SET_CW_LEVEL:
    display_menu_cw_level();
    break;
  case MENU_CW_TEXT:
  case MENU_SET_CW_TEXT:
  case MENU_SET_CW_TEXT_CHAR:
    display_menu_cw_text();
    break;
  case MENU_CLEAR_CW_TEXT:
  case MENU_CLEAR_CW_TEXT_NO:
  case MENU_CLEAR_CW_TEXT_YES:
    display_menu_clear_cw_text();
    break;
  case MENU_METER:
  case MENU_SET_METER:
    display_menu_meter();
    break;
  case MENU_TX_HOLD:
  case MENU_SET_TX_HOLD:
    display_menu_tx_hold();
    break;
  case MENU_TX_ENABLE:
  case MENU_SET_TX_ENABLE:
    display_menu_tx_enabled();
    break;
  case MENU_GREET:
  case MENU_SET_GREET:
  case MENU_SET_GREET_CHAR:
    display_menu_greet();
    break;
  case MENU_ROT_TYPE:
  case MENU_SET_ROT_TYPE:
    display_menu_rot_type();
    break;
  case MENU_VERSION:
    display_menu_version();
    break;
  case MENU_SIDEBAND:
  case MENU_SET_SIDEBAND:
    display_menu_sideband();
    break;
  case MENU_PLL_CORRECTION:
  case MENU_SET_PLL_CORRECTION:
    display_menu_pll_correction();
    break;
  case MENU_RESET:
  case MENU_RESET_DONE:
    display_menu_reset();
    break;
  }
}


void display_menu_rit() {
  lcd_string("RIT:");
  if (MENU_SET_RIT == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  int8_t t = trx_rit();
  int8_t neg = ((t<0) ? '-' : '+');
  t = ((t<0) ? -t : t);
  uint8_t tc = t/100; t %= 100;
  uint8_t td = t/10;  t %= 10;
  uint8_t tu = (t ? ('0'+t) : ' ');
  tc = (tc ? ('0'+tc) : ' ');
  td = (td ? ('0'+td) : ' ');
  char buffer[8] = {neg,tc,td,tu,'0','H','z',0};
  lcd_setcursor(1,2);
  lcd_string(buffer);
}

void display_menu_step() {
  lcd_string("Step:");
  if (MENU_SET_STEP == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }

  switch (trx_tune_step()) {
    case TRX_STEP_10:
      lcd_setcursor(4,2);
      lcd_string("10Hz");
      break;
    case TRX_STEP_25:
      lcd_setcursor(4,2);
      lcd_string("25Hz");
      break;
    case TRX_STEP_50:
      lcd_setcursor(4,2);
      lcd_string("50Hz");
      break;
    case TRX_STEP_100:
      lcd_setcursor(3,2);
      lcd_string("100Hz");
      break;
    case TRX_STEP_250:
      lcd_setcursor(3,2);
      lcd_string("250Hz");
      break;
    case TRX_STEP_500:
      lcd_setcursor(3,2);
      lcd_string("500Hz");
      break;
    case TRX_STEP_1k:
      lcd_setcursor(4,2);
      lcd_string("1kHz");
      break;
    case TRX_STEP_2_5k:
      lcd_setcursor(2,2);
      lcd_string("2.5kHz");
      break;
    case TRX_STEP_5k:
      lcd_setcursor(4,2);
      lcd_string("5kHz");
      break;
    case TRX_STEP_10k:
      lcd_setcursor(3,2);
      lcd_string("10kHz");
      break;
  }
}

void display_menu_vfo() {
  lcd_string("VFO:");
  if (MENU_SET_VFO == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  switch (trx_vfo_mode()) {
    case VFO_MODE_A:
      lcd_setcursor(7,2);
      lcd_string("A");
      break;
    case VFO_MODE_B:
      lcd_setcursor(7,2);
      lcd_string("B");
      break;
    case VFO_MODE_SPLIT:
      lcd_setcursor(3,2);
      lcd_string("Split");
      break;
  }
}

void display_menu_band() {
  lcd_string("Band:");
  if (MENU_SET_BAND == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }

  switch (trx_band()) {
    case BAND_80:
      lcd_setcursor(5,2);
      lcd_string("80m");
      break;
    case BAND_60:
      lcd_setcursor(5,2);
      lcd_string("60m");
      break;
    case BAND_40:
      lcd_setcursor(5,2);
      lcd_string("40m");
      break;
    case BAND_30:
      lcd_setcursor(5,2);
      lcd_string("30m");
      break;
    case BAND_20:
      lcd_setcursor(5,2);
      lcd_string("20m");
      break;
    case BAND_17:
      lcd_setcursor(5,2);
      lcd_string("17m");
      break;
    case BAND_15:
      lcd_setcursor(5,2);
      lcd_string("15m");
      break;
    case BAND_12:
      lcd_setcursor(5,2);
      lcd_string("12m");
      break;
    case BAND_10:
      lcd_setcursor(5,2);
      lcd_string("10m");
      break;
  }
}

void display_menu_setup() {
  lcd_string("Setup ..");
}

void display_menu_tx_enabled() {
  lcd_string("TX en.:");
  if (MENU_SET_TX_ENABLE == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  if (trx_tx_enabled()) {
    lcd_setcursor(6,2);
    lcd_string("ON");
  } else {
    lcd_setcursor(5,2);
    lcd_string("OFF");
  }
}

void display_menu_quickset() {
  lcd_string("QuickSet");
  if (MENU_SET_QUICK_SET == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  switch (trx_quickset()) {
  case TRX_QS_NONE:
    lcd_setcursor(4,2);
    lcd_string("None");
    break;
  case TRX_QS_RIT:
    lcd_setcursor(5,2);
    lcd_string("RIT");
    break;
  case TRX_QS_STEP:
    lcd_setcursor(4,2);
    lcd_string("Step");
    break;
  case TRX_QS_SPEED:
    lcd_setcursor(3,2);
    lcd_string("Speed");
    break;
  case TRX_QS_BAND:
    lcd_setcursor(4,2);
    lcd_string("Band");
    break;
  }
}

void display_menu_key_type() {
  lcd_string("CW key:");
  if (MENU_SET_KEY_TYPE == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  switch (trx_keyer_type()) {
  case KEYER_TYPE_STRAIGHT:
    lcd_setcursor(4,2);
    lcd_string("str.");
    break;
  case KEYER_TYPE_PADDLE:
    lcd_setcursor(2,2);
    lcd_string("paddle");
    break;
  case KEYER_TYPE_IAMBIC:
    lcd_setcursor(2,2);
    lcd_string("iambic");
    break;
  }
}

void display_menu_iambic_mode() {
  lcd_string("Iambic:");
  if (MENU_SET_IAMBIC_MODE == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  switch (trx_keyer_iambic_mode()) {
  case KEYER_IAMBIC_A:
    lcd_setcursor(6,2);
    lcd_string("A");
    break;
  case KEYER_IAMBIC_B:
    lcd_setcursor(6,2);
    lcd_string("B");
    break;
  }
}

void display_menu_cw_speed() {
  lcd_string("CW spe.:");
  if (MENU_SET_CW_SPEED == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  uint8_t speed = keyer_speed_wpm();
  uint8_t h = speed/10, l = speed%10;
  char buffer[7] = {'0'+h,'0'+l,' ','W','P','M',0};
  lcd_setcursor(2,2);
  lcd_string(buffer);
}

void display_menu_cw_tone() {
  lcd_string("CW tone:");
  if (MENU_SET_CW_TONE == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  uint16_t t = trx_cw_tone();
  uint8_t tc = t/100; t %= 100;
  uint8_t td = t/10;  t %= 10;
  char buffer[7] = {'0'+tc,'0'+td,'0'+t,' ','H','z', 0};
  lcd_setcursor(2,2);
  lcd_string(buffer);
}

void display_menu_cw_level() {
  lcd_string("CW lev.:");
  if (MENU_SET_CW_LEVEL == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  uint16_t t = trx_cw_level();
  uint8_t tc = t/100; t %= 100;
  uint8_t td = t/10;  t %= 10;
  char buffer[4] = {'0'+tc,'0'+td,'0'+t,0};
  lcd_setcursor(5,2);
  lcd_string(buffer);
}

void display_menu_cw_text() {
  lcd_string("CW Text:");
  if (MENU_CW_TEXT == menu_state()) {
    lcd_setcursor(0,2);
    for (uint8_t i=0; i<8; i++)
      lcd_data(keyer_sym2char(trx_cwtext()[i]));
  } else {
    lcd_setcursor(0,2);
    if (menu_cursor() < 4) {
      // left part: >0123456
      lcd_data(0x7E);
      for (uint8_t i=0; i<7; i++)
        lcd_data(keyer_sym2char(trx_cwtext()[i]));
      lcd_setcursor(menu_cursor()+1, 2);
    } else if (menu_cursor() > TRX_CWTEXT_MAXLEN-5) {
      // right part: 3456789<
      for (uint8_t i=0; i<7; i++)
        lcd_data(keyer_sym2char(trx_cwtext()[TRX_CWTEXT_MAXLEN-7+i]));
      lcd_data(0x7F);
      lcd_setcursor(7-TRX_CWTEXT_MAXLEN-menu_cursor(), 2);
    } else {
      // middle part: 01234567
      for (uint8_t i=0; i<7; i++)
        lcd_data(keyer_sym2char(trx_cwtext()[menu_cursor()-4+i]));
      lcd_setcursor(4,2);
    }
    if (MENU_SET_CW_TEXT == menu_state()) {
      lcd_showcursor();
    } else if (MENU_SET_CW_TEXT_CHAR == menu_state()) {
      lcd_blinkcursor();
    }
  }
}

void display_menu_clear_cw_text() {
  lcd_string("Clr CWT?");
  if (MENU_CLEAR_CW_TEXT_YES == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
    lcd_setcursor(5,2);
    lcd_string("Yes");
  } else if (MENU_CLEAR_CW_TEXT_NO == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
    lcd_setcursor(6,2);
    lcd_string("No");
  }
}

void display_menu_meter() {
  lcd_string("Meter:");
  if (MENU_SET_METER == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  switch(trx_meter_type()) {
    case METER_NONE:
      lcd_setcursor(4,2);
      lcd_string("Off");
      break;
    case METER_VOLTAGE:
      lcd_setcursor(2,2);
      lcd_string("Volt.");
      break;
    case METER_TEMP:
      lcd_setcursor(2,2);
      lcd_string("Temp.");
      break;
  }
}

void display_menu_tx_hold() {
  lcd_string("TX hold:");
  if (MENU_SET_TX_HOLD == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  lcd_setcursor(3,2);
  lcd_print_uint16(trx_tx_hold(), 4);
  lcd_string("ms");
}

void display_menu_greet() {
  lcd_string("Greet:");
  lcd_setcursor(0,2);
  for (uint8_t i=0; i<8; i++)
    lcd_data(trx_greet()[i]);
  if (MENU_SET_GREET == menu_state()) {
    lcd_setcursor(menu_cursor(),2);
    lcd_showcursor();
  } else if (MENU_SET_GREET_CHAR == menu_state()) {
    lcd_setcursor(menu_cursor(),2);
    lcd_blinkcursor();
  }
}

void display_menu_rot_type() {
  lcd_string("Enc.Type");
  lcd_setcursor(0,2);
  if (MENU_SET_ROT_TYPE == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  switch (trx_rot_type()) {
  case ROT_TYPE_A:
    lcd_setcursor(6,2);
    lcd_data('A');
    break;
  case ROT_TYPE_A_Rev:
    lcd_setcursor(2,2);
    lcd_string("Rev. A");
    break;
  case ROT_TYPE_B:
    lcd_setcursor(6,2);
    lcd_data('B');
    break;
  case ROT_TYPE_B_Rev:
    lcd_setcursor(2,2);
    lcd_string("Rev. B");
    break;
  }
}

void display_menu_version() {
  lcd_string("Version:");
  lcd_setcursor(5,2);
  lcd_string(VERSION_STRING);
}

void display_menu_sideband() {
  lcd_string("Sideband");
  if (MENU_SET_SIDEBAND == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  lcd_setcursor(5,2);
  if (TRX_USB == trx_sideband())
    lcd_string("USB");
  else
    lcd_string("LSB");
}

void display_menu_pll_correction() {
  lcd_string("PLL cor:");
  if (MENU_SET_PLL_CORRECTION == menu_state()) {
    lcd_setcursor(0,2);
    lcd_data(0x7E);
  }
  lcd_setcursor(1,2);
  lcd_print_pllcorr(trx_pll_correction());
}

void display_menu_reset() {
  lcd_string("Reset?");
  if (MENU_RESET == menu_state()) {
    lcd_setcursor(0,2);
    lcd_string("Lng Prss");
  } else {
    lcd_setcursor(0,2);
    lcd_string(" Reboot!");
  }
}

