/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: timer0.c
 *
 * Description: Source file for the ATmega16 Timer0 driver
 *
 *******************************************************************************/
#include "timer0.h"
#define NUMBER_OF_OVERFLOWS_PER_SECOND 4
unsigned char g_tick = 0;
/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		PORTC = PORTC ^ (1<<PC1); //toggle led every 1 second
		g_tick = 0; //clear the tick counter again to count a new 1 second
	}
}



/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* init function for timer0 overflow mode */
void timer0_init_normal_mode(void)
{
	/* Description :
	 * For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
	 * so put initial timer counter=0  0 --> 255 (256ms per overflow)
	 * so we need timer to overflow 4 times to get a 1 second
	 */
	TCNT0 = 0; //timer initial value
	TIMSK |= (1<<TOIE0); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
}
