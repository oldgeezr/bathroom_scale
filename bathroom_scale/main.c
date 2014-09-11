/*
 * main.c
 * 
 * Description:	Digital bathroom scale with UART communication
 *
 * Behavior:	Wake up on interrupt. 
 *		Start sending ADC input to RPi
 *		Power down after 30 sec
 *
 * Created: 09.09.2014 20:22:48
 *  Author: Christoffer
 */ 

#define F_CPU 4000000UL

#include "adc.h"
#include "setup.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>

// State
volatile int asleep = 1;
volatile int timer_factor = 0;

int main (void)
{
	// Interrupt setup for sleep mode
	interrupt_init();
	
	// temp for debugging
	DDRB |= (1 << PINB0);
	PORTB |= (1 << PINB0); 

	// Select ADC channel
	uint8_t ch = 0b00000000;
	
	while(1)
	{
		if (asleep) 
		{
			PORTB &= ~(1 << PINB0);
			// Disable interrupt
			cli();
			// Power down
			sleep_now();
			PORTB ^= (1 << PINB0);
			// Continue here at start up
			// Disable interrupt for setting registers
			cli();
			external_clock_init();
			interrupt_init();
			timer_init();
			uart_init();
			adc_init();
			sei();
		} else if (!asleep) {
			// Temp for debugging
			_delay_ms(100);
			// PORTB ^= (1 << PINB0);
			// Read from ADC
			uint16_t result = adc_read(ch);
			// Send result
			uart_send_byte((result >> 8));
			uart_send_byte(result);
			uart_send_byte('\n');
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (timer_factor)
	{
		// Power down
		timer_factor = 0;
		asleep = 1;
		cli();	
	} else {
		// Timer x2
		timer_factor++;
	}
}

ISR(INT0_vect)
{
	// Power up
	asleep = 0;
	cli();
}
