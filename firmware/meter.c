#include "meter.h"
#include "trx.h"
#include "display.h"

#define S_METER_COUNT  64

volatile uint8_t _meter_update = 0;
volatile uint8_t _meter_count = 0;
volatile uint16_t _meter_value = 0;
volatile uint16_t _meter_value_max = 0;
volatile uint16_t _meter_value_min = 1024;
volatile MeterType _meter_type = METER_NONE;

void meter_init(MeterType type) {
  DIDR0 |= (1<<ADC0D);
  meter_set_type(type);
  ADCSRA = ( (1<<ADIE) | (1<<ADATE) | (1<<ADEN) |
             (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) );
  ADCSRB = ( (0<<ACME) | (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0) );
}

void meter_set_type(MeterType type) {
  _meter_type = type;
  if (METER_TEMP == _meter_type) {
    // Select ADC8 (internal temp sensor)
    ADMUX  = ( (1<<REFS1) | (1<<REFS0) | (0<<ADLAR) |
               (1<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0) );
  } else {
    // Select ADC0 for input
    ADMUX  = ( (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) |
               (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0) );
  }
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

  if (TRX_RX != trx_state())
    return;
  else if (METER_VOLTAGE == _meter_type)
    display_voltage(_meter_value);
  else if (METER_TEMP == _meter_type)
    display_temp(_meter_value);
}

ISR(ADC_vect) {
  uint16_t v = ADC;
  if (METER_VOLTAGE == _meter_type) {
    int32_t temp = v;
    // Assuming voltage divider -> 47k + 4.7k to GND.
    temp *= 554; temp /= 1024;
    _meter_value = temp;
  } else if (METER_TEMP == _meter_type) {
    // Vref = 1.1V, 314mV @ 25C, 1mV/C
    int32_t temp = v; temp -= 292; // (== -314mV)
    // temp in 100 mC
    temp = 250 + (1000*temp)/931;
    _meter_value = temp;
  }
}
