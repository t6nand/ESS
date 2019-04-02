/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment: Implementation of Morse Code using LED1 on Pin P1.1 to send Code Word "I CAN MORSE"   repeatedly when XMC4500 is ON with a 5s pause between each transmission.
*/

#ifndef __MORSE_DEFINITION_H__
#define __MORSE_DEFINITION_H__

#include <xmc_common.h>

const uint8_t dotDuration;							// This variable defines duration of Dot in Morse Code.
const uint16_t dashDuration; 						// This variable defines duration of Dash in Morse Code.
const uint16_t letterSpacing;						// This defines duration spacing between 2 letters in a Morse code. 
const uint16_t wordSpacing;						// This defines duration spacing between 2 words in a Morse code. 

void initGPIO(void); 									// This function is used to initialise GPIO for performing switching action on LED1.
void transmitMessage(void);						// This function is used to transmit Message "I CAN MORSE" 
void dot(void);											// This function represents a dot in Morse Code message in terms of duration of LED flashing.
void dash(void);											// This function represents a dash in Morse Code message in terms of duration of LED flashing.
void getMorseForCharacter(char);					// This function is used to get morse code equivalent of the alphabets and numbers. 

# endif  