/*
 * Main File for HIDe Your Password ESS deliverable. Exploits Timing Side
 * Channel vulnerabilities in the custom authenticator of embedded tiny linux
 * core machine hosted on some other embedded system.
 */

/* Header Files used: */
#include "KeyboardHID.h"
#include "authenticator_crack.h"
#include "timing.h"

/**
 * Main program entry point. This routine configures the hardware required by
 * the application, then enters a loop to run the application tasks in sequence.
 */
int main(void) {
  // Initialize LEDs being used to keep visual state indicator of HID Keyboard
  // num_lock & caps_lock keys.
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  // Initialize LUFA USB interface
  USB_Init();

  // SysTick timer configuration. Creates sys tick to interrupt at 1 ms
  // duration (Defined by SYSTICK_RESOLUTION). This is further used to keep
  // track of time channels and response of authenticator program.
  SysTick_Config(SystemCoreClock / SYSTICK_RESOLUTION);

  // Initializations for a fresh start
  hid.actv = 0;
  hid.cracked = 0;
  key.num_lock = 0;

  // Dely USB Interface task until the start of the authenticator program.
  while (key.num_lock == 0) {
    HID_Device_USBTask(&Generic_HID_Interface);
  }

  // Wait until host has enumerated HID device.
  for (uint32_t i = 0; i < 10e5; ++i)
    ;
  if (key.num_lock == 1) {
    hid.actv = 1; // Indicates active state of HID device
    while (1) {
      HID_Device_USBTask(&Generic_HID_Interface);
    }
  }
}
