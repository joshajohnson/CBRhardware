//////////////////////////////////////////////
//                    ADC                   //
//////////////////////////////////////////////
#include "uC101.h"
#include "uart.h"
#include "pwmLED.h"

void adcInit()
{
  ADMUX = (1<<REFS0);                                     // AREF = AVcc
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);    // ADC Enable and prescaler of 128
}

uint16_t adcRead(uint8_t channel)
{
  ADMUX = (ADMUX & 0xF8)|channel;   // Set channel we are reading from
  ADCSRA |= (1<<ADSC);              // Start conversion (single conversion mode)
  while(ADCSRA & (1<<ADSC));        // Wait for conversion to complete
  return (ADC);                     // Return ADC value
}

uint8_t adcString[64];
uint8_t txString[64];

void setup ()
{
  adcInit();
  uartInit();
  pwmSetup();
  dirIn(BUTTON_1_PORT,BUTTON_1);
  dirIn(BUTTON_2_PORT,BUTTON_2);
}

void loop()
{
  setRGB(adcRead(6)/4,0,0); // Writing 10 bit (1024) adc value to 8 bit (256) pwm register
  _delay_ms(50);
  
  if (readPin(BUTTON_1_PORT,BUTTON_1))
  {
    uint16_t adcVal = adcRead(6);
    sprintf(adcString,"ADC Value: %d \r\n",adcVal);
    uartPutStr(adcString);
    _delay_ms(500);
  }

  if (readPin(BUTTON_2_PORT,BUTTON_2))
  {
    float voltage = (float) adcRead(6) * 5 / 1024;  // ADC -> voltage conversion 
    dtostrf(voltage,1,2,adcString);
    sprintf(txString,"ADC Voltage: %s \r\n",adcString);
    uartPutStr(txString);
    _delay_ms(500);
  }
}
