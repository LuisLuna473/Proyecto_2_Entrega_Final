/*
 * timer.h
 *
 * Created: 19/05/2024 13:24:09
 *  Author: luisa
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU 16000000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#define Positivo 1
#define Invertido 0
#define Externo 1
#define Interno 0
#define Fast 1
#define Phase 0
#define Todo 1
#define A 0
#define B 1
#define C 2
#define D 3

void SetupTimer0(uint16_t Prescaler0, uint8_t Desvordamiento0 );
void SetupTimer1(uint16_t Prescaler1, uint16_t Desvordamiento1);
void SetupTimer2(uint16_t Prescaler2, uint8_t Desvordamiento2);



#endif /* TIMER_H_ */