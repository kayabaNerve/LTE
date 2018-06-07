#ifndef LTE_LED
#define LTE_LED

#include <stdbool.h>

#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/efm32/gpio.h>

#define GREEN_LED GPIOA
#define GREEN_PIN GPIO0
#define RED_LED   GPIOB
#define RED_PIN   GPIO7

bool greenLed = false;
bool redLed = false;

void toggleGreen() {
    greenLed = !greenLed;
    gpio_toggle(GREEN_LED, GREEN_PIN);
}

void turnGreenOn() {
    if (greenLed == true) {
        return;
    }
    toggleGreen();
}

void turnGreenOff() {
    if (greenLed == false) {
        return;
    }
    toggleGreen();
}

void toggleRed() {
    redLed = !redLed;
    gpio_toggle(RED_LED, RED_PIN);
}

void turnRedOn() {
    if (redLed == true) {
        return;
    }
    toggleRed();
}

void turnRedOff() {
    if (redLed == false) {
        return;
    }
    toggleRed();
}

void led() {
    gpio_mode_setup(RED_LED, GPIO_MODE_WIRED_AND, RED_PIN);
    gpio_set(RED_LED, RED_PIN);
    gpio_clear(RED_LED, RED_PIN);
    gpio_toggle(RED_LED, RED_PIN);

    gpio_mode_setup(GREEN_LED, GPIO_MODE_WIRED_AND, GREEN_PIN);
    gpio_set(GREEN_LED, GREEN_PIN);
    gpio_clear(GREEN_LED, GREEN_PIN);
    gpio_toggle(GREEN_LED, GREEN_PIN);
}

#endif
