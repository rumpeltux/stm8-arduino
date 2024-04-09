#include "serial.h"

#include "stm8.h"

extern void handle_events();

int putchar(int c) {
  sim();
  UART1_CR2 |= UART_CR2_TIEN;  // Enable interrupts for TX empty
  while (!(UART1_SR & UART_SR_TXE)) {
    wfi();
    sim();
    handle_events();
  }
  rim();
  // Then, write the byte to the data register.
  UART1_DR = c;
  return c;
}
