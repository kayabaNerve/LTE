#ifndef LTE_SERIAL
#define LTE_SERIAl

#include <stdbool.h>

void Serial();
bool serialConnected();

char* readSerial();
char* sendSerial();

#endif
