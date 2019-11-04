#include "serial.h"

#include "stm8.h"

extern void handle_events();

int putchar(int c) {
  UART1_CR2 |= UART_CR2_TIEN;  // Flag is cleared by interrupt handler.
  while (!(UART1_SR & UART_SR_TXE)) {
    wfi();
  }
  // Then, write the byte to the data register.
  UART1_DR = c;
  return c;
}
