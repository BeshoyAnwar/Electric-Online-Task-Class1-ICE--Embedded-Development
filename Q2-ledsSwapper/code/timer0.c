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

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
volatile unsigned char g_press_no = 0;
volatile unsigned char g_tick1 = 0;
volatile unsigned char g_tick2 = 0;
volatile unsigned char g_tick3 = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	g_tick1++;g_tick2++;g_tick3++;
	if(g_press_no == 2)
	{
		if(g_tick1==4){//led 1 slowly
			TOGGLE_BIT(PORTC,PC0);
			g_tick1 = 0;
		}
	}
	else if(g_press_no == 3){
		if(g_tick1==1){// led 1 fast
			TOGGLE_BIT(PORTC,PC0);
			g_tick1 = 0;
		}
		if(g_tick2==4){// led 2 slowly
			TOGGLE_BIT(PORTC,PC1);
			g_tick2 = 0;
		}
	}
	else if(g_press_no == 4){
		if(g_tick2==1){// led 2 fast
			TOGGLE_BIT(PORTC,PC1);
			g_tick2 = 0;
		}
		if(g_tick3==4){// led 3 slowly
			TOGGLE_BIT(PORTC,PC2);
			g_tick3 = 0;
		}
	}
	else if(g_press_no == 5){
		if(g_tick3==1){// led 3 fast
			TOGGLE_BIT(PORTC,PC2);
			g_tick3 = 0;
		}
	}
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* init function for timer0 compare mode */
void timer0_init_CTC_mode(unsigned char tick)
{
	/* For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
	 * so we just need 250 counts to get 250ms every overflow. put initial timer counter=0
	 * and output compare register=250 0 --> 250 (250ms per overflow)
	 * so we need timer to overflow 1 times to get a 0.25 second (fast)
	 * 		       overflow 4 times to get a 1 second (slow)
	 */
	TCNT0 = 0; //timer initial value
	OCR0  = tick; //compare value
	TIMSK |= (1<<OCIE0); //enable compare interrupt
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
}
