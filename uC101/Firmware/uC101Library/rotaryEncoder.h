#ifndef __ROTARYENCODER_H__
#define __ROTARYENCODER_H__

// Struct definition
typedef struct encoderStruct{
	volatile uint8_t* port1;
	volatile uint8_t pin1;
	volatile uint8_t* port2;
	volatile uint8_t pin2;
	volatile uint8_t history1;
	volatile uint8_t history2;
	volatile uint8_t on1;
	volatile uint8_t on2;
	volatile uint8_t off1;
	volatile uint8_t off2;
	volatile uint8_t rising1;
	volatile uint8_t rising2;
	volatile uint8_t falling1;
	volatile uint8_t falling2;
	volatile uint8_t clockwise;
	volatile uint8_t antiClockwise;
}encoderStruct;


void encoderPollInit(void);
void pollEncoder(struct encoderStruct *encoder);
void calculateEncoder(struct encoderStruct *encoder);
void encoderFSM(struct encoderStruct *encoder);

#endif