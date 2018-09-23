/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.c
 *
 * Description: Source file for the Atmega16 PWM driver
 *
 *******************************************************************************/

#include "PWM.h"
/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void Timer0_PWM_Init(uint16 setDutyCycle)
{
	/*
	* Timer0 will be used with pre-scaler F_CPU/8
	* F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
	*/

	TCNT0 = 0; // Timer initial value

	OCR0  = setDutyCycle;

	DDRB  = DDRB | (1<<PB3); //set OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	_delay_ms(50);
}
