/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment:		1. Use Button1 to transmit Morse equivalent "I CAN MORSE" using LED1. 
*							2. Use Button2 to calculate time between last & second last button presses to display it in it's Morse equivalent using LED1.
*/

#ifndef __MORSE_DEFINITION_H__
#define __MORSE_DEFINITION_H__

#include <xmc_common.h>

const uint8_t dot_duration;							// This variable defines duration of Dot in Morse Code.
const uint16_t dash_duration; 					// This variable defines duration of Dash in Morse Code.
const uint16_t letter_spacing;						// This defines duration spacing between 2 letters in a Morse code. 
const uint16_t word_spacing;						// This defines duration spacing between 2 words in a Morse code. 

void init_GPIO (void); 									// This function is used to initialise GPIO for performing switching action on LED1.
void dot (void);											// This function represents a dot in Morse Code message in terms of duration of LED flashing.
void dash (void);											// This function represents a dash in Morse Code message in terms of duration of LED flashing.
void get_morse_for_character (char);			// This function is used to get morse code equivalent of the alphabets and numbers. 
void transmit_message (void);
void transmit_time (char*);

# endif  