#ifndef __TRX_H__
#define __TRX_H__

#include <avr/io.h>
#include <stdint.h>
#include "band.h"
#include "keyer.h"

#define TRX_TX_PORT PORTD
#define TRX_TX_DDR  DDRD
#define TRX_TX_BIT  PD7

#define TRX_KEY_PORT PORTB
#define TRX_KEY_DDR  DDRB
#define TRX_KEY_BIT  PB0

typedef enum {
  TRX_RX,
  TRX_TX,
  TRX_HOLD_TX,
  TRX_MENU
} TRXState;

typedef enum {
  TRX_STEP_10,
  TRX_STEP_25,
  TRX_STEP_50,
  TRX_STEP_100,
  TRX_STEP_250,
  TRX_STEP_500,
  TRX_STEP_1k,
  TRX_STEP_2_5k,
  TRX_STEP_5k,
  TRX_STEP_10k
} TRXStepSize;

/** VFO mode for the TRX. */
typedef enum {
  VFO_MODE_A,
  VFO_MODE_B,
  VFO_MODE_SPLIT
} VFOMode;


void trx_init();

void trx_tx();
void trx_rx();
VFOMode  trx_vfo_mode();
void trx_set_vfo_mode(VFOMode mode);
TRXState trx_state();
void trx_set_state(TRXState state);

void trx_tune(int8_t delta);
uint32_t trx_dial_freq();
void trx_set_vfo();
TRXStepSize trx_tune_step();
void trx_set_tune_step(TRXStepSize step);
Band trx_band();
void trx_set_band(Band band);
KeyerMode trx_cw_mode();
void trx_set_cw_mode(KeyerMode mode);
uint16_t trx_cw_tone();
void trx_set_cw_tone(uint16_t freq);
uint8_t trx_cw_level();
void trx_set_cw_level(uint8_t level);
uint8_t trx_cw_speed();
void trx_set_cw_speed(uint8_t idx);
uint16_t trx_tx_hold();
void trx_set_tx_hold(uint16_t delay);
uint8_t trx_tx_enabled();
void trx_set_tx_enabled(uint8_t enabled);
int32_t trx_pll_correction();
void trx_set_pll_correction(int32_t pptm);

void trx_poll();

#endif // __TRX_H__
