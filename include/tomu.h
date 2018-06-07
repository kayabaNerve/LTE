#ifndef LTE_TOMU
#define LTE_TOMU

#include <stddef.h>

#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/efm32/wdog.h>
#include <libopencm3/efm32/cmu.h>

#define SYSTICK_FREQUENCY 1000
#define AHB_FREQUENCY 14000000

#include <toboot.h>
TOBOOT_CONFIGURATION(0);

void (*run)() = NULL;
void setRun(void (*runArg)()) {
    run = runArg;
}

void sys_tick_handler() {
    if (!(run)) {
        return;
    }

    (*run)();
}

void tomu() {
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
