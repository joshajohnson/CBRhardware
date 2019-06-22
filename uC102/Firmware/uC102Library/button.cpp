#include "Arduino.h"
#include "uC101.h"
#include "button.h"
#include <avr/sfr_defs.h>

struct buttonStruct; 

void buttonPollingInit(void)
{
	// Timer 2 Setup
	// Might seem strange but allows timer 2 to PWM LEDs and leave Timer 1 free
	TCCR2A |= _BV(WGM21) | _BV(WGM20); 	// WGM 0b011 sets up fast PWM 
	TCCR2A |= _BV(COM2B1); 				// Noninverting mode
	TCCR2A |= _BV(COM2A0); 				// OC2A Disconnected (PB3 can be used normally)
	TCCR2B |= _BV(2);					// Prescaler 64 (CA22)
	TIMSK2 |= _BV(0);					// Sets TOIE - Overflow interrupt enbaled

	OCR2B = 255;						// Forces LED_RED off

	sei(); 								// Enable global interrupts 

}

void pollButton(struct buttonStruct *button)
{
	// Shift in a new value
	button->history = button->history << 1;
	button->history |= readPin(*button->port,button->pin);

	// Check for button conditions
	(button->history == 0b11111111) ? button->on = 1 : button->on = 0;
	(button->history == 0b00000000) ? button->off = 1 : button->off = 0;
	(button->history == 0b01111111) ? button->rising = 1 : button->rising = 0;
	(button->history == 0b10000000) ? button->falling = 1 : button->falling = 0;
}
