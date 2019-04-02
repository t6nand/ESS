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
#include <string.h>

#include "button_state.h"
#include "morse_definition.h"
#include "timer_config.h"

/*********************************************************************************************************************************************************************************************
																							STANDARD DEFINITIONS, MACROS, DECLARATIONS AND GLOBAL CONSTANTS				
*********************************************************************************************************************************************************************************************/

const uint8_t dot_duration = 100;										// Dot duration is of 100ms. Dot also represents 1 fundamental unit in a Morse code.
const uint16_t dash_duration = 300; 									// Dash duration is of 3x dot duration. (Refer Section 2 ITU-R M.1677-1)
const uint16_t letter_spacing = 300;									// Spacing duration between 2 letters in a word is of 3x dot duration. (Refer Section 2 ITU-R M.1677-1).
const uint16_t word_spacing = 700;									// Spacing duration between 2 words is of 7x dot duration. (Refer Section 2 ITU-R M.1677-1)

bool transmit_message_0_once = false;
bool transmit_message_once = false;

void end_transmission_abruptly (void);

/*********************************************************************************************************************************************************************************************
																							FUNCTION DEFINITIONS														
*********************************************************************************************************************************************************************************************/

/**
* This function initiates GPIO using config as defined in it.
*/ 
void init_GPIO(void) {
	const XMC_GPIO_CONFIG_t LED_config = \
			{.mode=XMC_GPIO_MODE_OUTPUT_PUSH_PULL,\
			 .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
			 .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};	 
	XMC_GPIO_Init(XMC_GPIO_PORT1, 1, &LED_config);	
	XMC_GPIO_Init(XMC_GPIO_PORT1, 0, &LED_config);	
}

/**
* This function describes a "DOT" in Morse code. Each Dot is represented by a HIGH state of LED for {@param: dot_uration} which is 100 milli-second in this case.
*/
void dot(void) {
	XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 1);
	delay(dot_duration);
	XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 1);
	delay(dot_duration); // Added to keep distance from next "DOT/DASH" equivalent to 1 dotDuration. (Refer Section 2 ITU-R M.1677-1)
}

/**
* This function describes a "DOT" in Morse code. Each Dot is represented by a HIGH state of LED for {@param: dotDuration} which is 100 milli-second in this case.
*/
void dash(void) {
	XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 1);
	delay(dash_duration);
	XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 1);
	delay(dot_duration); // Added to keep distance from next "DOT/DASH" equivalent to 1 dotDuration. (Refer Section 2 ITU-R M.1677-1)
}

/**
* This method transmits the message I CAN MORSE when button1 is pressed and held. Transmission is terminated if button is released.
*/
void transmit_message() {
	if(get_button1_state()) {
		 char message[] = "I CAN MORSE";
		char* token_iterator = strtok(message, " ");
		while (token_iterator != NULL) {
			int length_of_word = strlen(token_iterator);
			char word_of_message[] = "";
			strcat(word_of_message, token_iterator);
			char* letter_iterator = word_of_message;
			int count = 0;
			while(letter_iterator != NULL && *letter_iterator != '\0') { 
				get_morse_for_character(*letter_iterator);
				if(length_of_word > 1 && count < (length_of_word -1) ) {
					count++;
					delay(letter_spacing - dot_duration);
				}
				letter_iterator++;				
			}
			delay(word_spacing - dot_duration);
			token_iterator = strtok(NULL, " ");
		} 
	}
}

/**
* This method transmits the time between 2 Button1 press downs. 
* CAUTION: Can't be used for character strings with spaces. (Assumes string to be a continuous alpha-numeric one (Time in milli-second in this case i.e. only numbers) )
*/
void transmit_time(char* time_message) {
	if (get_button2_state()) {
		char* letter_iterator = time_message;
		while(letter_iterator != NULL && *letter_iterator != '\0') { 
			get_morse_for_character(*letter_iterator);
			delay(letter_spacing - dot_duration);
			letter_iterator++;
		}
	} 
}

/**
* This function serves as a morse code mapping to their alpha-numeric equivalents.
*/
void get_morse_for_character(char character) {
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