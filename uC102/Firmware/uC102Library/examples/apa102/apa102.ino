//////////////////////////////////////////////
//              APA102 SPI                  //
//////////////////////////////////////////////
#include "uC101.h"
#include "apa102.h"

#define NUM_LEDS 4

struct BGR led[NUM_LEDS];

void setup ()
{
  spiInit();
  dirIn(BUTTON_1_PORT,BUTTON_1);
  dirIn(BUTTON_2_PORT,BUTTON_2);
}

void loop()
{
  if (readPin(BUTTON_1_PORT,BUTTON_1))
  {
    led[0].red = 255; 
    led[0].green = 0;
    led[0].blue = 0;

    led[1].red = 0; 
    led[1].green = 255;
    led[1].blue = 0;

    led[2].red = 0; 
    led[2].green = 0;
    led[2].blue = 255;

    led[3].red = 255; 
    led[3].green = 255;
    led[3].blue = 255;

    setLED(led,NUM_LEDS,15);
    _delay_ms(100);
  }

  if (readPin(BUTTON_2_PORT,BUTTON_2))
  {
    led[3].red = 255; 
    led[3].green = 0;
    led[3].blue = 0;

    led[2].red = 0; 
    led[2].green = 255;
    led[2].blue = 0;

    led[1].red = 0; 
    led[1].green = 0;
    led[1].blue = 255;

    led[0].red = 255; 
    led[0].green = 255;
    led[0].blue = 255;

    setLED(led,NUM_LEDS,15);
    _delay_ms(100);
  }

}

