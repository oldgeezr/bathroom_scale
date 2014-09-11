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

#include "adc.h"
#include "setup.h"
#include "uart.h"

// State
volatile int asleep = 0; // 1;

int main (void)
{
	interrupt_init();
	
	// temp for debugging
	DDRB |= (1 << PINB0);
	PORTB |= (1 << PINB0); 

	// Select ADC channel
	// uint8_t ch = 0b00000000;

	while(1)
	{
		if (asleep) 
		{
			PORTB |= (1 << PINB0);
			// Power down
			sleep_now();
			// Power up 
			// external_clock_init();
			// interrupt_init();
			// uart_init();
			// timer_init();
			// adc_init();
			// sei();
		} else {
			// Temp for debugging
			_delay_ms(1000);
			PORTB ^= (1 << PINB0);
			// Read from ADC
			// uint16_t result = adc_read(ch);
			
			// Send result
			// uart_send_byte((result >> 8));
			// uart_send_byte(result);
			// uart_send_byte('\n');
			
			external_clock_init();
			timer_init();
			
			sei();
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	// Power down
	asleep = 1;
	cli();
}

ISR(INT0_vect)
{
	// Power up
	asleep = 0;
	cli();
}
