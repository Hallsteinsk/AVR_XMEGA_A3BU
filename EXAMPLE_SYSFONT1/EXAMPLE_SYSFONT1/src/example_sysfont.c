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


static void initialState(void);
static void secretMessageState(void);
static void clearScreen(void);
static void toggleBacklight(void);

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
	sysclk_init();
	gfx_mono_init();

	
	initialState();
	


	while (true) {
		
		//Push button 0 for turning backlight on/off.
		if(gpio_pin_is_low(GPIO_PUSH_BUTTON_0)){
			toggleBacklight();
			while(gpio_pin_is_low(GPIO_PUSH_BUTTON_0)){
				//asm(nop);
				//Do nothing while the button is low.
			}
		}
		
		//Push button 1 for secret message ;)
		if(gpio_pin_is_low(GPIO_PUSH_BUTTON_1)){
			secretMessageState();
			while(gpio_pin_is_low(GPIO_PUSH_BUTTON_1)){
				//asm(nop);
				//Do nothing while the button is low.
			}
		}
		
		//Push button 2 for reset;)
		if(gpio_pin_is_low(GPIO_PUSH_BUTTON_2)){
			initialState();
			while(gpio_pin_is_low(GPIO_PUSH_BUTTON_2)){
				//asm(nop);
				//Do nothing while the button is low.
			}
		}
	}
}

static void initialState(void){
	clearScreen();
	gfx_mono_draw_string("Trykk paa knappen   ^",
	0, 0, &sysfont);	
}

static void secretMessageState(void){
	clearScreen();
	gfx_mono_draw_string("Hei Caroline.\nDu er sot!",
	0, 0, &sysfont);
}

static void toggleBacklight(void){
	gpio_toggle_pin(NHD_C12832A1Z_BACKLIGHT);
}

static void clearScreen(void){
	gfx_mono_draw_string("                     \n                     \n                     ",
	0, 0, &sysfont);
}
