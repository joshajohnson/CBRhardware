#include "uC101.h"
#include <util/delay.h>

#define F_CPU 16000000UL // 16 MHz

void setup() {
  dirOut(LED_RED_PORT,LED_RED);
  dirIn(BUTTON_1_PORT,BUTTON_1);
}

void loop() {
  if (readBit(BUTTON_1_PORT,BUTTON_1))
  {
    setBit(LED_RED_PORT,LED_RED);
    _delay_ms(100);
  }
  else
  {
    clearBit(LED_RED_PORT,LED_RED);
    _delay_ms(100);
  }
}
