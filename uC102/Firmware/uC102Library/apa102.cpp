#include "Arduino.h"
#include <util/delay.h>
#include "uC101.h"
#include "apa102.h"

void spiInit(void)
{
  dirOut(SPI_MOSI_PORT,SPI_MOSI);
  dirOut(SPI_SCK_PORT,SPI_SCK);
  dirOut(SPI_nSS_PORT,SPI_nSS);
  
  clearBit(SPI_MOSI_PORT,SPI_MOSI);
  clearBit(SPI_SCK_PORT,SPI_SCK);  
  setBit(SPI_nSS_PORT,SPI_nSS);
}

void spiWrite(uint8_t var)
{
  // Begin SPI Transfer
  for(uint8_t i = 8; i > 0; i--)
  {
    (var & 0x80) ? setBit(SPI_MOSI_PORT,SPI_MOSI) : clearBit(SPI_MOSI_PORT,SPI_MOSI); 
    _delay_us(1);
    setBit(SPI_SCK_PORT,SPI_SCK);
    _delay_us(2);
    clearBit(SPI_SCK_PORT,SPI_SCK);

    var <<= 1;
    _delay_us(1);
  }
  // Pull MOSI low now transfer is done
  clearBit(SPI_MOSI_PORT,SPI_MOSI);
}

void setLED(struct BGR *ledArray, uint8_t numLeds, uint8_t brightness)
{
  // Struct to array conversion 
  uint8_t *ledValues=(uint8_t*)ledArray;

  // Pull chip select low - NOT NEEDED
  clearBit(SPI_nSS_PORT,SPI_nSS);
  
  // Init with 32 zeros
  spiWrite(0x00);
  spiWrite(0x00);
  spiWrite(0x00);
  spiWrite(0x00);

  // Send data
  for(uint8_t i = 0; i < (numLeds * 3); i += 3)
  {
    spiWrite(0xe0 + brightness);
    spiWrite(ledValues[i+0]);
    spiWrite(ledValues[i+1]);
    spiWrite(ledValues[i+2]);
  }

  // End with 32 ones
  spiWrite(0xff);
  spiWrite(0xff);
  spiWrite(0xff);
  spiWrite(0xff);

  // Pull chip select back to high - NOT NEEDED
  setBit(SPI_nSS_PORT,SPI_nSS);
   
}
