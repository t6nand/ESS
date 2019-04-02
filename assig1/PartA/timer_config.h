/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment: Implementation of Morse Code using LED1 on Pin P1.1 to send Code Word "I CAN MORSE"   repeatedly when XMC4500 is ON with a 5s pause between each transmission.
*/

#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

#include <xmc_common.h>

uint32_t globalSysTickCounter;							//  Variable to keep global count for clock Ticks. 

void initSysTick(void);												// This function initialises SysTick.
void delay(uint32_t  delay_mS);									// This function is used to introduce a Software delay using SysTick. 

# endif