/*
 * si5351.c - Si5351 library for avr-gcc
 *
 * Copyright (C) 2014 Jason Milldrum <milldrum@gmail.com>
 *
 * Some tuning algorithms derived from clk-si5351.c in the Linux kernel.
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Rabeeh Khoury <rabeeh@solid-run.com>
 *
 * rational_best_approximation() derived from lib/rational.c in
 * the Linux kernel.
 * Copyright (C) 2009 emlix GmbH, Oskar Schirmer <oskar@scara.com>
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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <util/twi.h>

#include "si5351.h"
#include "i2c.h"

int32_t ref_correction = 0;
uint32_t plla_freq = 0;
uint32_t pllb_freq = 0;

struct Si5351Status dev_status;
struct Si5351IntStatus dev_int_status;

void si5351_reset();
void si5351_pll_reset(enum si5351_pll target_pll);

/******************************/
/* Suggested public functions */
/******************************/

/*
 * si5351_init(void)
 *
 * Call this to initialize I2C communications and get the
 * Si5351 ready for use.
 */
uint8_t si5351_init(int32_t refcorr)
{
	i2c_init();

	/* Set crystal load capacitance */
	if (si5351_write(SI5351_CRYSTAL_LOAD, SI5351_CRYSTAL_LOAD_8PF))
    return 1;

	/* Get the correction factor from EEPROM */
  ref_correction = refcorr;

  //si5351_reset();

  return 0;
}

/*
 * Resets the PLLs, outputs etc.
 */
void si5351_reset() {
  // Initialize the CLK outputs according to flowchart in datasheet
	// First, turn them off
	si5351_write(16, 0x80);
	si5351_write(17, 0x80);
	si5351_write(18, 0x80);
	si5351_write(19, 0x80);
	si5351_write(20, 0x80);
	si5351_write(21, 0x80);
	si5351_write(22, 0x80);
	si5351_write(23, 0x80);

	// Turn the clocks back on...
	si5351_write(16, 0x0c);
	si5351_write(17, 0x0c);
	si5351_write(18, 0x0c);
	si5351_write(19, 0x0c);
	si5351_write(20, 0x0c);
	si5351_write(21, 0x0c);
	si5351_write(22, 0x0c);
	si5351_write(23, 0x0c);

	// Set PLLA to 800 MHz for automatic tuning
	si5351_set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
	si5351_set_pll(SI5351_PLL_FIXED, SI5351_PLLB);

	si5351_set_ms_source(SI5351_CLK0, SI5351_PLLA);
	si5351_set_ms_source(SI5351_CLK1, SI5351_PLLB);
	si5351_set_ms_source(SI5351_CLK2, SI5351_PLLB);

  si5351_clock_enable(SI5351_CLK0, 0);
  si5351_clock_enable(SI5351_CLK1, 0);
  si5351_clock_enable(SI5351_CLK2, 0);

  // Then reset the PLLs
	si5351_pll_reset(SI5351_PLLA);
	si5351_pll_reset(SI5351_PLLB);
}

void si5351_pll_reset(enum si5351_pll target_pll)
{
  switch (target_pll) {
    case SI5351_PLLA: si5351_write(SI5351_PLL_RESET, SI5351_PLL_RESET_A); break;
    case SI5351_PLLB: si5351_write(SI5351_PLL_RESET, SI5351_PLL_RESET_B); break;
  }
}


/*
 * si5351_set_freq(uint32_t freq, uint32_t pll_freq, enum si5351_clock output)
 *
 * Sets the clock frequency of the specified CLK output
 *
 * freq - Output frequency in Hz
 * pll_freq - Frequency of the PLL driving the Multisynth
 *   Use a 0 to have the function choose a PLL frequency
 * clk - Clock output
 *   (use the si5351_clock enum)
 */
void si5351_set_freq(uint32_t freq, uint32_t pll_freq, enum si5351_clock clk)
{
	struct Si5351RegSet ms_reg;//, pll_reg;
	enum si5351_pll target_pll;

	/* Calculate the synth parameters
	 * If pll_freq is 0, let the algorithm pick a PLL frequency */
	if (0 == pll_freq) {
		pll_freq = multisynth_calc(freq, &ms_reg);
	} else {
		multisynth_recalc(freq, pll_freq, &ms_reg);
	}

	/* Determine which PLL to use
	 * CLK0 gets PLLA, CLK1 gets PLLB
	 * CLK2 gets PLLB if necessary
	 * Only good for Si5351A3 variant at the moment */
	if (clk == SI5351_CLK0) {
		target_pll = SI5351_PLLA;
		plla_freq = pll_freq;
	} else if (clk == SI5351_CLK1) {
		target_pll = SI5351_PLLB;
		pllb_freq = pll_freq;
	} else {
		/* need to account for CLK2 set before CLK1 */
		if (pllb_freq == 0) {
			target_pll = SI5351_PLLB;
			pllb_freq = pll_freq;
		} else {
			target_pll = SI5351_PLLB;
			pll_freq = pllb_freq;
			multisynth_recalc(freq, pll_freq, &ms_reg);
		}
	}

  si5351_set_pll(pll_freq, target_pll);

	/* Now the multisynth parameters */
  uint8_t params[SI5351_PARAMETERS_LENGTH];
	uint8_t i = 0;
	uint8_t temp;

	/* Registers 42-43 */
	temp = (uint8_t)((ms_reg.p3 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(ms_reg.p3  & 0xFF);
	params[i++] = temp;

	/* Register 44
	 * TODO: add code for output divider */
	temp = (uint8_t)((ms_reg.p1 >> 16) & 0x03);
  //uint8_t reg_val; si5351_read((SI5351_CLK0_PARAMETERS + 2) + (clk * 8), &reg_val);
  //reg_val &= ~(0x03);
  //temp = reg_val | ((uint8_t)((ms_reg.p1 >> 16) & 0x03));
	params[i++] = temp;

	/* Registers 45-46 */
	temp = (uint8_t)((ms_reg.p1 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(ms_reg.p1  & 0xFF);
	params[i++] = temp;

	/* Register 47 */
	temp = (uint8_t)((ms_reg.p3 >> 12) & 0xF0);
	temp += (uint8_t)((ms_reg.p2 >> 16) & 0x0F);
	params[i++] = temp;

	/* Registers 48-49 */
	temp = (uint8_t)((ms_reg.p2 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(ms_reg.p2  & 0xFF);
	params[i++] = temp;

	/* Write the parameters */
	switch(clk)
	{
	case SI5351_CLK0:
		si5351_write_bulk(SI5351_CLK0_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	case SI5351_CLK1:
		si5351_write_bulk(SI5351_CLK1_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	case SI5351_CLK2:
		si5351_write_bulk(SI5351_CLK2_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	case SI5351_CLK3:
		si5351_write_bulk(SI5351_CLK3_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	case SI5351_CLK4:
		si5351_write_bulk(SI5351_CLK4_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	case SI5351_CLK5:
		si5351_write_bulk(SI5351_CLK5_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	case SI5351_CLK6:
		si5351_write_bulk(SI5351_CLK6_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	case SI5351_CLK7:
		si5351_write_bulk(SI5351_CLK7_PARAMETERS, i, params);
		si5351_set_ms_source(clk, target_pll);
		break;
	}
}

/*
 * si5351_set_pll(uint32_t pll_freq, enum si5351_pll target_pll)
 *
 * Set the specified PLL to a specific oscillation frequency
 *
 * pll_freq - Desired PLL frequency
 * target_pll - Which PLL to set
 *     (use the si5351_pll enum)
 */
void si5351_set_pll(uint32_t pll_freq, enum si5351_pll target_pll)
{
	struct Si5351RegSet pll_reg;

	pll_calc(pll_freq, &pll_reg, ref_correction);

	/* Derive the register values to write */

	/* Prepare an array for parameters to be written to */
	uint8_t params[SI5351_PARAMETERS_LENGTH];
	uint8_t i = 0;
	uint8_t temp;

	/* Registers 26-27 */
	temp = ((pll_reg.p3 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(pll_reg.p3  & 0xFF);
	params[i++] = temp;

	/* Register 28 */
	temp = (uint8_t)((pll_reg.p1 >> 16) & 0x03);
	params[i++] = temp;

	/* Registers 29-30 */
	temp = (uint8_t)((pll_reg.p1 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(pll_reg.p1  & 0xFF);
	params[i++] = temp;

	/* Register 31 */
	temp = (uint8_t)((pll_reg.p3 >> 12) & 0xF0);
	temp += (uint8_t)((pll_reg.p2 >> 16) & 0x0F);
	params[i++] = temp;

	/* Registers 32-33 */
	temp = (uint8_t)((pll_reg.p2 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(pll_reg.p2  & 0xFF);
	params[i++] = temp;

	/* Write the parameters */
	if(target_pll == SI5351_PLLA) {
		si5351_write_bulk(SI5351_PLLA_PARAMETERS, i, params);
	} else if(target_pll == SI5351_PLLB) {
		si5351_write_bulk(SI5351_PLLB_PARAMETERS, i, params);
	}
}

/*
 * si5351_clock_enable(enum si5351_clock clk, uint8_t enable)
 *
 * Enable or disable a chosen clock
 * clk - Clock output
 *   (use the si5351_clock enum)
 * enable - Set to 1 to enable, 0 to disable
 */
void si5351_clock_enable(enum si5351_clock clk, uint8_t enable)
{
	uint8_t reg_val;

	if(si5351_read(SI5351_OUTPUT_ENABLE_CTRL, &reg_val) != 0) {
		return;
	}

	if(enable == 1) {
		reg_val &= ~(1<<(uint8_t)clk);
	} else {
		reg_val |= (1<<(uint8_t)clk);
	}

	si5351_write(SI5351_OUTPUT_ENABLE_CTRL, reg_val);
}

/*
 * si5351_drive_strength(enum si5351_clock clk, enum si5351_drive drive)
 *
 * Sets the drive strength of the specified clock output
 *
 * clk - Clock output
 *   (use the si5351_clock enum)
 * drive - Desired drive level
 *   (use the si5351_drive enum)
 */
void si5351_drive_strength(enum si5351_clock clk, enum si5351_drive drive)
{
	uint8_t reg_val;
	const uint8_t mask = 0x03;

	if (si5351_read(SI5351_CLK0_CTRL + (uint8_t)clk, &reg_val) != 0) {
		return;
	}

	switch(drive)
	{
	case SI5351_DRIVE_2MA:
		reg_val &= ~(mask);
		reg_val |= 0x00;
		break;
	case SI5351_DRIVE_4MA:
		reg_val &= ~(mask);
		reg_val |= 0x01;
		break;
	case SI5351_DRIVE_6MA:
		reg_val &= ~(mask);
		reg_val |= 0x02;
		break;
	case SI5351_DRIVE_8MA:
		reg_val &= ~(mask);
		reg_val |= 0x03;
		break;
	default:
		break;
	}

	si5351_write(SI5351_CLK0_CTRL + (uint8_t)clk, reg_val);
}

/*
 * si5351_update_status(void)
 *
 * Call this to update the status structs, then access them
 * via the dev_status and dev_int_status global variables.
 *
 * See the header file for the struct definitions. These
 * correspond to the flag names for registers 0 and 1 in
 * the Si5351 datasheet.
 */
void si5351_update_status(void)
{
	si5351_update_sys_status(&dev_status);
	si5351_update_int_status(&dev_int_status);
}

/*
 * si5351_set_correction(int32_t corr)
 *
 * Use this to set the oscillator correction factor to
 * EEPROM. This value is a signed 32-bit integer of the
 * parts-per-10 million value that the actual oscillation
 * frequency deviates from the specified frequency.
 *
 * The frequency calibration is done as a one-time procedure.
 * Any desired test frequency within the normal range of the
 * Si5351 should be set, then the actual output frequency
 * should be measured as accurately as possible. The
 * difference between the measured and specified frequencies
 * should be calculated in Hertz, then multiplied by 10 in
 * order to get the parts-per-10 million value.
 *
 * Since the Si5351 itself has an intrinsic 0 PPM error, this
 * correction factor is good across the entire tuning range of
 * the Si5351. Once this calibration is done accurately, it
 * should not have to be done again for the same Si5351 and
 * crystal. The library will read the correction factor from
 * EEPROM during initialization for use by the tuning
 * algorithms.
 */
void si5351_set_correction(int32_t corr)
{
	ref_correction = corr;
}


/*******************************
 * Suggested private functions *
 *******************************/

/*
 * Calculate best rational approximation for a given fraction
 * taking into account restricted register size, e.g. to find
 * appropriate values for a pll with 5 bit denominator and
 * 8 bit numerator register fields, trying to set up with a
 * frequency ratio of 3.1415, one would say:
 *
 * rational_best_approximation(31415, 10000,
 *              (1 << 8) - 1, (1 << 5) - 1, &n, &d);
 *
 * you may look at given_numerator as a fixed point number,
 * with the fractional part size described in given_denominator.
 *
 * for theoretical background, see:
 * http://en.wikipedia.org/wiki/Continued_fraction
 */
void rational_best_approximation(
        uint32_t given_numerator, uint32_t given_denominator,
        uint32_t max_numerator, uint32_t max_denominator,
        uint32_t *best_numerator, uint32_t *best_denominator)
{
	uint32_t n, d, n0, d0, n1, d1;
	n = given_numerator;
	d = given_denominator;
	n0 = d1 = 0;
	n1 = d0 = 1;
	for (;;) {
		uint32_t t, a;
		if ((n1 > max_numerator) || (d1 > max_denominator)) {
			n1 = n0;
			d1 = d0;
			break;
		}
		if (d == 0)
			break;
		t = d;
		a = n / d;
		d = n % d;
		n = t;
		t = n0 + a * n1;
		n0 = n1;
		n1 = t;
		t = d0 + a * d1;
		d0 = d1;
		d1 = t;
	}
	*best_numerator = n1;
	*best_denominator = d1;
}

uint32_t pll_calc(uint32_t freq, struct Si5351RegSet *reg, int32_t correction)
{
	uint32_t ref_freq = SI5351_XTAL_FREQ;
	uint32_t rfrac, denom, a, b, c, p1, p2, p3;
	uint64_t lltmp;

	/* Factor calibration value into nominal crystal frequency */
	/* Measured in parts-per-ten million */
  ref_freq += (uint32_t)((double)(correction / 10000000.0) * (double)ref_freq);

	/* PLL bounds checking */
	if (freq < SI5351_PLL_VCO_MIN)
		freq = SI5351_PLL_VCO_MIN;
	if (freq > SI5351_PLL_VCO_MAX)
		freq = SI5351_PLL_VCO_MAX;

	/* Determine integer part of feedback equation */
	a = freq / ref_freq;

	if (a < SI5351_PLL_A_MIN)
		freq = ref_freq * SI5351_PLL_A_MIN;
	if (a > SI5351_PLL_A_MAX)
		freq = ref_freq * SI5351_PLL_A_MAX;

	/* find best approximation for b/c = fVCO mod fIN */
	denom = 1000L * 1000L;
	lltmp = freq % ref_freq;
	lltmp *= denom;
	do_div(lltmp, ref_freq);
	rfrac = (uint32_t)lltmp;

	b = 0;
	c = 1;
	if (rfrac)
		rational_best_approximation(rfrac, denom,
				    SI5351_PLL_B_MAX, SI5351_PLL_C_MAX, &b, &c);

	/* calculate parameters */
	p3  = c;
	p2  = (128 * b) % c;
	p1  = 128 * a;
	p1 += (128 * b / c);
	p1 -= 512;

	/* recalculate rate by fIN * (a + b/c) */
	lltmp  = ref_freq;
	lltmp *= b;
	do_div(lltmp, c);

	freq  = (uint32_t)lltmp;
	freq += ref_freq * a;

	reg->p1 = p1;
	reg->p2 = p2;
	reg->p3 = p3;

	return freq;
}

uint32_t multisynth_calc(uint32_t freq, struct Si5351RegSet *reg)
{
	uint32_t pll_freq;
	uint64_t lltmp;
	uint32_t a, b, c, p1, p2, p3;
	uint8_t divby4;

	/* Multisynth bounds checking */
	if (freq > SI5351_MULTISYNTH_MAX_FREQ)
		freq = SI5351_MULTISYNTH_MAX_FREQ;
	if (freq < SI5351_MULTISYNTH_MIN_FREQ)
		freq = SI5351_MULTISYNTH_MIN_FREQ;

	divby4 = 0;
	if (freq > SI5351_MULTISYNTH_DIVBY4_FREQ)
		divby4 = 1;

	/* Find largest integer divider for max */
	/* VCO frequency and given target frequency */
	if (divby4 == 0) {
		lltmp = SI5351_PLL_VCO_MAX;
		do_div(lltmp, freq);
		a = (uint32_t)lltmp;
	}
	else
		a = 4;

	b = 0;
	c = 1;
	pll_freq = a * freq;

	/* Recalculate output frequency by fOUT = fIN / (a + b/c) */
	lltmp  = pll_freq;
	lltmp *= c;
	do_div(lltmp, a * c + b);
	freq  = (unsigned long)lltmp;

	/* Calculate parameters */
	if (divby4) {
		p3 = 1;
		p2 = 0;
		p1 = 0;
	} else {
		p3  = c;
		p2  = (128 * b) % c;
		p1  = 128 * a;
		p1 += (128 * b / c);
		p1 -= 512;
	}

	reg->p1 = p1;
	reg->p2 = p2;
	reg->p3 = p3;

	return pll_freq;
}

uint32_t multisynth_recalc(uint32_t freq, uint32_t pll_freq, struct Si5351RegSet *reg)
{
	uint64_t lltmp;
	uint32_t rfrac, denom, a, b, c, p1, p2, p3;
	uint8_t divby4;

	/* Multisynth bounds checking */
	if (freq > SI5351_MULTISYNTH_MAX_FREQ)
		freq = SI5351_MULTISYNTH_MAX_FREQ;
	if (freq < SI5351_MULTISYNTH_MIN_FREQ)
		freq = SI5351_MULTISYNTH_MIN_FREQ;

	divby4 = 0;
	if (freq > SI5351_MULTISYNTH_DIVBY4_FREQ)
		divby4 = 1;

	/* Determine integer part of feedback equation */
	a = pll_freq / freq;

	/* TODO: not sure this is correct */
	if (a < SI5351_MULTISYNTH_A_MIN)
		freq = pll_freq / SI5351_MULTISYNTH_A_MIN;
	if (a > SI5351_MULTISYNTH_A_MAX)
		freq = pll_freq / SI5351_MULTISYNTH_A_MAX;

	/* find best approximation for b/c */
	denom = 1000L * 1000L;
	lltmp = pll_freq % freq;
	lltmp *= denom;
	do_div(lltmp, freq);
	rfrac = (uint32_t)lltmp;

	b = 0;
	c = 1;
  if (rfrac) {
		rational_best_approximation(rfrac, denom,
				    SI5351_MULTISYNTH_B_MAX, SI5351_MULTISYNTH_C_MAX, &b, &c);
  }

	/* Recalculate output frequency by fOUT = fIN / (a + b/c) */
	lltmp  = pll_freq;
	lltmp *= c;
	do_div(lltmp, a * c + b);
	freq  = (unsigned long)lltmp;

	/* Calculate parameters */
	if (divby4) {
		p3 = 1;
		p2 = 0;
		p1 = 0;
	} else {
		p3  = c;
		p2  = (128 * b) % c;
		p1  = 128 * a;
		p1 += (128 * b / c);
		p1 -= 512;
	}

	reg->p1 = p1;
	reg->p2 = p2;
	reg->p3 = p3;

	return freq;
}

uint8_t si5351_write_bulk(uint8_t addr, uint8_t bytes, uint8_t *data)
{
	int i;

	i2c_start();
	if (i2c_status() != TW_START) {
		i2c_stop();
		return 1;
	}
	i2c_write(SI5351_BUS_BASE_ADDR);
	if (i2c_status() != TW_MT_SLA_ACK) {
		i2c_stop();
		return 1;
	}
	i2c_write(addr);
	if (i2c_status() != TW_MT_DATA_ACK) {
		i2c_stop();
		return 1;
	}

	for (i = 0; i < bytes; i++) {
    i2c_write(data[i]);
		if (i2c_status() != TW_MT_DATA_ACK) {
			i2c_stop();
			return 1;
		}
	}

	i2c_stop();
	return 0;
}

uint8_t si5351_write(uint8_t addr, uint8_t data)
{
	i2c_start();
	if(i2c_status() != TW_START) {
    i2c_stop();
    return 1;
	}
	i2c_write(SI5351_BUS_BASE_ADDR);
	if(i2c_status() != TW_MT_SLA_ACK) {
		i2c_stop();
		return 1;
	}
	i2c_write(addr);
	if(i2c_status() != TW_MT_DATA_ACK) {
		i2c_stop();
		return 1;
	}
	i2c_write(data);
	if(i2c_status() != TW_MT_DATA_ACK) {
		i2c_stop();
		return 1;
	}
	i2c_stop();
	return 0;
}

uint8_t si5351_read(uint8_t addr, uint8_t *data)
{
	i2c_start();
	if (i2c_status() != TW_START) {
		i2c_stop();
		return 1;
	}
	i2c_write(SI5351_BUS_BASE_ADDR);
	if (i2c_status() != TW_MT_SLA_ACK) {
		i2c_stop();
		return 1;
	}
	i2c_write(addr);
	if(i2c_status() != TW_MT_DATA_ACK) {
		i2c_stop();
		return 1;
	}

	i2c_start();
	if(i2c_status() != TW_REP_START) {
		i2c_stop();
		return 1;
	}
	i2c_write(SI5351_BUS_BASE_ADDR | TW_READ);
	if(i2c_status() != TW_MR_SLA_ACK) {
		i2c_stop();
		return 1;
	}
	*data = i2c_read_nack();
	if(i2c_status() != TW_MR_DATA_NACK) {
		i2c_stop();
		return 1;
	}
	i2c_stop();
	return 0;
}


void si5351_update_sys_status(struct Si5351Status *status)
{
	uint8_t reg_val = 0;

	if (si5351_read(SI5351_DEVICE_STATUS, &reg_val) != 0) {
		return;
	}

	/* Parse the register */
	status->SYS_INIT = (reg_val >> 7) & 0x01;
	status->LOL_B = (reg_val >> 6) & 0x01;
	status->LOL_A = (reg_val >> 5) & 0x01;
	status->LOS = (reg_val >> 4) & 0x01;
	status->REVID = reg_val & 0x03;
}

void si5351_update_int_status(struct Si5351IntStatus *int_status)
{
	uint8_t reg_val = 0;

	if (si5351_read(SI5351_DEVICE_STATUS, &reg_val) != 0) {
		return;
	}

	/* Parse the register */
	int_status->SYS_INIT_STKY = (reg_val >> 7) & 0x01;
	int_status->LOL_B_STKY = (reg_val >> 6) & 0x01;
	int_status->LOL_A_STKY = (reg_val >> 5) & 0x01;
	int_status->LOS_STKY = (reg_val >> 4) & 0x01;
}

void si5351_set_ms_source(enum si5351_clock clk, enum si5351_pll pll)
{
	uint8_t reg_val = 0x0c;
	//uint8_t reg_val2;

	//if (si5351_read(SI5351_CLK0_CTRL + (uint8_t)clk, &reg_val2) != 0) {
	//	return;
	//}

	if (pll == SI5351_PLLA) {
		reg_val &= ~(SI5351_CLK_PLL_SELECT);
	} else if(pll == SI5351_PLLB) {
		reg_val |= SI5351_CLK_PLL_SELECT;
	}
	si5351_write(SI5351_CLK0_CTRL + (uint8_t)clk, reg_val);
}
