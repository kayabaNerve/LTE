#ifndef LTE_LED
#define LTE_LED

#include <stdbool.h>

#include <libopencm3/efm32/gpio.h>

struct LEDHeaderStruct {
    int GREEN_LED, GREEN_PIN, RED_LED, RED_PIN;
    bool greenLED, redLED;
} LEDHeader;

void toggleGreenLED() {
    LEDHeader.greenLED = !LEDHeader.greenLED;
    gpio_toggle(LEDHeader.GREEN_LED, LEDHeader.GREEN_PIN);
}

void turnGreenLEDOn() {
    if (LEDHeader.greenLED == true) {
        return;
    }
    toggleGreenLED();
}

void turnGreenLEDOff() {
    if (LEDHeader.greenLED == false) {
        return;
    }
    toggleGreenLED();
}

void toggleRedLED() {
    LEDHeader.redLED = !LEDHeader.redLED;
    gpio_toggle(LEDHeader.RED_LED, LEDHeader.RED_PIN);
}

void turnRedLEDOn() {
    if (LEDHeader.redLED == true) {
        return;
    }
    toggleRedLED();
}

void turnRedLEDOff() {
    if (LEDHeader.redLED == false) {
        return;
    }
    toggleRedLED();
}

void LED() {
    LEDHeader.GREEN_LED = GPIOA;
    LEDHeader.GREEN_PIN = GPIO0;
    LEDHeader.RED_LED = GPIOB;
    LEDHeader.RED_PIN = GPIO7;

    gpio_mode_setup(LEDHeader.RED_LED, GPIO_MODE_WIRED_AND, LEDHeader.RED_PIN);
    gpio_set(LEDHeader.RED_LED, LEDHeader.RED_PIN);

    gpio_mode_setup(LEDHeader.GREEN_LED, GPIO_MODE_WIRED_AND, LEDHeader.GREEN_PIN);
    gpio_set(LEDHeader.GREEN_LED, LEDHeader.GREEN_PIN);

    LEDHeader.greenLED = false;
    LEDHeader.redLED = false;
}

#endif
