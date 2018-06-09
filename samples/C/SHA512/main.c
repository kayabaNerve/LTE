#include <stdlib.h>

#include <tomu.h>
#include <serial.h>

#include "sha512.h"

char* line;
void run() {
    if (serialConnected()) {
        if ((line = readSerial()) != NULL) {
            sendSerial(sha512(line));
            sendSerial("\r\n");
        }
    }
}

int main() {
    Tomu();
    Serial();
    setRun(&run);
    loop();
}
