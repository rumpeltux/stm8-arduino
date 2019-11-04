#include "Arduino.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm8.h"

void (*isr_callbacks[4])() = {(void *)0, (void *)0, (void *)0, (void *)0};
void (*event_loop_next)() = (void *)0;

// All interrupt handlers must be defined in the same file that
// includes the main() function.

ISR(timer2_isr, TIM2_OVR_UIF_vector) {
  TIM2_SR1 &= ~TIM_SR1_UIF;  // clear interrupt flag
}

ISR(gpioA_isr, EXTI_PORTA_vector) { event_loop_next = isr_callbacks[0]; }

ISR(gpioB_isr, EXTI_PORTB_vector) { event_loop_next = isr_callbacks[1]; }

ISR(gpioC_isr, EXTI_PORTC_vector) { event_loop_next = isr_callbacks[2]; }

ISR(gpioD_isr, EXTI_PORTD_vector) { event_loop_next = isr_callbacks[3]; }

ISR(adc_isr, ADC1_EOC_vector) {
  // Disable the interrupt leaving the ADC_CSR_EOC flag intact
  ADC_CSR &= ~ADC_CSR_EOCIE;
}

ISR(uart1_isr, UART1_T_TXE_vector) {
  // Disable the interrupt leaving the UART_SR_TXE flag intact.
  UART1_CR2 &= ~UART_CR2_TIEN;
}

extern void loop();
extern void setup();

void handle_events() {
  if (event_loop_next) {
    (*event_loop_next)();
  }
  event_loop_next = (void *)0;
}

static void event_loop() {
  while (1) {
    handle_events();
    loop();
  }
}

void main() {
  CLK_CKDIVR = 0x00;   // Set the frequency to 16 MHz
  CLK_PCKENR1 = 0xFF;  // Enable peripherals
  rim();               // Enable interrupts.

  setup();
  event_loop();
}

void yield() { handle_events(); }
