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

#include "morse_definition.h"
#include "timer_config.h"
#include "button_state.h"
#include "utils.h"

/*********************************************************************************************************************************************************************************************
																							STANDARD DEFINITIONS, MACROS, DECLARATIONS AND GLOBAL CONSTANTS				
*********************************************************************************************************************************************************************************************/

uint32_t button1_previous_time = 0;
uint32_t button1_first_press = 0;
uint32_t time_between_two_button1_press = 0;
uint32_t boot_time;
static bool has_string_transmitted = false;
bool print_time_once = false;
bool print_zero_once = false;
uint32_t button1_counter = 0;


static bool prev_button1_state = false;
static bool prev_button2_state = false;
 
/*********************************************************************************************************************************************************************************************
																							FUNCTION DEFINITIONS														
*********************************************************************************************************************************************************************************************/

/**
*	Main function of PartB of Assignment. 
*/
int main (void) {
	
	// 1. Initialise System Clock.
	init_sys_tick();
	
	// 2. Capture Boot Time.
	boot_time = get_current_time();
	
	// 3. Initialise I/O
	init_GPIO();
	init_button_for_input_read();
	
	// 4. Program Logic
	
	if(button1_counter == 0) {
				print_time_once = true;
		}
		
	while (1) {
		uint32_t current_time_ms = get_current_time();
		bool button1_state = get_button1_state();
		bool button2_state = get_button2_state();
		
		if (button1_state && prev_button1_state) {
			if(!button2_state) {
				button1_counter++;
				if(button1_counter == 1) {
					button1_first_press = current_time_ms;
				}
				time_between_two_button1_press = current_time_ms - button1_previous_time;
				button1_previous_time = current_time_ms;
				print_time_once = true;
				if (!has_string_transmitted) {
					transmit_message();
					has_string_transmitted = true;
				}
			} else {
				while(!button2_state) {
					// Do Nothing. i.e. wait until button2 is released..
				}
				button1_counter++;
				if(button1_counter == 1) {
					button1_first_press = current_time_ms;
				}
				time_between_two_button1_press = current_time_ms - button1_previous_time;
				button1_previous_time = current_time_ms;
				print_time_once = true;
				if (!has_string_transmitted) {
					transmit_message();
					has_string_transmitted = true;
				}
			}
			delay(50);
		} else {
			has_string_transmitted = false;
		}	
		
		prev_button1_state = button1_state;
		
		if(button2_state && prev_button2_state) {
			if (!button1_state) {
				char* message;
				switch(button1_counter) {
					case 0:
							message = "0";
							break;
					case 1:
							message = character_notation_of_number(button1_first_press - boot_time);
							break;
					default:
							message = character_notation_of_number(time_between_two_button1_press);
				}
				if (print_time_once) {
					transmit_time(message);
					print_time_once = false;
				} 
			} else {
				while(!button1_state) {
					// Do Nothing. i.e. wait until button1 is released.
				}
				char* message;
				switch(button1_counter) {
					case 0:
							message = "0";
							break;
					case 1:
							message = character_notation_of_number(button1_first_press - boot_time);
							break;
					default:
							message = character_notation_of_number(time_between_two_button1_press);
				}
				if(print_time_once) {
					transmit_time(message);
					print_time_once = false;
				}
			}
			delay(50);
		}
		
		prev_button2_state = button2_state;
	}
  return 0;
}