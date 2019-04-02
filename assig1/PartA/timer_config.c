/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment: Implementation of Morse Code using LED1 on Pin P1.1 to send Code Word "I CAN MORSE"   repeatedly when XMC4500 is ON with a 5s pause between each transmission.
*/

/*********************************************************************************************************************************************************************************************
																								HEADER FILES																														
*********************************************************************************************************************************************************************************************/

#include "timer_config.h"

/*********************************************************************************************************************************************************************************************
														STANDARD DEFINITIONS, MACROS, DECLARATIONS AND GLOBAL CONSTANTS														
*********************************************************************************************************************************************************************************************/

uint32_t globalSysTickCounter = 0;								// Global counts of Clock ticks. Initialised to 0.

/*********************************************************************************************************************************************************************************************
																							FUNCTION DEFINITIONS														
*********************************************************************************************************************************************************************************************/
/**
* This function initialises Systm Clock using SysTick to interrupt every 1ms. This can be counted to keep track of time.
*
*/
void initSysTick(void) {
	SysTick_Config ( SystemCoreClock / 1000 ) ;			// System Clock interrupts every 1 ms.
}	

/**
* This function is the interrupt handler for SysTick interrupts. It updates a global variable to keep track of each milli second elapsed.
*/
extern void SysTick_Handler(void) {
	globalSysTickCounter++;
}

/**
*	This Method is used to introduce software delays between using SysTick. 
*/
void delay(uint32_t delayDuration) {
	 uint32_t currentSysTickCounterValue; 
	 currentSysTickCounterValue = globalSysTickCounter;
	 while(globalSysTickCounter - currentSysTickCounterValue < delayDuration);
}