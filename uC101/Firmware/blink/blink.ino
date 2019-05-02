//////////////////////////////////////////////////////////////
//                        Arduino Blink                     //
//////////////////////////////////////////////////////////////
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

//////////////////////////////////////////////////////////////
//                        Bare Bones                        //
//////////////////////////////////////////////////////////////
//#include <util/delay.h>
//
//#define F_CPU 16000000UL // 16 MHz
//
//void setup() 
//{
//  DDRD |= 1<<3;
//}
//
//void loop() 
//{
//  PORTD &= ~(1<<3);
//  _delay_ms(500);
//  PORTD |= (1<<3);
//  _delay_ms(500);
//}

//////////////////////////////////////////////////////////////
//                        DIY Blink                         //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include <util/delay.h>
//
//#define F_CPU 16000000UL // 16 MHz
//
//void setup() 
//{
//  dirOut(LED_RED_PORT,LED_RED);
//}
//
//void loop() 
//{
////  setBit(LED_RED_PORT,LED_RED);
////  _delay_ms(500);
////  clearBit(LED_RED_PORT,LED_RED);
////  _delay_ms(500);
//  toggleBit(LED_RED_PORT,LED_RED);
//  _delay_ms(500);
//}

//////////////////////////////////////////////////////////////
//                      Improved Blink                      //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include <util/delay.h>
//
//#define F_CPU 16000000UL // 16 MHz
//
//void setup() 
//{
//  dirOut(LED_RED_PORT,LED_RED);
//}
//
//void loop() 
//{
//  ledOn(LED_RED);
//  _delay_ms(500);
//  ledOff(LED_RED);
//  _delay_ms(500);
////  ledToggle(LED_RED);
////  _delay_ms(500);
//}

//////////////////////////////////////////////////////////////
//                   Blink without delay                    //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include "timer.h"
//
//#define F_CPU 16000000UL // 16 MHz
//
//// Variables for timing
//uint32_t previousTime = 0;
//const uint16_t interval = 500;
//
//void setup() 
//{
//  dirOut(LED_BLUE_PORT,LED_BLUE);
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
//    ledToggle(LED_BLUE);
//    _delay_ms(500);
//  }
//}

//////////////////////////////////////////////////////////////
//                      Empty Program                       //
//////////////////////////////////////////////////////////////

//void setup() 
//{
//  
//}
//
//void loop() 
//{
//  
//}

//////////////////////////////////////////////////////////////
//                   Need for Speed                         //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include "button.h"
//#include <util/delay.h>
//
//#define F_CPU 16000000UL // 16 MHz
//
//// Structs for each button
//extern struct buttonStruct button1 = {.port = &BUTTON_1_PORT, .pin = BUTTON_1};
//extern struct buttonStruct button2 = {.port = &BUTTON_2_PORT, .pin = BUTTON_2};
//
//// ISR to poll buttons
//volatile uint8_t sample = 0;  // For clock division
//
//ISR(TIMER2_OVF_vect)
//{
//  // Nasty clock division to decrease sample rate
//  if (!sample)
//  {
//    pollButton(&button1);
//    pollButton(&button2);
//    sample = 4;
//  }
//  sample--;
//}
//
//void setup() 
//{
//  dirIn(BUTTON_1_PORT, BUTTON_1);
//  dirIn(BUTTON_2_PORT, BUTTON_2);
//  dirOut(LED_BLUE_PORT, LED_BLUE); 
//  ledOff(LED_BLUE);
//  
//  buttonPollingInit();
//}
//
//void loop() 
//{
//  if (button1.rising)
//  {
//    button1.rising = 0;
//    ledOn(LED_BLUE);
//    _delay_ms(1);
//    ledOff(LED_BLUE);
//    digitalWrite(LED_BLUE,LOW);
//    _delay_ms(10);
//    ledOff(LED_BLUE);
//  }
//
//  if (button2.rising)
//  {
//    button2.rising = 0;
//    ledOn(LED_BLUE);
//    _delay_ms(1);
//    ledOff(LED_BLUE);
//    ledOn(LED_BLUE);
//    _delay_ms(10);
//    ledOff(LED_BLUE);
//  }
//}
