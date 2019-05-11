#include <Wire.h>
#include "Adafruit_MCP23017.h"

// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Output #0 is on pin 21 so connect an LED or whatever from that to ground

Adafruit_MCP23017 mcp;
// For right LEDs
int8_t dir = 0;
uint8_t pos = 0;

// For left LEDs
int8_t state_1 = 0;
int8_t dir_1 = 0;
uint8_t pos_1 = 0;

void setup() {  
  mcp.begin();      // use default address 0

  // Config all pins as outputs and turn them off
  for (uint8_t i = 0; i <= 15; i++)
  {
    mcp.pinMode(i,OUTPUT);
    mcp.digitalWrite(i,LOW);
  } 
}

void loop() 
{
  // Up Down on right hand LEDs
  mcp.digitalWrite(pos,HIGH);
  delay(100);
  mcp.digitalWrite(pos,LOW);

  if (pos == 7)
  {
    dir = 0;
  }
  else if (pos == 0)
  {
    dir = 1;
  }
  dir ? pos++ : pos--;
  
  // Left LEDs
  mcp.digitalWrite(pos_1+7,state_1);
  
  if (pos_1 == 9)
  {
    dir_1 = 0;
    state_1 ^= 1;
  }
  else if (pos_1 == 0)
  {
    dir_1 = 1;
    state_1 ^= 1;
  }
  dir_1 ? pos_1++ : pos_1--;
}
