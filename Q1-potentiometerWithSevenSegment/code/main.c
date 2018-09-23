/******************************************************************************
 *
 * Module: Main
 *
 * File Name: main.c
 *
 * Description: Source file for application layer
 *
 *******************************************************************************/
#include "adc.h"
int main(void)
{
	SREG |= (1<<7);/* Enable Global Interrupts */
	ADC_init(); /* initialize ADC driver */
	DDRD |= 0x0F;/* init the pins PD0:PD3 as output */
	PORTD &= 0xF0;/* display zero on 7-seg as initiation */
	uint8 num=0;
	while(1)
	{
		ADC_readChannel(0); /* read channel two where the temp sensor is connect */
		num=(g_adcResult*5)/1023;/* mapping the adc result into a num from 0:5 */
		PORTD = (PORTD & 0xF0) | (num & 0x0F);/* display thr num on 7-seg */
	}

}
