#include "delay.h"

#include "Arduino.h"
#include "stm8.h"

static void delayPrescaled(uint16_t time, uint8_t scale) {
  if (!time) return;
  time--;
  TIM2_PSCR = scale;
  TIM2_EGR |= TIM_EGR_UG;  // load new PSCR value
  TIM2_ARRH = time >> 8;
  TIM2_ARRL = time;

  sim();
  // TIM2_IER (Interrupt Enable Register), Update interrupt (UIE) (bit 0)
  TIM2_IER |= TIM_IER_UIE;
  // TIM2_CR1 – Timer 2 Control Register 1
  // Counter ENable bit (CEN) (bit 0)
  // One Pulse Mode (counter stops after count down)
  TIM2_CR1 = TIM_CR1_CEN | TIM_CR1_OPM;
}

static void finishDelay() {
  // loop while the timer i still active
  while ((TIM2_CR1 & TIM_CR1_CEN) != 0) {
    handle_events();
  }
  rim();
}

void setTimeoutMicroseconds(uint16_t time) {
  delayPrescaled(time, 4);  // prescale 2^4 = 16
}

void delayMicroseconds(uint16_t time) {
  delayPrescaled(time, 4);  // prescale 2^4 = 16
  finishDelay();
}

// delay millis
void delay(uint16_t time) {
  // TODO: use delayPrescaled directly
  while (time > 65) {
    delayMicroseconds(65000); // minus ~32 cycles @16MHz
    time -= 65;
  }
  delayMicroseconds(time * 1000);
}
