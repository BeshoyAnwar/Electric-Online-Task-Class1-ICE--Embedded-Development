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
	SREG |= (1<<7);/* enable the global interrupt bit */
	ADC_init(); /* initialize ADC driver */
    while(1)
    {
		ADC_readChannel(0); /* read channel zero where the potentiometer is connect */
		Timer0_PWM_Init(g_adcResult);/* send the adc reading to the Timer0 */
    }
}
