proc cTomu() {.header: "tomu.h", importc: "Tomu".}
cTomu()

proc setRun*(runArg: proc() {.cdecl.}) {.header: "tomu.h", importc: "setRun".}
proc loop*() {.header: "tomu.h", importc: "loop".}
proc finish*() {.header: "tomu.h", importc: "end".}
