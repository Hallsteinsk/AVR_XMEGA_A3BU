/*
 * TestDisplay.c
 *
 * Created: 18.02.2018 13:56:08
 * Author : Hallstein
 */ 

#include <avr/io.h>


int main(void)
{
	PORTE_DIR = (1<<4);
	PORTR_OUT = (1<<4);
    /* Replace with your application code */
    while (1) 
    {
    }
}

