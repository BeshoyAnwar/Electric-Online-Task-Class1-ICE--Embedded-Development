 /******************************************************************************
 *
 * Module: Main
 *
 * File Name: main.c
 *
 * Description: Source file for application layer
 *
 *******************************************************************************/

#include "timer0.h"

/* External INT1 Interrupt Service Routine */
ISR(INT1_vect)
{
	g_press_no++;
	if(g_press_no==6)
		g_press_no=0;
	g_tick1 = 0;g_tick2 = 0;g_tick3 = 0;
	timer0_init_CTC_mode(250);
}

/* External INT1 enable and configuration function */
void INT1_Init(void)
{
	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	PORTD |= (1<<PD3);     // Enable the internal pull up resistor at PD3 pin
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	// Trigger INT1 with the falling edge
	MCUCR |= (1<<ISC11);
	MCUCR &= ~(1<<ISC10);
	SREG  |= (1<<7);       // Enable interrupts by setting I-bit
}

int main(void)
{
	INT1_Init();           		// Enable and configure external INT1
	SREG  |= (1<<7);           // enable global interrupts in MC.
	DDRC  = (DDRC&0xF1)|0x07; // Configure PC0-PC2 as output


    while(1)
    {

		switch(g_press_no)
		{
			case 0:
				PORTC=0;
				break;
			case 1:
				SET_BIT(PORTC,0);
				CLEAR_BIT(PORTC,1);
				CLEAR_BIT(PORTC,2);
				break;
			case 2:
				SET_BIT(PORTC,1);
				CLEAR_BIT(PORTC,2);
				break;
			case 3:
				SET_BIT(PORTC,2);
				break;
			case 4:
				CLEAR_BIT(PORTC,0);
				break;
			case 5:
				CLEAR_BIT(PORTC,0);
				CLEAR_BIT(PORTC,1);
				break;
		}

	}
}
