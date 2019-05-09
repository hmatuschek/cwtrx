#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <avr/io.h>

#define TRXMODE_BUTTON_PORT PORTB
#define TRXMODE_BUTTON_DDR  DDRB
#define TRXMODE_BUTTON_PIN  PINB
#define TRXMODE_BUTTON_BIT  PB4

typedef enum {
  TRX_SSB,
  TRX_CW
} TRXMode;


void buttons_init();

TRXMode button_mode();

#endif // __BUTTON_H__
