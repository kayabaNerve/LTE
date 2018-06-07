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
            turnGreenOn();
            turnRedOn();
        } else {
            turnGreenOff();
            turnRedOff();
        }
    }
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    tomu();
    led();
    setRun(&runEveryMilisecond);

    loop();
}
