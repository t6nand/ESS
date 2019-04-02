/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment:		1. Use Button1 to transmit Morse equivalent "I CAN MORSE" using LED1. 
*							2. Use Button2 to calculate time between last & second last button presses to display it in it's Morse equivalent using LED1.
*/

#ifndef __BUTTON_STATE_H__
#define __BUTTON_STATE_H__

bool button1_state; 								// Keeps Button1 state as read from the XMC4500 board.
bool button2_state;								// Keeps Button2 state as read from the XMC4500 board.

bool get_button1_state (void);					// Function to get Button1 state which can be used to build programming logics.
bool get_button2_state (void);					// Function to get Button2 state which can be used to build programming logics.
void init_button_for_input_read (void);		// Initialises and sets up Button1 & Button2 for reading input.

#endif