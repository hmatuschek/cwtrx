#ifndef __ROT_H__
#define __ROT_H__

#include <avr/io.h>
#include <inttypes.h>


#define ROT_PIN    PINC
#define ROT_PORT   PORTC
#define ROT_DDR    DDRC
#define ROT_A_BIT  PC1
#define ROT_B_BIT  PC2
#define ROT_M_BIT  PC3

void rot_init();

uint8_t rot_button_read();
uint8_t rot_button_up();
int8_t rot_delta();

void rot_tick();

#endif // __ROT_H__
