#ifndef LTE_TOMU
#define LTE_TOMU

#include <stddef.h>

#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/efm32/wdog.h>
#include <libopencm3/efm32/cmu.h>

#include <toboot.h>
TOBOOT_CONFIGURATION(0);

struct TomuHeaderStruct {
    void (*run)();
} TomuHeader;

void setRun(void (*runArg)()) {
    TomuHeader.run = runArg;
}

void sys_tick_handler() {
    if (TomuHeader.run != NULL) {
        (*TomuHeader.run)();
    }
}

void Tomu() {
    TomuHeader.run = NULL;

    WDOG_CTRL = 0;

    cmu_periph_clock_enable(CMU_GPIO);

    cmu_osc_on(USHFRCO);
    cmu_wait_for_osc_ready(USHFRCO);
    CMU_USBCRCTRL = CMU_USBCRCTRL_EN;
    CMU_CMD = CMU_CMD_HFCLKSEL(5);
    while (!(CMU_STATUS & CMU_STATUS_USHFRCODIV2SEL));

    systick_set_frequency(1000, 24000000);
    systick_counter_enable();
    systick_interrupt_enable();
}

void loop() {
    while (true);
}

#endif
