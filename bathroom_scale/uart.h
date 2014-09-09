/*
 * uart.h
 *
 * Created: 09.09.2014 20:23:40
 *  Author: Christoffer
 */ 

#ifndef UART_H_
#define UART_H_

#define USART_BAUDRATE 9600
#define UBRR_VALUE 25

#include <stdint.h>

void uart_init(void);
void uart_send_byte(uint8_t u8Data);

#endif