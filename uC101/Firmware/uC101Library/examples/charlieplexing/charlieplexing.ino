////////////////////////////////////////////////////////////////
////            Blink, Charlieplexing Edition                 //
////////////////////////////////////////////////////////////////
#include "uC101.h"
#include <avr/io.h>

void setup() {
}

void loop() 
{  
  setLED(1);
  _delay_ms(1000);
  setLED(0);
  _delay_ms(1000);

}

uint8_t setLED(uint8_t led)
{
  if (led > 9)
  return -1;

  // Below pins map the position on the dev board (top left 1, top right 3, etc) to their ports
  // To turn on a single LED, High Z all pins, then set pinHigh to VCC, pinLow to GND.
  uint8_t pinHigh[9] = {CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_2,CHARLIE_3,CHARLIE_4,CHARLIE_2};
  uint8_t pinLow[9]  = {CHARLIE_4,CHARLIE_4,CHARLIE_2,CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_3};

  PORTC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));  // Outputs low / pullups off
  DDRC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));   // Set all high Z

  if (led)
  DDRC |= _BV(pinHigh[led-1]) | _BV(pinLow[led-1]);  // Set pins as outputs
  PORTC |= _BV(pinHigh[led-1]); // Pull to VCC  
  PORTC &= ~_BV(pinLow[led-1]); // Pull to GND  
}

//////////////////////////////////////////////////////////////
//                    Multiple LEDs                         //
//////////////////////////////////////////////////////////////

// #include "uC101.h"
// #include <avr/io.h>
//
// void setup() {
// }
//
// void loop() 
// {  
//  for(uint8_t i = 1; i <=9; i++)
//  {
//    setLED(i);
//    _delay_us(500);
//  }
//
// }
//
// uint8_t setLED(uint8_t led)
// {
//   if (led > 9)
//   return -1;
//
//   // Below pins map the position on the dev board (top left 1, top right 3, etc) to their ports
//   // To turn on a single LED, High Z all pins, then set pinHigh to VCC, pinLow to GND.
//   uint8_t pinHigh[9] = {CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_2,CHARLIE_3,CHARLIE_4,CHARLIE_2};
//   uint8_t pinLow[9]  = {CHARLIE_4,CHARLIE_4,CHARLIE_2,CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_3};
//
//   PORTC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));  // Outputs low / pullups off
//   DDRC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));   // Set all high Z
//
//   if (led)
//   	DDRC |= _BV(pinHigh[led-1]) | _BV(pinLow[led-1]);  // Set pins as outputs
//   	PORTC |= _BV(pinHigh[led-1]); // Pull to VCC  
//   	PORTC &= ~_BV(pinLow[led-1]); // Pull to GND  
// }

////////////////////////////////////////////////////////////////
////                    Changing LEDs                         //
////////////////////////////////////////////////////////////////
//
//#include "uC101.h"
//#include "timer.h"
//#include <avr/io.h>
//
//// Variables for timing
//uint32_t previousTime = 0;
//const uint16_t interval = 500;
//
//uint8_t numLED = 0;
//uint8_t enable = 1;
//
//void setup() {
//  timerInit();
//}
//
//void loop() 
//{  
//  uint32_t currentTime = timerMilliseconds();
//  
//  if (currentTime - previousTime >= interval)
//  {
//    previousTime = currentTime;
//    (numLED < 9) ? numLED++ : numLED = 0;
//  }
//  for (uint8_t pos = 0; pos <= numLED; pos++)    // Comment this line out and below two in for constant intensity
////  for (uint8_t pos = 0; pos <= 9; pos++)
//  {
////    (pos <= numLED) ? enable = 1 : enable = 0;
//    setLED(pos,enable);
//    _delay_us(500);
//  }
//
//}
//
//uint8_t setLED(uint8_t led, uint8_t enable)
//{
//  if (led > 9)
//  return -1;
//
//  uint8_t pinHigh[9] = {CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_2,CHARLIE_3,CHARLIE_4,CHARLIE_2};
//  uint8_t pinLow[9]  = {CHARLIE_4,CHARLIE_4,CHARLIE_2,CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_3};
//
//  PORTC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));  // Outputs low / pullups off
//  DDRC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));   // Set all high Z
//
//  if (led && enable)
//  DDRC |= _BV(pinHigh[led-1]) | _BV(pinLow[led-1]);
//  PORTC |= _BV(pinHigh[led-1]); // Pull to VCC  
//  PORTC &= ~_BV(pinLow[led-1]); // Pull to GND  
//}
