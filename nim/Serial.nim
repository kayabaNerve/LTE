proc cSerial() {.header: "serial.h", importc: "Serial".}
cSerial()

proc isConnected*(): bool {.header: "serial.h", importc: "serialConnected".}
proc read*(): cstring {.header: "serial.h", importc: "readSerial".}
proc send*(data: cstring) {.header: "serial.h", importc: "sendSerial".}
