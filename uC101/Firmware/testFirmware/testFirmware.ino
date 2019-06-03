/////////////////////////////////////////////////////////////////////////////
//                            uC101 Test Program                           //
/////////////////////////////////////////////////////////////////////////////
#include "uC101.h"
#include "button.h"
#include "pwmLED.h"
#include "rotaryEncoder.h"
#include "timer.h"
#include <avr/io.h>

// For LED state machine
#define ENC_RED 0b001
#define ENC_GREEN 0b010
#define ENC_BLUE 0b100

// Button and Encoder Debouncing
extern struct buttonStruct button1 = {.port = &BUTTON_1_PORT, .pin = BUTTON_1};
extern struct buttonStruct button2 = {.port = &BUTTON_2_PORT, .pin = BUTTON_2};
extern struct buttonStruct encoderSW = {.port = &ENCODER_SW_PORT, .pin = ENCODER_SW};
extern struct encoderStruct encoder = {.port1 = &ENCODER_B_PORT, .pin1 = ENCODER_B, .port2 = &ENCODER_A_PORT, .pin2 = ENCODER_A};

// Charlieplexing Variables
uint32_t previousTime = 0;
const uint16_t interval = 250;
uint8_t numLED = 0;
uint8_t enable = 1;

// ISR to poll buttons
volatile uint8_t sample = 4;  // For clock division
ISR(TIMER2_OVF_vect)
{ 
  // Nasty clock division to decrease sample rate
  if (!sample)
  {
    pollButton(&encoderSW);
    pollButton(&button1);
    pollButton(&button2);
    sample = 4;
  }
  sample--;
}

// ISR to poll encoder
ISR (TIMER1_COMPB_vect)
{
  pollEncoder(&encoder); 
  calculateEncoder(&encoder);
}

// To control RGB colour
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;
uint8_t stepSize = 4;  // Brightness per click, must be 2^n
uint8_t state = ENC_RED; // Initial state

void setup() 
{
  pinMode(A6,INPUT);
  dirIn(ENCODER_SW_PORT,ENCODER_SW);
  dirIn(ENCODER_A_PORT,ENCODER_A);
  dirIn(ENCODER_B_PORT,ENCODER_B);
  dirIn(BUTTON_1_PORT,BUTTON_1);
  dirIn(BUTTON_2_PORT,BUTTON_2);
  dirOut(CHARLIE_1_PORT,CHARLIE_1);
  dirOut(CHARLIE_2_PORT,CHARLIE_2);
  dirOut(CHARLIE_3_PORT,CHARLIE_3);
  dirOut(CHARLIE_4_PORT,CHARLIE_4);
  
  buttonPollingInit();
  encoderPollInit();
  pwmSetup();
  timerInit();

  // Charlieplexing Test
  while (!readPin(BUTTON_1_PORT,BUTTON_1))
  {
    uint32_t currentTime = timerMilliseconds();
    if (currentTime - previousTime >= interval)
    {
      previousTime = currentTime;
      (numLED < 9) ? numLED++ : numLED = 0;
    }
    for (uint8_t pos = 0; pos <= 9; pos++)
    {
      (pos <= numLED) ? enable = 1 : enable = 0;
      setLED(pos,enable);
      _delay_us(500);
    }
  }
}

void loop() 
{


  // Button Test
  if (button1.on)
  {
    setRGB(0,255,0);
  }

  if (button2.on)
  {
    setRGB(0,0,255);
  }

  if (encoderSW.on)
  {
    setRGB(analogRead(A6)/4,0,0);
  }

  if (encoderSW.off && button1.off && button2.off)
  {
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

}

uint8_t setLED(uint8_t led, uint8_t enable)
{
  if (led > 9)
  return -1;

  uint8_t pinHigh[9] = {CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_2,CHARLIE_3,CHARLIE_4,CHARLIE_2};
  uint8_t pinLow[9]  = {CHARLIE_4,CHARLIE_4,CHARLIE_2,CHARLIE_3,CHARLIE_2,CHARLIE_1,CHARLIE_1,CHARLIE_3,CHARLIE_3};

  PORTC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));  // Outputs low / pullups off
  DDRC &= ~(_BV(CHARLIE_1) | _BV(CHARLIE_2) | _BV(CHARLIE_3) | _BV(CHARLIE_4));   // Set all high Z

  if (led && enable)
  DDRC |= _BV(pinHigh[led-1]) | _BV(pinLow[led-1]);
  PORTC |= _BV(pinHigh[led-1]); // Pull to VCC  
  PORTC &= ~_BV(pinLow[led-1]); // Pull to GND  
}

