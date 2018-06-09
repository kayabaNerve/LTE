# LTE

To install:

- Install dfu-util and dfu-suffix.
- Download the GCC cross compiler and make.
- Grab the quickstart repo from https://github.com/im-tobu
- Place LTE inside of the quickstart repo
- Replace the quickstart makefile with the one from LTE

To use with C:

- Create a project folder inside the quickstart repo.
- Create your main.c file (or main.cpp).
- Include the tomu.h header as so: `#include <tomu.h>`.
- Call `tomu()` inside your main function.
- End your main function with `loop()`.

To compile C:

- Create a makefile in your project folder.
- Only enter one line. `include ../Makefile.common`.
- Run make from inside the project folder.

To use with Nim:

- Create a project folder inside the quickstart repo.
- Create your main.nim file.
- Import the tomu header as so: `import Tomu`.
- Write your code. tomu() will be automatically called.
- End your code with `Tomu.loop()`.

To compile Nim:

If it is your first time compiling, edit Makefile.common. Line 23 has a commented `-IPATH_TO_YOUR_NIM\lib`. Remove the `#` and enter the path to your Nim install's /lib.

- Copy panicoverride.nim from the Base sample.
- Create a makefile in your project folder.
- Only enter one line. `include ../Makefile.common`.
- EITHER
- Copy the compile script for your OS from Base and run it (these will delete all generated files, except for the .dfu target, including \*.c).
- OR
- Compile the Nim with `nim c --forceBuild --os:standalone --cpu:arm --gc:none --compileOnly --path:..\LTE\nim --define:release .\main.nim`.
- Move all the generated C code from nimcache/ to your project folder.
- Run make.

To run it on a Tomu:

- Find the generated .dfu file.
- Run `dfu-util -D .\GENERATED_DFU.dfu` in a terminal.

All of the headers are C and guaranteed to work in C and Nim.
If a C sample has a C++ file extension, it means that sample works in C++.
Not all headers are guaranteed to work in C++.
