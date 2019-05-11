#include "Arduino.h"
#include "uC101.h"
#include "pwmLED.h"
#include <avr/sfr_defs.h>

void pwmSetup(void)
{
	// Timer 0 Setup
	TCCR0A |= _BV(WGM01) | _BV(WGM00); 	// WGM 0b011 sets up fast PWM
	TCCR0A |= _BV(COM0A1);				// Noninverting mode
	TCCR0A |= _BV(COM0B1); 				// Noninverting mode
	TCCR0B |= _BV(1) | _BV(0);			// Prescaler to 64 (CA01 & CS00)
	
	// Timer 2 Setup
	TCCR2A |= _BV(WGM21) | _BV(WGM20); 	// WGM 0b011 sets up fast PWM 
	TCCR2A |= _BV(COM2B1); 				// Noninverting mode
	TCCR2A |= _BV(COM2A0); 				// OC2A Disconnected (PB3 can be used normally)
	TCCR2B |= _BV(2);					// Prescaler 64 (CA22)

	setRGB(0,0,0); 	// Init all off

	// Turn LEDs off (common anode so 1 == off)
	ledOff(LED_RED);
	ledOff(LED_GREEN);
	ledOff(LED_BLUE);

	// Set pins as outputs
	dirOut(LED_RED_PORT,LED_RED);
	dirOut(LED_GREEN_PORT,LED_GREEN);
	dirOut(LED_BLUE_PORT,LED_BLUE);	
}

void setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
	// Set comparator values, inverted due to being common anode
	OCR0A = ~blue;									
	OCR0B = ~green;	
	OCR2B = ~red;	
}
