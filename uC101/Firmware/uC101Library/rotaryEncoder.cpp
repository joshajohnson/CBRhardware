#include "Arduino.h"
#include "UC101.h"
#include "rotaryEncoder.h"
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#define CTC_MATCH_OVERFLOW_ENCODER 8

// For  state machine
#define IDLE 	0b00000000
#define CW1 	0b00000001 
#define CW2 	0b00000010
#define CW3 	0b00000100 
#define CW4 	0b00001000  
#define CCW1 	0b00010000 
#define CCW2 	0b00100000
#define CCW3 	0b01000000 
#define CCW4 	0b10000000

struct encoderStruct;

// Init encoder polling ISR
void encoderPollInit(void)
{
	TCCR1B = _BV(WGM12); 				// CTC mode 
	TCCR1B |= _BV(CS11);				// Prescaler / 8		

	// Set CTC value
	OCR1BH = (CTC_MATCH_OVERFLOW_ENCODER >> 8);
    OCR1BL = CTC_MATCH_OVERFLOW_ENCODER;
 
    // Enable the CTC
    TIMSK1 |= _BV(OCIE1B);

    // Enable interrupts
    sei();
}

void pollEncoder(struct encoderStruct *encoder)
{
	// Shift in a new value
	encoder->history1 = encoder->history1 << 1;
	encoder->history1 |= readPin(*encoder->port1,encoder->pin1);
	
	encoder->history2 = encoder->history2 << 1;
	encoder->history2 |= readPin(*encoder->port2,encoder->pin2);
}

void calculateEncoder(struct encoderStruct *encoder)
{
	// Check for conditions
	(encoder->history1 == 0b11111111) ? encoder->on1 = 1 : encoder->on1 = 0;
	(encoder->history1 == 0b00000000) ? encoder->off1 = 1 : encoder->off1 = 0;
	(encoder->history1 == 0b01111111) ? encoder->rising1 = 1 : encoder->rising1 = 0;
	(encoder->history1 == 0b10000000) ? encoder->falling1 = 1 : encoder->falling1 = 0;
	
	(encoder->history2 == 0b11111111) ? encoder->on2 = 1 : encoder->on2 = 0;
	(encoder->history2 == 0b00000000) ? encoder->off2 = 1 : encoder->off2 = 0;
	(encoder->history2 == 0b01111111) ? encoder->rising2 = 1 : encoder->rising2 = 0;
	(encoder->history2 == 0b10000000) ? encoder->falling2 = 1 : encoder->falling2 = 0;

	// Check for rotation
	(encoder->on2 && encoder->rising1) ? encoder->clockwise = 1 : encoder->clockwise = 0;
	(encoder->on1 && encoder->rising2) ? encoder->antiClockwise = 1 : encoder->antiClockwise = 0;
	encoder->rising1 = 0;
	encoder->rising2 = 0;
} 

// Controls clockwise / antiClockwise rotation
void encoderFSM(struct encoderStruct *encoder)
{
	encoder->clockwise = 0;
	encoder->antiClockwise = 0;

	static uint8_t state;

	switch (state)
	{

		case IDLE:
			if (encoder->on2)
				state = CW1;
			else if (encoder->on1)
				state = CCW1;
			else 
				state = IDLE;
			break;

		// Rotating Clockwise
		case CW1:
			if (encoder->on1)
				state = CW2;
			else if (encoder->off2)
				state = IDLE;
			else 
				state = CW1;
			break;	

		case CW2:
			if (encoder->off2)
				state = CW3;
			else if (encoder->off1)
				state = CW1;
			else 
				state = CW2;
			break;	
		
		case CW3:
			if (encoder->off1)
				state = CW4;
			else if (encoder->on2)
				state = CW2;
			else 
				state = CW3;
			break;		

		case CW4:
			encoder->clockwise = 1;
			state = IDLE;
			break;

		// Rotating anti clockwise
		case CCW1:
			if (encoder->on2)
				state = CCW2;
			else if (encoder->off1)
				state = IDLE;
			else 
				state = CCW1;
			break;	

		case CCW2:
			if (encoder->off1)
				state = CCW3;
			else if (encoder->off2)
				state = CCW1;
			else 
				state = CCW2;
			break;	
		
		case CCW3:
			if (encoder->off2)
				state = CCW4;
			else if (encoder->on1)
				state = CCW2;
			else 
				state = CCW3;
			break;		

		case CCW4:
			encoder->antiClockwise = 1;
			state = IDLE;
			break;

		default:
			state = IDLE;
			break;

	}
}