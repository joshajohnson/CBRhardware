#include "Arduino.h"
#include "uC101.h"
#include "timer.h"
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/atomic.h>

// Millisecond timer                   
#define CLK_PRESCALER 64
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / CLK_PRESCALER) 
volatile uint32_t timerMillis;

void timerInit(void)
{
	TCCR1B = _BV(WGM12); 				// CTC mode 
	TCCR1B |= _BV(CS11) | _BV(0); 		// Prescaler / 64		

	// Set CTC value
	OCR1AH = (CTC_MATCH_OVERFLOW >> 8);
    OCR1AL = CTC_MATCH_OVERFLOW;
 
    // Enable the CTC
    TIMSK1 |= _BV(OCIE1A);

    // Enable interrupts
    sei();
}

// ISR is called every 1ms, so increase count
ISR (TIMER1_COMPA_vect)
{
    timerMillis++;
}

uint32_t timerMilliseconds(void)
{
	uint32_t milliReturn;

	ATOMIC_BLOCK(ATOMIC_FORCEON) // Prevents interrupts disrupting
	{
		milliReturn = timerMillis;
	}

	return milliReturn;
}
