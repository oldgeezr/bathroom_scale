/*
 * main.c
 *
 * Created: 09.09.2014 20:22:48
 *  Author: Christoffer
 */ 

#include "adc.h"
#include "setup.h"
#include "uart.h"

// State
volatile int asleep = 1;

int main (void)
{
	interrupt_init();
	sei();
	
	// temp for debugging
	DDRB |= (1 << PINB0);
	PORTB |= (1 << PINB0); 

	// Select ADC channel
	uint8_t ch = 0b00000000;

	while(1)
	{
		if (asleep) 
		{
			PORTB |= (1 << PINB0);
			// Power down
			sleep_now();
			// Power up 
			external_clock_init();
			interrupt_init();
			uart_init();
			timer_init();
			adc_init();
			sei();
		} else {
			// Temp for debugging
			PORTB ^= (1 << PINB0);
			// Read from ADC
			uint16_t result = adc_read(ch);
			_delay_ms(100);
			// Send result
			uart_send_byte((result >> 8));
			uart_send_byte(result);
			uart_send_byte('\n');
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	// Power down
	asleep = 1;
}

ISR(INT0_vect)
{
	// Power up
	asleep = 0;
	cli();
}