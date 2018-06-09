#include <stdbool.h>
#include <string.h>

#include <tomu.h>
#include <led.h>
#include <Serial.h>

bool connected = false;
void runEveryMillisecond() {
    if ((serialConnected()) && (connected == false)) {
        connected = true;
        sendSerial("What is my favorite fruit?\r\n> ");
    }
    char* line;
    while ((line = readSerial()) != NULL) {
        if (strcmp((const char*) line, "apple") == 0) {
            turnRedLEDOff();
            turnGreenLEDOn();
            sendSerial("Correct!");
            end();
        } else {
            turnRedLEDOn();
            sendSerial("Try again!\r\n> ");
        }
    }
}

int main() {
    Tomu();
    LED();
    Serial();

    setRun(&runEveryMillisecond);

    loop();
}
