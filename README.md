# LTE

To install:

- Install dfu-util and dfu-suffix.
- Download the GCC cross compiler and make.
- Grab the quickstart repo from https://github.com/im-tobu
- Place LTE inside of the quickstart repo
- Replace the quickstart makefile with the one from LTE

To use:

- Create a project folder inside the quickstart repo.
- Create your main.c file (or main.cpp).
- Include the tomu.h header as so: `#include <tomu.h>`
- Call `tomu()` inside your main function.
- End your main function with `loop()`.

To compile:

- Create a makefile in your project folder.
- Only enter one line. `include ../Makefile.common`.
- Run make from inside the project folder.

To run it on a Tomu:

- Find the generated .dfu file.
- Run `dfu-util -D .\GENERATED_DFU.dfu` in a terminal.

The samples are all C++ files, yet the headers are C, and guaranteed to work with C.
