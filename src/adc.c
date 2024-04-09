#include "adc.h"

#include "stm8.h"

// We only use 8-bit accuracy.
uint8_t analogRead(uint8_t channel) {
  // Enable interrupts, and turn on ADC
  ADC_CSR = channel | ADC_CSR_EOCIE;
  ADC_CR1 |= ADC_CR1_ADON;  // wake up from power-down
  sim();
  ADC_CR1 |= ADC_CR1_ADON;  // start conversion
  while ((ADC_CSR & ADC_CSR_EOC) == 0) {
    wfi();
    sim();
  }
  uint8_t result = ADC_DRH;
  ADC_CSR &= ~ADC_CSR_EOCIE; // disable ADC interrupts
  ADC_CR1 &= ~ADC_CR1_ADON;  // Put the ADC to sleep.
  rim();
  return result;
}
