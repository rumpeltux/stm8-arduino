#include "serial.h"

#include "stm8.h"

extern void handle_events(void);

void uart_write(uint8_t c) {
  disableInterrupts();
  UART1_CR2 |= UART_CR2_TIEN;  // Enable interrupts for TX empty
  while (!(UART1_SR & UART_SR_TXE)) {
    wfi();
    handle_events();
  }
  enableInterrupts();
  // Then, write the byte to the data register.
  UART1_DR = c;
}

uint8_t uart_read(void) {
  disableInterrupts();
  UART1_CR2 |= UART_CR2_RIEN | UART_CR2_REN;
  // Wait until an interrupt signals us that RX data register is not empty
  while (!(UART1_SR & UART_SR_RXNE)) {
    wfi();
    handle_events();
  }
  enableInterrupts();
  return UART1_DR;
}
