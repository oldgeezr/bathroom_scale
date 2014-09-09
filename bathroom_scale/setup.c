/*
 * setup.c
 *
 * Created: 09.09.2014 20:22:48
 *  Author: Christoffer
 */ 

#include "setup.h"

void external_clock_init()
{
	// Enable clock prescale
	CLKPR = 0x00 | ( 1 << CLKPCE ); // Very sensitive to writing
	// Prescale 4
	CLKPR = ( 1 << CLKPS1 ); // Very sensitive to writing
}

void interrupt_init()
{
	// Set pulldown resistor
	PORTD |= (1 << PIND2);
	// Interrupt on any egde INT0
	EICRA |= (1 << ISC00) | (1 << ISC01);
	// Enable INT0
	EIMSK |= (1 << INT0);
}

void timer_init()
{
	TCNT1 = 0x0000;
	// Set CTC mode
	TCCR1B = (1 << WGM12);
	// Set clock prescale to 1024
	TCCR1B = (1 << CS12) | (1 << CS10);
	// Overflow compare at 16/4 seconds
	OCR1A = 62500/4;
	// Enable timer compare interrupt
	TIMSK1 = 0x00 | (1 << OCIE1A);
}

void sleep_now()
{
	// Set sleep mode to POWER DOWN
	SMCR |= (1 << SM1);
	// Set sleep enable
	sleep_enable();
	// Enable interrupt
	sei();
	// Put the device to sleep
	sleep_mode();
	// Continue from this point and disable sleep mode
	sleep_disable();
}