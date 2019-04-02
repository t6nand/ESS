/**
 *  This Header File is the base Modeling for a HID device. The declarations,
 * macros and prototypes are respectively extended by the KeyboardHID.c and
 * other project files.
 */

#ifndef _KEYBOARDHID_H_
#define _KEYBOARDHID_H_

/* Header Files used: */
#include "Descriptors.h"

#define LED1 P1_1     // Defines LED1 of the XMC4500 relax lite kit connected to the Pin P1_1
#define LED2 P1_0     // Defines LED2 of the XMC4500 relax lite kit connected to the Pin P1_0

/* Global variables: */
extern USB_ClassInfo_HID_Device_t Generic_HID_Interface; // Extren HID Interface variable.

// This extern struct defines layout of modeled HID device's state
extern struct hid_state
{
    uint32_t response_time;        // Time elapsed since request until response.
    uint8_t n;                     // Current count in buffer.
    bool check_char;               // Indicator for next attempt or not.
    bool actv;                     // Indicates active state of keyboard i.e. when it's attempting.
    bool cracked;                  // Indicator for crack success.
    uint8_t hops;                  // Indicates different phases until stopping of the HID attempts.
} hid;

// This function initializes USB
void USB_Init(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);

// Callback function called when a new HID report needs to be created
bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, uint8_t *const ReportID,
    const uint8_t ReportType, void *ReportData, uint16_t *const ReportSize);

// Called on report input. For keyboard HID devices, that's the state of the
// LEDs
void CALLBACK_HID_Device_ProcessHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, const uint8_t ReportID,
    const uint8_t ReportType, const void *ReportData,
    const uint16_t ReportSize);

#endif