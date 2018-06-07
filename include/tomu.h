#ifndef LTE_TOMU
#define LTE_TOMU

#include <stddef.h>

#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/efm32/wdog.h>
#include <libopencm3/efm32/cmu.h>

//How often to cause a tick.
//714 is roughly every 1 milisecond, however 700 is round.
//It should be noted this isn't perfect as Tomus don't have crystals.
//A variance of 0.05 seconds per second is expected.
#define SYSTICK_FREQUENCY 700

//Core clock frequency.
#define AHB_FREQUENCY 14000000

#include <toboot.h>
TOBOOT_CONFIGURATION(0);

struct TomuHeaderStruct {
    void (*run)();
} TomuHeader;

void setRun(void (*runArg)()) {
    TomuHeader.run = runArg;
}

void sys_tick_handler() {
    if (!(TomuHeader.run)) {
        return;
    }

    (*TomuHeader.run)();
}

void Tomu() {
    TomuHeader.run = NULL;

    WDOG_CTRL = 0;

    cmu_periph_clock_enable(CMU_GPIO);

    systick_set_frequency(SYSTICK_FREQUENCY, AHB_FREQUENCY);
    systick_counter_enable();
    systick_interrupt_enable();
}

void loop() {
    while(true){}
}

#endif
