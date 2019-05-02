///////////////////////////////////////////////////////////////////////////////
//                             Basic Encoder                                 //
///////////////////////////////////////////////////////////////////////////////
#include "uC101.h"
#include "button.h"
#include "pwmLED.h"
#include "rotaryEncoder.h"

#define F_CPU 16000000UL // 16 MHz

// Structs for each button
extern struct encoderStruct encoder = {.port1 = &ENCODER_B_PORT, .pin1 = ENCODER_B, .port2 = &ENCODER_A_PORT, .pin2 = ENCODER_A};

// ISR to poll buttons
ISR(TIMER2_OVF_vect) // 1kHz
{
  pollEncoder(&encoder); 
  calculateEncoder(&encoder);
}

// ISR to poll encoder
ISR (TIMER1_COMPB_vect) // 250 kHz
{
//  pollEncoder(&encoder); 
//  calculateEncoder(&encoder);
} 

// To control RGB colour
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;
uint8_t stepSize = 16;  // Brightness per click, must be 2^n

void setup() 
{
  dirIn(ENCODER_A_PORT,ENCODER_A);
  dirIn(ENCODER_B_PORT,ENCODER_B);
 
  buttonPollingInit();
  encoderPollInit();
  pwmSetup();
}

void loop() 
{
  // Update encoder before making decisions
//  calculateEncoder(&encoder);
//  encoderFSM(&encoder);
        
  if (encoder.clockwise && (red < 256-stepSize))
  {
    encoder.clockwise = 0;
    red = red + stepSize;
  }
  if(encoder.antiClockwise && (red > stepSize-1))
  {
    encoder.antiClockwise = 0;
    red = red - stepSize;
  }
  setRGB(red,green,blue);
 
  
}


///////////////////////////////////////////////////////////////////////////////
//                             RGB Encoder Control                           //
///////////////////////////////////////////////////////////////////////////////
//#include "uC101.h"
//#include "button.h"
//#include "pwmLED.h"
//#include "rotaryEncoder.h"
//
//#define F_CPU 16000000UL // 16 MHz
//
//// For LED state machine
//#define ENC_RED 0b001
//#define ENC_GREEN 0b010
//#define ENC_BLUE 0b100
//
//// Structs for each button
//extern struct buttonStruct encoderSW = {.port = &ENCODER_SW_PORT, .pin = ENCODER_SW};
//extern struct encoderStruct encoder = {.port1 = &ENCODER_B_PORT, .pin1 = ENCODER_B, .port2 = &ENCODER_A_PORT, .pin2 = ENCODER_A};
//
//// ISR to poll buttons
//volatile uint8_t sample = 4;  // For clock division
//ISR(TIMER2_OVF_vect)
//{
//  // Nasty clock division to decrease sample rate
//  if (!sample)
//  {
//    pollButton(&encoderSW);
//    sample = 4;
//  }
//  sample--;
//
//}
//
//// ISR to poll encoder
//ISR (TIMER1_COMPB_vect)
//{
//  pollEncoder(&encoder); 
//}
//
//// To control RGB colour
//uint8_t red = 0;
//uint8_t green = 0;
//uint8_t blue = 0;
//uint8_t stepSize = 4;  // Brightness per click, must be 2^n
//uint8_t state = ENC_RED; // Initial state
//
//void setup() 
//{
//  dirIn(ENCODER_SW_PORT,ENCODER_SW);
//  dirIn(ENCODER_A_PORT,ENCODER_A);
//  dirIn(ENCODER_B_PORT,ENCODER_B);
// 
//  buttonPollingInit();
//  encoderPollInit();
//  pwmSetup();
//}
//
//void loop() 
//{
//  // Update encoder before making decisions
//  calculateEncoder(&encoder);
//  encoderFSM(&encoder);
//  switch(state)
//  {
//    // Red LED under control
//    case ENC_RED:
//      if(encoderSW.rising) 
//      {
//        encoderSW.rising = 0;
//        state = ENC_GREEN;
//      }
//      
//      if (encoder.clockwise && (red < 256-stepSize))
//      {
//        encoder.clockwise = 0;
//        red = red + stepSize;
//      }
//      if(encoder.antiClockwise && (red > stepSize-1))
//      {
//        encoder.antiClockwise = 0;
//        red = red - stepSize;
//      }
//      setRGB(red,green,blue);
//      break;
//
//    // Green LED under control
//    case ENC_GREEN:
//      if(encoderSW.rising)
//      {
//        encoderSW.rising = 0;
//        state = ENC_BLUE;
//      }
//      
//      if (encoder.clockwise && (green < 256-stepSize))
//      {
//        encoder.clockwise = 0;
//        green = green + stepSize;
//      }
//      if(encoder.antiClockwise && (green > stepSize-1))
//      {
//        encoder.antiClockwise = 0;
//        green = green - stepSize;
//      }
//      setRGB(red,green,blue);
//      break;
//
//    // Blue LED under control
//    case ENC_BLUE:
//      if(encoderSW.rising)
//      {
//        encoderSW.rising = 0;
//        state = ENC_RED;
//      }
//      
//      if (encoder.clockwise && (blue < 256-stepSize))
//      {
//        encoder.clockwise = 0;
//        blue = blue + stepSize;
//      }
//      if(encoder.antiClockwise && (blue > stepSize-1))
//      {
//        encoder.antiClockwise = 0;
//        blue = blue - stepSize;
//      }
//      setRGB(red,green,blue);
//      break;
//
//      default:
//        state = ENC_RED; 
//        break;
//
//  } 
//  
//}

