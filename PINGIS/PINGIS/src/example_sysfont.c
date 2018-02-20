/**
 * \file
 *
 * \brief Example application for GFX Monochrome System Font (sysfont)
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is an example application for the \ref gfx_mono_font. It will print a
 * string, with line break, on the display; Hello World!\\r\\nI'm bored...".
 *
 * \section files Main Files
 * - \ref example_sysfont.c
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_st7565r.h or conf_ssd1306.h
 * - \ref conf_sysfont.h
 * - \ref conf_usart_spi.h
 *
 * \section device_info Device Info
 * All AVR devices can be used.
 * This example has been tested with the following setup:
 * - XMEGA-A3BU Xplained
 * - XMEGA-C3 Xplained
 *
 * \section description Description of the example application
 * The example application will upon power up display two text strings on the
 * display; "My name is XXXXXXXX!" "And I'm board...".
 *
 * \section dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref gfx_mono
 * - \ref gfx_mono_font
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.atmel.com/">Atmel</a>.\n
 */

//Prototype my own functions:
static void drawLeftPaddle(int y);
static void drawRightPaddle(int y);
static void drawBall(int x, int y);
static void initialState(void);
static void clearBall(int x, int y);

//Interupt routine
static void myCallback(void);

//Global constants:
#define ballStartPosX			60
#define ballStartPosY			15
#define leftPaddleStartPos		0
#define rightPaddleStartPos		0 

int ballX = ballStartPosX;
int ballY = ballStartPosY;
int ballSpeedX = 1;


/**
 * \brief Main entry of example application
 */
int main(void)
{
	/**
	 * Starts off by initializing the system clock before configuring the
	 * board and the monochrome graphical system.
	 */
	board_init();
	pmic_init();
	sysclk_init();
	gfx_mono_init();
	
	tc_enable(&TCC0);
	tc_set_overflow_interrupt_callback(&TCC0, myCallback);
	tc_set_wgm(&TCC0, TC_WG_NORMAL);
	tc_write_period(&TCC0, 300);
	tc_set_overflow_interrupt_level(&TCC0, TC_INT_LVL_LO);
	
	cpu_irq_enable();
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1024_gc);
	
	
	
	
	gpio_set_pin_high(NHD_C12832A1Z_BACKLIGHT);
	
	initialState();

	while (true) {
		/* Intentionally left empty. */
	}
}

static void myCallback(void){
	clearBall(ballX,ballY);
	ballX += ballSpeedX;
	//ballY += ballSpeedY;
	drawBall(ballX,ballY);
}

static void initialState(void){
	drawBall(ballStartPosX,ballStartPosY);
	//drawLeftPaddle(leftPaddleStartPos);
	//drawRightPaddle(rightPaddleStartPos);
}

static void drawBall(int x, int y){
	gfx_mono_generic_draw_filled_circle(x, y, 2, GFX_PIXEL_SET, 0xFF);
}

static void drawLeftPaddle(int y){
	gfx_mono_generic_draw_vertical_line(0, y, 15, GFX_PIXEL_SET);
	gfx_mono_generic_draw_vertical_line(1, y, 15, GFX_PIXEL_SET);
}

static void drawRightPaddle(int y){
	gfx_mono_generic_draw_vertical_line(126, y, 15, GFX_PIXEL_SET);
	gfx_mono_generic_draw_vertical_line(127, y, 15, GFX_PIXEL_SET);
}

static void clearBall(int x, int y){
	gfx_mono_generic_draw_filled_circle(x, y, 2, GFX_PIXEL_CLR, 0x18);
}