/*
 * timer.c
 *
 * Created: 19/05/2024 13:24:20
 *  Author: luisa
 */ 
#include "timer.h"
void SetupTimer0(uint16_t Prescaler0, uint8_t Desvordamiento0 ){
	switch (Prescaler0)
	{
		case 0:
		TCCR0B |= (1<<CS00);
		break;
		case 8:
		TCCR0B |= (1<<CS01);
		break;
		case 64:
		TCCR0B |= (1<<CS00)|(1<<CS01);
		break;
		case 256:
		TCCR0B |= (1<<CS02);
		break;
		case 1024:
		TCCR0B |= (1<<CS00)|(1<<CS02);
		break;
	}
	
	TCNT0 = Desvordamiento0;
	
	TIMSK0 |= (1<<TOIE0);
}

void SetupTimer1(uint16_t Prescaler1, uint16_t Desvordamiento1){
	switch (Prescaler1)
	{
		case 0:
		TCCR1B |= (1<<CS10);
		break;
		case 8:
		TCCR1B |= (1<<CS11);
		break;
		case 64:
		TCCR1B |= (1<<CS10)|(1<<CS11);
		break;
		case 256:
		TCCR1B |= (1<<CS12);
		break;
		case 1024:
		TCCR1B |= (1<<CS10)|(1<<CS12);
		break;
	}
	
	TCNT0 = Desvordamiento1;
	
	TIMSK1 |= (1<<TOIE1);
}

void SetupTimer2(uint16_t Prescaler2, uint8_t Desvordamiento2){
	switch (Prescaler2)
	{
		case 0:
		TCCR2B |= (1<<CS20);
		break;
		case 8:
		TCCR2B |= (1<<CS21);
		break;
		case 64:
		TCCR2B |= (1<<CS20)|(1<<CS21);
		break;
		case 256:
		TCCR2B |= (1<<CS22);
		break;
		case 1024:
		TCCR2B |= (1<<CS20)|(1<<CS22);
		break;
	}
	
	TCNT2 = Desvordamiento2;
	
	TIMSK2 |= (1<<TOIE2);
	
	
}