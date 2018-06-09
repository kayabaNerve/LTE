#include <stdbool.h>

#include <libopencm3/efm32/gpio.h>

int GREEN_LED = GPIOA;
int GREEN_PIN = GPIO0;
int RED_LED = GPIOB;
int RED_PIN = GPIO7;
bool greenLED, redLED;

void toggleGreenLED() {
    greenLED = !greenLED;
    gpio_toggle(GREEN_LED, GREEN_PIN);
}

void turnGreenLEDOn() {
    if (greenLED == true) {
        return;
    }
    toggleGreenLED();
}

void turnGreenLEDOff() {
    if (greenLED == false) {
        return;
    }
    toggleGreenLED();
}

void toggleRedLED() {
    redLED = !redLED;
    gpio_toggle(RED_LED, RED_PIN);
}

void turnRedLEDOn() {
    if (redLED == true) {
        return;
    }
    toggleRedLED();
}

void turnRedLEDOff() {
    if (redLED == false) {
        return;
    }
    toggleRedLED();
}

void LED() {
    gpio_mode_setup(RED_LED, GPIO_MODE_WIRED_AND, RED_PIN);
    gpio_set(RED_LED, RED_PIN);

    gpio_mode_setup(GREEN_LED, GPIO_MODE_WIRED_AND, GREEN_PIN);
    gpio_set(GREEN_LED, GREEN_PIN);

    greenLED = false;
    redLED = false;
}
