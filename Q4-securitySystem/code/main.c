 /******************************************************************************
 *
 * Module: Main
 *
 * File Name: main.c
 *
 * Description: Source file for application layer
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "PWM.h"
#include "lcd.h"
#include "keypad.h"

/* ISR of INT1 make sleep mode when push button is pressed */
ISR(INT1_vect)
{
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode();
}

/* init the INT1 */
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
	unsigned char key;
	char password[3];
	unsigned char i=0;
	unsigned char chances_no=3;
	DDRC=0x3;// init PC0-PC1 as output
	DDRB|=(1<<PB4)|(1<<PB5);// init PB4-PB5 as output
	PORTC=0;
	INT1_Init();
	SREG  |= (1<<7); //enable global interrupts in MC by setting the I-Bit.
	LCD_init();
	LCD_displayStringRowColumn(0,0,"Enter your passw");
	LCD_displayStringRowColumn(1,0,"ord");
	LCD_goToRowColumn(2,0);
    while(1)
    {

		/* if any switch pressed for more than 250 ms it counts more than one press */
    	if(chances_no!=0){
		key = KeyPad_getPressedKey(); /* get the pressed key number */
		LCD_displayCharacter('*');
		if((key <= 9) && (key >= 0))
		{
			password[i]=key+'0';
		}

		else{
			password[i]=key;
		}
		i++;
		if(i==3){
			LCD_clearScreen();i=0;
			if(password[0]=='1'&&password[1]=='2'&&password[2]=='3'){
				LCD_displayStringRowColumn(0,0,"Correct");
				SET_BIT(PORTC,0);// green led on
				/* motor rotate clockwise with square wave 50% Duty cycle and 500 Hz */
				SET_BIT(PORTB,4);
				CLEAR_BIT(PORTB,5);
				Timer0_PWM_Init(128);
			}
			else{
				chances_no--;
				if(chances_no==0){
					LCD_displayStringRowColumn(0,0,"System is locked");
					timer0_init_normal_mode();// init the overflow timer to  start the alert
				}
				else{
					LCD_displayStringRowColumn(0,0,"Wrong, Re-enter ");
					LCD_displayStringRowColumn(1,0,"the password");
					LCD_goToRowColumn(2,0);
				}

			}
		}
		_delay_ms(250); /* Press time */
    	}
    }
}
