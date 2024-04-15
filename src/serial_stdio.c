// To support the stdio.h interface that enable printf/puts etc.
#include "serial.h"

// Providing the symbols in a separate file in the Arduino lib
// makes them weak symbols, i.e. another implementation that’s
// directly linked will take precedence over these.
int putchar(int c) { uart_write(c); return c; }
int getchar(void) { return uart_read(); }