nim c --forceBuild --os:standalone --cpu:arm --gc:none --compileOnly --path:..\LTE\nim --define:release .\main.nim

move .\nimcache\*.c .\
rmdir /s /q nimcache

make

del /q .\*.c
rmdir /s /q .obj

del .\project.bin
del .\project.elf
del .\project.ihex
