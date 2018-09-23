/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: timer0.h
 *
 * Description: Header file for the ATmega16 Timer0 driver
 *
 *******************************************************************************/


#ifndef TIMER0_H_
#define TIMER0_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern volatile unsigned char g_press_no;
extern volatile unsigned char g_tick1;
extern volatile unsigned char g_tick2;
extern volatile unsigned char g_tick3;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void timer0_init_CTC_mode(unsigned char tick);


#endif /* TIMER0_H_ */
