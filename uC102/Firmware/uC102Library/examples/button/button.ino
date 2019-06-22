//////////////////////////////////////////////////////////////
//                      Basic Button                        //
//////////////////////////////////////////////////////////////
#include "uC101.h"
#include <util/delay.h>

#define F_CPU 16000000UL // 16 MHz

void setup() {
  dirOut(LED_RED_PORT,LED_RED);
  dirIn(BUTTON_1_PORT,BUTTON_1);
  ledOff(LED_RED);
}

void loop() {
  if (digitalRead(2))
//  if (PIND & (1<<BUTTON_1))
//  if (readPin(BUTTON_1_PORT,BUTTON_1))
  {
    ledToggle(LED_RED);
  }
}

//////////////////////////////////////////////////////////////
//              Basic Button with Delay                     //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include <util/delay.h>
//
//#define F_CPU 16000000UL // 16 MHz
//
//void setup() {
//  dirOut(LED_RED_PORT,LED_RED);
//  dirIn(BUTTON_1_PORT,BUTTON_1);
//  ledOff(LED_RED);
//}
//
//void loop() {
//  if (readPin(BUTTON_1_PORT,BUTTON_1))
//  {
//    ledToggle(LED_RED);
//    _delay_ms(500);
//  }
//}

//////////////////////////////////////////////////////////////
//                 Button with Interrupt                    //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include <util/delay.h>
//
//#define F_CPU 16000000UL // 16 MHz
//
//ISR(INT0_vect)
//{
//  // DONT DO THIS
//  cli();
//  ledToggle(LED_RED);
//  _delay_ms(500); 
//  sei();
//}
//
//void setup() {
//  dirOut(LED_RED_PORT,LED_RED);
//  dirIn(BUTTON_1_PORT,BUTTON_1);
//  ledOff(LED_RED);
//
//  // Setup ISR
//  EICRA = _BV(ISC01) | _BV(ISC00);  // Trigger on rising edge on INT0 (Button1)
//  EIMSK = _BV(INT0);                // Enable INT0 interrupt
//  sei();                            // Enable interrupts
//  
//}
//
//void loop() {
//  _delay_ms(100); // Pretend to be busy
//}

//////////////////////////////////////////////////////////////
//                  Smarter debouncer                       //
//////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include "button.h"
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
//  dirOut(LED_GREEN_PORT, LED_GREEN);
//  dirOut(LED_RED_PORT, LED_RED);
//
//  ledOff(LED_BLUE);
//  ledOff(LED_GREEN);
//  ledOff(LED_RED);
//  buttonPollingInit();
//}
//
//void loop() 
//{
//  if (button1.rising)
//  {
//    button1.rising = 0;
//    ledToggle(LED_BLUE);
//  }
//
//  if (button2.falling)
//  {
//    button2.falling = 0;
//    ledToggle(LED_GREEN);
//  }
//
//	  // If both buttons pressed
////  if ((button1.on && button2.rising) || (button1.rising && button2.on) || (button1.rising && button2.rising))  	
////  {
////    button1.rising = 0;
////    button2.rising = 0;
////    ledToggle(LED_GREEN);
////  }
//}
