/* Header files used: */
#include "authenticator_crack.h"
#include "timing.h"

/**
 * This struct contains the current state of the NUM_LOCK and CAPS_LOCK LEDs.
 * Initialized to be OFF.
 */
struct key_state key = {0, 0};

/**
 * Valid Password characters. Total 84 characters.
 */
const char pwchars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123"
                       "4567890!()-_+=~;:,.<>[]{}/?&$";

/**
 * This struct is filled char by char with the correct password.
 * word initialised to first valid character.
 */
struct correct_password psw = {{0x04}, 0, {0x00}};

/**
 * Required for modeling XMC4500 board's LEDs as NUM_LOCK
 * & CAPS_LOCK indicators.
 */
const XMC_GPIO_CONFIG_t LED_config = {
    .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};

/**
 * This struct contains the keyboard scan codes for valid characters of the
 * password to be attempted along with the scan codes for command to execute
 * after the password is cracked.
 */
struct message_to_send
    // Scan codes for valid password characters. Follows standard German
    // Keyboard Layout.
    pswchars = {{// a - z
                 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
                 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                 0x18, 0x19, 0x1A, 0x1B, 0x1D, 0x1C,
                 // 1, 2, 3, 4, 5, 6, 7, 8, 9, 0
                 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                 // , . -
                 0x36, 0x37, 0x38,
                 // < +. (invoked using L_SHIFT modifier).
                 0x64, 0x30,
                 // A - Z. (Capitalization achieved using L_SHIFT modifier)
                 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
                 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                 0x18, 0x19, 0x1A, 0x1B, 0x1D, 0x1C,
                 // ! $ / ( ) = ? > ; : _ . (Achieved using L_SHIFT modifier)
                 0x1E, 0x21, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x64, 0x36,
                 0x37, 0x38,
                 // ~ { [ ] }. (invoked using AltGr / right Alt)
                 0x30, 0x24, 0x25, 0x26, 0x27},

                0, // Initial Password Count.

                // Modifiers to be used to model above defined characters.
                {// No modifiers. For the case a-z 0-9 ,.-
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00,
                 // LEFT SHIFT modifier. For the case <+ A-Z !$/()=?>;:_
                 L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT,
                 L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT,
                 L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT,
                 L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT,
                 L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT, L_SHIFT,
                 L_SHIFT, L_SHIFT, L_SHIFT,
                 // ALT GR modifier. For case ~{[]}
                 ALT_GR, ALT_GR, ALT_GR, ALT_GR, ALT_GR}},

    // Scan codes for executing command after authenticator is breached
    // Command to be executed: `echo tapan sharma >>
    // ~/<My_Matriculation_Number>`
    inject_file = {
        {0x00, GERMAN_KEYBOARD_SC_E, GERMAN_KEYBOARD_SC_C, GERMAN_KEYBOARD_SC_H,
         GERMAN_KEYBOARD_SC_O,
         GERMAN_KEYBOARD_SC_SPACE, // "echo" + space = 5
         GERMAN_KEYBOARD_SC_T, GERMAN_KEYBOARD_SC_A, GERMAN_KEYBOARD_SC_P,
         GERMAN_KEYBOARD_SC_A, GERMAN_KEYBOARD_SC_N,
         GERMAN_KEYBOARD_SC_SPACE, // "tapan" + space = 6
         GERMAN_KEYBOARD_SC_S, GERMAN_KEYBOARD_SC_H, GERMAN_KEYBOARD_SC_A,
         GERMAN_KEYBOARD_SC_R, GERMAN_KEYBOARD_SC_M, GERMAN_KEYBOARD_SC_A,
         GERMAN_KEYBOARD_SC_SPACE, // "sharma" + space = 7
         GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE,
         0x00, // No Key Press. This helps to model key presses of same type
               // multiple times i.e. >> in this case
         GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE,
         GERMAN_KEYBOARD_SC_SPACE, // ">" No Key ">" + space = 4
         GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE,   // tilde = 1
         GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE, // slash = 1
         GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE,
         GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH,
         GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE,
         GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION, GERMAN_KEYBOARD_SC_2_AND_QUOTES,
         0x00, GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET,
         GERMAN_KEYBOARD_SC_4_AND_DOLLAR, GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION},
        33, // 33 Character long message to be executed post cracking.

        // Modifiers for the message to be executed post cracking.
        {
            0x00,                                           // For fresh start
            0x00,    0x00, 0x00,    0x00, 0x00,             // "echo" + space
            0x00,    0x00, 0x00,    0x00, 0x00, 0x00,       // "tapan" + space
            0x00,    0x00, 0x00,    0x00, 0x00, 0x00, 0x00, // "sharma" + space
            L_SHIFT, 0x00, L_SHIFT, 0x00, // ">" + No Key (0x00) + ">" + space
            ALT_GR,                       // for the tilde
            L_SHIFT,                      // for the slash
            0x00,    0x00, 0x00,    0x00, 0x00, 0x00, 0x00,
            0x00 // "Matrikulation Number"
        }};

uint32_t request_sent_at_time = 0;
uint32_t response_received_at_time = 0;
uint32_t max_response_time = 0;
bool send_message_flag = false;
bool send_enter_flag = false;
uint64_t max_iteration_time[84];
uint64_t samples_response_time[MAX_SAMPLES_PER_CHARACTER];
unsigned int response_counter = 0;
unsigned int max_index = 0;
bool consume_on = false;