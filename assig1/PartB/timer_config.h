/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment:		1. Use Button1 to transmit Morse equivalent "I CAN MORSE" using LED1. 
*							2. Use Button2 to calculate time between last & second last button presses to display it in it's Morse equivalent using LED1.
*/

#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

#include <xmc_common.h>

uint32_t global_sys_tick_counter;								//  Variable to keep global count for clock Ticks. 

void init_sys_tick (void);												// This function initialises SysTick.
void delay (uint32_t);												// This function is used to introduce a Software delay using SysTick. 
uint32_t get_current_time (void);										// This function returns current time i.e. number of SysTicks in milli seconds.
# endif