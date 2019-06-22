#ifndef APA102_H_
#define APA102_H_

struct BGR
  {  uint8_t blue; 
     uint8_t green; 
     uint8_t red; 
  };

void spiInit(void);
void spiWrite(uint8_t var);
void setLED(struct BGR *ledArray, uint8_t numLeds, uint8_t brightness);

#endif
