#include "trx.h"
#include "tone.h"
#include "rot.h"
#include "meter.h"

#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
  trx_init();

  sei();

  rot_button_up();
  rot_delta();
  meter_start();

  while (1) {
    trx_poll();
  }

  return 0;
}
