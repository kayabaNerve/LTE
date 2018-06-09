import Tomu
import LED
import Serial

proc strcmp(str1: cstring, str2: cstring): int {.header: "<string.h>", importc: "strcmp".}

var
    connected: bool = false
    line: cstring
proc runEveryMillisecond() {.cdecl.} =
    if (Serial.isConnected()) and (connected == false):
        connected = true;
        Serial.send("What is my favorite fruit?\r\n> ")

    line = Serial.read()
    while line != nil:
        if (strcmp(line, "apple") == 0):
            LED.turnRedOff();
            LED.turnGreenOn();
            Serial.send("Correct!");
            Tomu.finish()
        else:
            LED.turnRedOn();
            Serial.send("Try again!\r\n> ");
        line = Serial.read()

Tomu.setRun(runEveryMillisecond)

Tomu.loop()
