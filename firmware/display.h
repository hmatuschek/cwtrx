#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <inttypes.h>
#include "menu.h"

void display_update();
void display_trx_state();
void display_rx();
void display_frequency();
void display_smeter(uint8_t s);
void display_voltage(uint8_t v);
void display_soc_lion4s(uint8_t v);
void display_temp(uint16_t t);
void display_menu(MenuState state);

#endif // __DISPLAY_H__
