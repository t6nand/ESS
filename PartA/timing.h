/**
 * This header file contains Timing related configurations &  function
 * prototypes. Intentional use in this project is to configure clock for USB HID
 * Keyboard Interface using CCU4 & using SysTick for timing side channel
 * attacks.
 */

/* Header files included: */
#include "KeyboardHID.h"
#include "authenticator_crack.h"

/* Macros: */
#define SYSTICK_RESOLUTION 100000 // 100000 SysTicks per second.

/* Global Variables: */

/* Function prototypes: */

/**
 * Systick_Handler. ISR for SysTick interrupts.
 */
void SysTick_Handler(void);

/**
 * CCU4 configure setup for providing clock to the HID device.
 */
void SystemCoreClockSetup(void);

/**
 * Returns current system time in ms since program is first executed.
 */
uint32_t get_system_time(void);