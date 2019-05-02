//////////////////////////////////////////////////////////////
//                        Arduino Blink                     //
//////////////////////////////////////////////////////////////

// the setup function runs once when you press reset or power the board
//void setup() {
//  // initialize digital pin LED_BUILTIN as an output.
//  pinMode(LED_BUILTIN, OUTPUT);
//}
//
//// the loop function runs over and over again forever
//void loop() {
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second
//}

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
#include "uC101.h"
#include <util/delay.h>

#define F_CPU 16000000UL // 16 MHz

void setup() 
{
  dirOut(LED_RED_PORT,LED_RED);
}

void loop() 
{
//  setBit(LED_RED_PORT,LED_RED);
//  _delay_ms(500);
//  clearBit(LED_RED_PORT,LED_RED);
//  _delay_ms(500);
  toggleBit(LED_RED_PORT,LED_RED);
  _delay_ms(500);
}

//////////////////////////////////////////////////////////////
//                        Empty Program                     //
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
