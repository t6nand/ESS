/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment: Implementation of Morse Code using LED1 on Pin P1.1 to send Code Word "I CAN MORSE"   repeatedly when XMC4500 is ON with a 5s pause between each transmission.
*/

/*********************************************************************************************************************************************************************************************
																								HEADER FILES																														
*********************************************************************************************************************************************************************************************/
#include "morse_definition.h"
#include <xmc_gpio.h>
#include "timer_config.h"

/*********************************************************************************************************************************************************************************************
														STANDARD DEFINITIONS, MACROS, DECLARATIONS AND GLOBAL CONSTANTS														
*********************************************************************************************************************************************************************************************/

const uint8_t dotDuration = 100;										// Dot duration is of 100ms. Dot also represents 1 fundamental unit in a Morse code.
const uint16_t dashDuration = 300; 								// Dash duration is of 3x dot duration. (Refer Section 2 ITU-R M.1677-1)
const uint16_t letterSpacing = 300;									// Spacing duration between 2 letters in a word is of 3x dot duration. (Refer Section 2 ITU-R M.1677-1).
const uint16_t wordSpacing = 700;									// Spacing duration between 2 words is of 7x dot duration. (Refer Section 2 ITU-R M.1677-1)

/*********************************************************************************************************************************************************************************************
																							FUNCTION DEFINITIONS														
*********************************************************************************************************************************************************************************************/

/**
* This function initiates GPIO using config as defined in it.
*/ 
void initGPIO(void) {
	const XMC_GPIO_CONFIG_t LED_config = \
			{.mode=XMC_GPIO_MODE_OUTPUT_PUSH_PULL,\
			 .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
			 .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};	 
	XMC_GPIO_Init(XMC_GPIO_PORT1, 1, &LED_config);	
}

/**
* This function describes a "DOT" in Morse code. Each Dot is represented by a HIGH state of LED for {@param: dotDuration} which is 100 milli-second in this case.
*/
void dot(void) {
	XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 1);
	delay(dotDuration);
	XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 1);
	delay(dotDuration); // Added to keep distance from next "DOT/DASH" equivalent to 1 dotDuration. (Refer Section 2 ITU-R M.1677-1)
}

/**
* This function describes a "DOT" in Morse code. Each Dot is represented by a HIGH state of LED for {@param: dotDuration} which is 100 milli-second in this case.
*/
void dash(void) {
	XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 1);
	delay(dashDuration);
	XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 1);
	delay(dotDuration); // Added to keep distance from next "DOT/DASH" equivalent to 1 dotDuration. (Refer Section 2 ITU-R M.1677-1)
}

/**
* This method represents the intended Message in it's Morse Code equivalent.
*/

void transmitMessage(void) {
	// Message is "I CAN MORSE"
	
	// I 
	getMorseForCharacter('I');
	
	delay(wordSpacing - dotDuration); // Added to keep distance from next word, equivalent to 7 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	// C
	getMorseForCharacter('C');
	
	delay(letterSpacing - dotDuration); // Added to keep distance from next letter in a word, equivalent to 3 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	//A 
	getMorseForCharacter('A');
	
	delay(letterSpacing - dotDuration); // Added to keep distance from next letter in a word, equivalent to 3 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	// N 
	getMorseForCharacter('N');
	
	delay(wordSpacing - dotDuration); // Added to keep distance from next word, equivalent to 7 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	// M 
	getMorseForCharacter('M');
	
	delay(letterSpacing - dotDuration); // Added to keep distance from next letter in a word, equivalent to 3 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	// O 
	getMorseForCharacter('O');
	
	delay(letterSpacing - dotDuration); // Added to keep distance from next letter in a word, equivalent to 3 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	// R 
	getMorseForCharacter('R');
	
	delay(letterSpacing - dotDuration); // Added to keep distance from next letter in a word, equivalent to 3 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	// S 
	getMorseForCharacter('S');
	
	delay(letterSpacing - dotDuration); // Added to keep distance from next letter in a word, equivalent to 3 dotDurations. (Refer Section 2 ITU-R M.1677-1)
	
	// E
	getMorseForCharacter('E');
}

/**
* This function serves as a morse code mapping to their alpha-numeric equivalents.
*/
void getMorseForCharacter(char character) {
	switch (character) {
		case 'a':
		case 'A':
					dot();
					dash();
				break;
		case 'b':
		case 'B':
					dash();
					dot();
					dot();
					dot();
				break;
		case 'c':
		case 'C':
					dash();
					dot();
					dash();
					dot();
				break;
		case 'd':
		case 'D':
					dash();
					dot();
					dot();
				break;
		case 'e':
		case 'E':
					dot();
				break;
		case 'f':
		case 'F':
					dot();
					dot();
					dash();
					dot();
				break;
		case 'g':
		case 'G':
					dash();
					dash();
					dot();
				break;
		case 'h':
		case 'H':
					dot();
					dot();
					dot();
					dot();
				break;
		case 'i':
		case 'I':
					dot();
					dot();
				break;
		case 'j':
		case 'J':
					dot();
					dash();
					dash();
					dash();
				break;
		case 'k':
		case 'K':
					dash();
					dot();
					dash();
				break;
		case 'l':
		case 'L':
					dot();
					dash();
					dot();
					dot();
				break;
		case 'm':
		case 'M':
					dash();
					dash();
				break;
		case 'n':
		case 'N':
					dash();
					dot();
				break;
		case 'o':
		case 'O':
					dash();
					dash();
					dash();
				break;
		case 'p':
		case 'P':
					dot();
					dash();
					dash();
					dot();
				break;
		case 'q':
		case 'Q':
					dash();
					dash();
					dot();
					dash();
				break;
		case 'r':
		case 'R':
					dot();
					dash();
					dot();
				break;
		case 's':
		case 'S':
					dot();
					dot();
					dot();
				break;
		case 't':
		case 'T':
					dash();
				break;
		case 'u':
		case 'U':
					dot();
					dot();
					dash();
				break;
		case 'v':
		case 'V':
					dot();
					dot();
					dot();
					dash();
				break;
		case 'w':
		case 'W':
					dot();
					dash();
					dash();
				break;
		case 'x':
		case 'X':
					dash();
					dot();
					dot();
					dash();
				break;
		case 'y':
		case 'Y':
					dash();
					dot();
					dash();
					dash();
				break;
		case 'z':
		case 'Z':
					dash();
					dash();
					dot();
					dot();
				break;
		case '0':
					dash();
					dash();
					dash();
					dash();
					dash();
				break;
		case '1':
					dot();
					dash();
					dash();
					dash();
					dash();
				break;
		case '2':
					dot();
					dot();
					dash();
					dash();
					dash();
				break;
		case '3':
					dot();
					dot();
					dot();
					dash();
					dash();
				break;
		case '4':
					dot();
					dot();
					dot();
					dot();
					dash();
				break;
		case '5':
					dot();
					dot();
					dot();
					dot();
					dot();
				break;
		case '6':
					dash();
					dot();
					dot();
					dot();
					dot();
				break;
		case '7':
					dash();
					dash();
					dot();
					dot();
					dot();
				break;
		case '8':
					dash();
					dash();
					dash();
					dot();
					dot();
				break;
		case '9':
					dash();
					dash();
					dash();
					dash();
					dot();
				break;
		default: 
					;			// Do Nothing
	}
}
