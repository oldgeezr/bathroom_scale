/*
 * setup.h
 *
 * Created: 09.09.2014 20:23:57
 *  Author: Christoffer
 */ 

#ifndef SETUP_H_
#define SETUP_H_

#include <avr/sleep.h>
#include <avr/interrupt.h>

void external_clock_init();
void interrupt_init();
void timer_init();
void sleep_now();

#endif