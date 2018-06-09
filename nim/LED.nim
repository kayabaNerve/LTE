proc cLED() {.header: "led.h", importc: "LED".}
cLED();

proc turnRedOn*() {.header: "led.h", importc: "turnRedLEDOn".}
proc turnRedOff*() {.header: "led.h", importc: "turnRedLEDOff".}
proc turnGreenOn*() {.header: "led.h", importc: "turnGreenLEDOn".}
proc turnGreenOff*() {.header: "led.h", importc: "turnGreenLEDOn".}
