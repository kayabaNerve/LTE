#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <tomu.h>
#include <led.h>

int randNum = 0;
bool on = false;
uint32_t milliseconds = 0;
void runEveryMillisecond() {
    milliseconds++;

    if ((milliseconds % 1000) == 0) {
        if (on) {
            turnGreenLEDOff();
            on = false;

            return;
        }

        if (randNum > 0) {
            turnGreenLEDOn();
            on = true;

            randNum--;
        }
    }
}

int main() {
    Tomu();
    LED();

    //This will always be the same.
    //Tomu spawns with the same random seed always.
    //Each call to rand builds entropy and changes the output.
    //That said, you can definitively say the output for call 1 is X, call 2 is Y...
    randNum = (rand() % 10) + 1;

    setRun(&runEveryMillisecond);

    loop();
}
