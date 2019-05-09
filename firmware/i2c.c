/*
 * i2c.c - I2C library for avr-gcc for devices with TWI
 *
 * Copyright (C) 2014 Jason Milldrum <milldrum@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <util/twi.h>
#include <avr/power.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "i2c.h"

void i2c_init(void)
{
	//set SCL to ~100 kHz for 20 MHz CPU clock
	TWSR = (0<<TWPS1) || (0<<TWPS0); /* Prescale /1 */
  // TWBR = 01011100
	TWBR = 0x5c;
}

void i2c_start(void)
{
  //enable I2C
	TWCR = ( (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) );
	while (!(TWCR & (1<<TWINT)));
}

void i2c_stop(void)
{
	TWCR = ((1<<TWINT) | (1<<TWSTO) | (0<<TWEN));
}

void i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = ( (1<<TWINT) | (1<<TWEN) );
	while (!(TWCR & (1<<TWINT)));
}

uint8_t i2c_read_ack(void)
{
	TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWEA) );
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t i2c_read_nack(void)
{
	TWCR = ( (1<<TWINT) | (1<<TWEN) );
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t i2c_status(void)
{
	return TW_STATUS;
}
