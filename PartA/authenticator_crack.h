/**
 * This Header File serves as the layout required in exploiting timing side
 * channel vulnerabilities in authenticator.
 */

#ifndef _AUTHENTICATOR_CRACK_H_
#define _AUTHENTICATOR_CRACK_H_

/* Header Files used: */
#include "KeyboardHID.h"
#include "german_keyboardCodes.h"
#include <xmc_gpio.h>

/* Macros: */
#define L_SHIFT HID_KEYBOARD_MODIFIER_LEFTSHIFT // Left Shift Key.
#define ALT_GR HID_KEYBOARD_MODIFIER_RIGHTALT   // Defines HID Keyboard's AltGr key (on non US layout keyboards.)
#define PSW_LENGTH 20                           // Max. Password length for cracking.
#define MAX_SAMPLES_PER_CHARACTER 1             // Max. samples for which response time is averaged out.

/* Global Variables: */
uint32_t request_sent_at_time;              // System time when a keystroke is sent.
uint32_t response_received_at_time;         // Time elapsed until response from host.
uint32_t max_response_time;                 // Max. response time for character in one iteration. Represents correct character comparison.
bool send_message_flag;                 // Monitor indicating the message send report is made to LUFA library.
bool send_enter_flag;                   // Monitor indicating the enter key send report is made.
uint64_t max_iteration_time[84];                // Array to keep response times for all possibilities (84 possible password chars) in one iteration.
uint64_t samples_response_time[MAX_SAMPLES_PER_CHARACTER]; // Keeps response time for multiple symbol requests. Can be averaged out for tuning.
unsigned int response_counter;              // Indicates number of process HID report callbacks invoked, meaning response from host.
unsigned int max_index;                     // Indicates index of symbol with maximum response time per iteration.
bool consume_on;                        // Indicates when to start consuming response from the host.

// This extern struct defines layout of intended message to be sent post
// cracking of the authenticator system
extern struct message_to_send
{
  const uint8_t word[100];     // Contins command to execute during/post cracking.
  uint8_t cnt;                 // Contains current count of commands during/post cracking.
  const uint8_t modifier[100]; // Modifiers like Left shift or AltGr.
} pswchars, inject_file;

// This extern struct contains definition of Password that would be filled
// character by character with cracked password.
extern struct correct_password
{
  uint8_t word[PSW_LENGTH];     // Keeps all correctly identified characters.
  uint8_t cnt;                  // Keeps current count of characters of correct password.
  uint8_t modifier[PSW_LENGTH]; // Keeps state of Modifiers required per character.
} psw;

// This extern struct defines State of NUM_LOCK & CAPS_LOCK Key which can be
// used as LED indicators of the HID keyboard.
extern struct key_state
{
  bool num_lock;
  bool caps_lock;
} key;

/* Function Prototypes: */

#endif