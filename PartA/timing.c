#include "timing.h"

/* Variables: */
uint32_t CORE_TIME_VARIABLE = 0;

XMC_SCU_CLOCK_CONFIG_t clock_config = {
    .syspll_config.p_div = 2,
    .syspll_config.n_div = 80,
    .syspll_config.k_div = 4,
    .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
    .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
    .enable_oschp = true,
    .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
    .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
    .fsys_clkdiv = 1,
    .fcpu_clkdiv = 1,
    .fccu_clkdiv = 1,
    .fperipheral_clkdiv = 1};

void SysTick_Handler(void) { CORE_TIME_VARIABLE++; }

void SystemCoreClockSetup(void) {
  /* Setup settings for USB clock */
  XMC_SCU_CLOCK_Init(&clock_config);

  XMC_SCU_CLOCK_EnableUsbPll();
  XMC_SCU_CLOCK_StartUsbPll(2, 64);
  XMC_SCU_CLOCK_SetUsbClockDivider(4);
  XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

  SystemCoreClockUpdate();
}

uint32_t get_system_time(void) { return CORE_TIME_VARIABLE; }
