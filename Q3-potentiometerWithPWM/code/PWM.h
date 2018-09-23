/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Description: header file for the Atmega16 PWM driver
 *
 *******************************************************************************/


#ifndef PWM_H_
#define PWM_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer0_PWM_Init(uint16 adcReading);

#endif /* PWM_H_ */
