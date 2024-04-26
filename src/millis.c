#include "stm8.h"
#include <stdint.h>

uint16_t millis(void) {
  static uint8_t millis_inited = 0;
  if (!millis_inited) {
    // prescaling: 16 MHz / 16000 -> 1ms
    TIM1_PSCRH = 16000 >> 8;
    TIM1_PSCRL = 16000 & 0xff;
    TIM1_EGR |= TIM_EGR_UG; // load new PSCR value
    TIM1_CR1 = TIM_CR1_CEN; // enable the counter
    millis_inited = 1;
  }
  return (TIM1_CNTRH << 8) | TIM1_CNTRL;
}