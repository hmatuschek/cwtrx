#include "meter.h"
#include "trx.h"
#include "display.h"

#define S_METER_REF_mV 5000L
#define S_METER_MIN_mV 3500L
#define S_METER_MAX_mV 2500L

#define S_METER_OFFSET ((S_METER_MIN_mV*1024)/S_METER_REF_mV)

volatile uint8_t _meter_update = 0;
volatile uint16_t _meter_value = 0;


void meter_init() {
  DIDR0 |= (1<<ADC0D);
  ADMUX  = ( (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) |
             (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0) );
  ADCSRA = ( (1<<ADIE) | (1<<ADATE) | (1<<ADEN) |
             (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) );
  ADCSRB = ( (0<<ACME) | (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0) );
}

void meter_start() {
  ADCSRA |= (1<<ADSC);
}

uint8_t meter_sig() {
  return _meter_value;
}

void meter_update() {
  _meter_update = 1;
}

void meter_poll() {
  if (0 == _meter_update)
    return;
  _meter_update = 0;

  if (TRX_RX == trx_state()) {
    display_smeter(_meter_value);
  }
}

ISR(ADC_vect) {
  uint16_t v = ADC;
  if (v>S_METER_OFFSET)
    _meter_value = 0;
  else {
    int32_t temp = v;
    temp -= S_METER_OFFSET;
    temp *= 9*S_METER_REF_mV;
    temp /= (1024*(S_METER_MAX_mV-S_METER_MIN_mV));
    _meter_value = temp;
  }
}
