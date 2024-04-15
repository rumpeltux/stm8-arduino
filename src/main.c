#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Arduino.h"
#include "stm8.h"

extern void (*isr_callbacks[4])();
extern uint8_t arduino_pending_events;

// sdcc requires all interrupt handlers to be defined in the same file that
// includes the main() function.

uint8_t triggered_interrupts = 0;

ISR(timer2_isr, TIM2_OVR_UIF_vector) {
  TIM2_SR1 &= ~TIM_SR1_UIF;  // clear interrupt flag
  triggered_interrupts = 1;
}

ISR(gpioA_isr, EXTI_PORTA_vector) { arduino_pending_events |= 1 << 0; }

ISR(gpioB_isr, EXTI_PORTB_vector) { arduino_pending_events |= 1 << 1; }

ISR(gpioC_isr, EXTI_PORTC_vector) { arduino_pending_events |= 1 << 2; }

ISR(gpioD_isr, EXTI_PORTD_vector) { arduino_pending_events |= 1 << 3; }

ISR(adc_isr, ADC1_EOC_vector) {
  // Disable the interrupt leaving the ADC_CSR_EOC flag intact
  ADC_CSR &= ~ADC_CSR_EOCIE;
}

ISR(uart1_isr_tx, UART1_T_TXE_vector) {
  // Disable the interrupt leaving the UART_SR_TXE flag intact.
  UART1_CR2 &= ~UART_CR2_TIEN;
}

ISR(uart1_isr_rx, UART1_R_RXNE_vector) {
  // Disable the interrupt leaving the UART_SR_RXNE flag intact.
  UART1_CR2 &= ~UART_CR2_RIEN;
}

ISR(awu_isr, AWU_vector) {
  if (AWU_CSR & AWU_CSR_AWUF) {
    triggered_interrupts |= 2;
  }
  AWU_CSR = 0;
  AWU_TBR = 0;
}

extern void loop();
extern void setup();

static void event_loop() {
  while (1) {
    yield();
    enableInterrupts();
    loop();
  }
}

void main() {
  CLK_CKDIVR = 0x00;  // Set the frequency to 16 MHz
  enableInterrupts();

  setup();
  event_loop();
}
