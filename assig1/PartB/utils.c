/**
*	Created By: Tapan Sharma
*	Matrikulation Number: 03712841
*   
*   Assignment:		1. Use Button1 to transmit Morse equivalent "I CAN MORSE" using LED1. 
*							2. Use Button2 to calculate time between last & second last button presses to display it in it's Morse equivalent using LED1.
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <xmc_common.h>

char * character_notation_of_number (uint32_t number) {
	if (number ==0) {
		return "0";
	}
	int n = log10(number) + 1;
	char* num_to_char = calloc(n, sizeof(char));
	sprintf(num_to_char, "%ld", number);
	return num_to_char;
}