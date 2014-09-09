/*
 * uart.c
 *
 * Created: 09.09.2014 20:19:54
 *  Author: Christoffer
 */ 

#include "uart.h"
#include <avr/io.h>

void uart_init(void)
{
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)(UBRR_VALUE);
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	// Enable transmission and reception
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}

void uart_send_byte(uint8_t u8Data)
{
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0)));
	// Transmit data
	UDR0 = u8Data;
}