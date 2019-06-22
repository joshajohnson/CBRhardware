//////////////////////////////////////////////////////////////
//                      Basic RGB                           //
//////////////////////////////////////////////////////////////

#include "uC101.h"
#include "pwmLED.h"
#include <util/delay.h>

void setup() 
{
  pwmSetup();
}

void loop() 
{
  // Cycle through a bunch of RGB values
  setRGB(255,0,0);
  _delay_ms(500);
  setRGB(0,255,0);
  _delay_ms(500);
  setRGB(0,0,255);
  _delay_ms(500);
  setRGB(128,0,128);
  _delay_ms(500);
  setRGB(0,64,180);
  _delay_ms(500);
  setRGB(90,50,200);
  _delay_ms(500);
}
