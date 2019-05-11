#ifndef __BUTTON_H__
#define __BUTTON_H__

// Struct definition
typedef struct buttonStruct{
	volatile uint8_t* port;
	volatile uint8_t pin;
	volatile uint8_t history;
	volatile uint8_t on;
	volatile uint8_t off;
	volatile uint8_t rising;
	volatile uint8_t falling;
}buttonStruct;

void buttonPollingInit(void);
void pollButton(struct buttonStruct *button);

#endif