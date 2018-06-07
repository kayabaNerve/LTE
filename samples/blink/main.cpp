#include <stdbool.h>

#include <tomu.h>
#include <led.h>

uint32_t milliseconds = 0;
bool on = false;
void runEveryMilisecond() {
    milliseconds++;

    if ((milliseconds % 5000) == 0) {
        on = !on;
        if (on) {
            turnGreenLEDOn();
            turnRedLEDOn();
        } else {
            turnGreenLEDOff();
            turnRedLEDOff();
        }
    }
}

int main() {
    Tomu();
    LED();
    setRun(&runEveryMilisecond);

    loop();
}
