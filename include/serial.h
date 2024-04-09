#include "stm8.h"

// Both assume f_master to be 16000000.
// If you have a lower f_master divide the baudrate accordingly.
#define UART_BRR(baud) ((16000000l + baud / 2) / baud)
#define UART_BRR2(baud) \
  ((UART_BRR(baud) & 0xf000) >> 8 | (UART_BRR(baud) & 0xf))
#define UART_BRR1(baud) ((UART_BRR(baud) >> 4) & 0xff)

#define SERIAL_INIT(baud_rate)      \
  do {                              \
    UART1_CR2 = UART_CR2_TEN;       \
    UART1_BRR2 = UART_BRR2(baud_rate); \
    UART1_BRR1 = UART_BRR1(baud_rate); \
  } while (0);
