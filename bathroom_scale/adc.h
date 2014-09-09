/*
 * adc.h
 *
 * Created: 09.09.2014 20:23:49
 *  Author: Christoffer
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adc_init(void);
uint16_t adc_read(uint8_t ch);

#endif