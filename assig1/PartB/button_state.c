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
#include <xmc_gpio.h>

#include "morse_definition.h"
#include "timer_config.h"

/*********************************************************************************************************************************************************************************************
																	STANDARD DEFINITIONS, MACROS, DECLARATIONS AND GLOBAL CONSTANTS												
*********************************************************************************************************************************************************************************************/

bool button1_state = false;
bool button2_state = false;

uint32_t time_between_last_two_button1_presses = 0;
uint32_t button1_previous_pressed_time = 0;

void read_button1_state (void);
void read_button2_state (void);
void set_button1_state (bool);
void set_button2_state (bool);

/*********************************************************************************************************************************************************************************************
																	FUNCTION DEFINITIONS														
*********************************************************************************************************************************************************************************************/

/**
*	Setter for capturing Button1 state to a variable.
*/
void set_button1_state (bool state) {
	button1_state = state;
}

/**
*	Setter for capturing Button2 state to a variable.
*/
void set_button2_state (bool state) {
	button2_state = state;
}

/**
*	Getter for reading Button1 State.
*/
bool get_button1_state (void) {
	read_button1_state();
	return button1_state;
}

/**
*	Getter for reading Button2 State.
*/
bool get_button2_state (void) {
	read_button2_state();
	return button2_state;
}

/**
* This function reads Button1 state from the board and uses a setter function to capture it's value to a variable.
*/
void read_button1_state (void) {
	if ( XMC_GPIO_GetInput ( XMC_GPIO_PORT1, 14 ) ) {
		set_button1_state(true);
	} else {
		set_button1_state(false);
	}
}

/**
* This function reads Button2 state from the board and uses a setter function to capture it's value to a variable.
*/
void read_button2_state (void) {
	if ( XMC_GPIO_GetInput ( XMC_GPIO_PORT1, 15 ) ) {
		set_button2_state(true);
	} else {
		set_button2_state(false);
	}
}

/**
*	This function sets up buttons for input read.
*/
void init_button_for_input_read (void) {
	const XMC_GPIO_CONFIG_t buttonConfig = \
			{.mode=XMC_GPIO_MODE_INPUT_INVERTED_TRISTATE};	 
	XMC_GPIO_Init(XMC_GPIO_PORT1, 14, &buttonConfig);	
	XMC_GPIO_Init(XMC_GPIO_PORT1, 15, &buttonConfig);
}