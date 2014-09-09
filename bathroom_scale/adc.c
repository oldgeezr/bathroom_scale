/*
 * adc.c
 *
 * Created: 09.09.2014 20:19:44
 *  Author: Christoffer
 */ 

#include "adc.h"

void adc_init(void)
{
	// AREF = AVcc
	ADMUX |= (1<<REFS0);
	// ADC Enable and prescaler of 64
	// 4000000/64 = 62500
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
	// Select ADC channel
	ADMUX |= (ADMUX & 0xF8)|ch;
	// start single convertion
	ADCSRA |= (1<<ADSC);
	// wait for conversion to complete
	while(ADCSRA & (1<<ADSC));
	// Return value from ADC
	return (ADC);
}