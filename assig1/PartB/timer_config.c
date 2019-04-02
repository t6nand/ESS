/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment:		1. Use Button1 to transmit Morse equivalent "I CAN MORSE" using LED1. 
*							2. Use Button2 to calculate time between last & second last button presses to display it in it's Morse equivalent using LED1.
*/

/*********************************************************************************************************************************************************************************************
																								HEADER FILES																														
*********************************************************************************************************************************************************************************************/

#include "timer_config.h"

/*********************************************************************************************************************************************************************************************
														STANDARD DEFINITIONS, MACROS, DECLARATIONS AND GLOBAL CONSTANTS														
*********************************************************************************************************************************************************************************************/

uint32_t global_sys_tick_counter = 0;								// Global counts of Clock ticks. Initialised to 0.

/*********************************************************************************************************************************************************************************************
																							FUNCTION DEFINITIONS														
*********************************************************************************************************************************************************************************************/
/**
* This function initialises Systm Clock using SysTick to interrupt every 1ms. This can be counted to keep track of time.
*
*/
void init_sys_tick (void) {
	SysTick_Config ( SystemCoreClock / 1000 ) ;			// System Clock interrupts every 1 ms.
}	

/**
* This function is the interrupt handler for SysTick interrupts. It updates a global variable to keep track of each milli second elapsed.
*/
extern void SysTick_Handler (void) {
	global_sys_tick_counter++;
}

/**
*	This Method is used to introduce software delays between using SysTick. 
*/
void delay (uint32_t delay_duration) {
	 uint32_t current_sys_tick_counter_value; 
	 current_sys_tick_counter_value = global_sys_tick_counter;
	 while(global_sys_tick_counter - current_sys_tick_counter_value < delay_duration);
}

uint32_t get_current_time (void) {
	return global_sys_tick_counter;
}