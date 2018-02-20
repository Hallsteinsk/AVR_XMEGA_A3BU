/*
 * AVR_GPIO.c
 *
 * Created: 17.02.2018 15:45:27
 * Author : Hallstein
 */ 

#include <avr/io.h>


int main(void)
{
	PORTR_DIR = (1<<0) | (1<<1);
	PORTR_OUT &= ~(1<<0) & ~(1<<1);
	
    /* Replace with your application code */
    while (1) 
    {
		//asm(nop);
    }
	
	return 0;
}

