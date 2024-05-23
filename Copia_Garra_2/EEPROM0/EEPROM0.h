/*
 * EEPROM0.h
 *
 * Created: 19/05/2024 13:27:40
 *  Author: luisa
 */ 


#ifndef EEPROM0_H_
#define EEPROM0_H_

#define F_CPU 16000000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

/*
	DEFINICIONES DE VARIABLES
*/
#define ch1 0
#define ch2 1
#define ch3 2
#define ch4 3


void writeEeprom(uint8_t address, uint8_t data);
void readEeprom(uint8_t address); 



#endif /* EEPROM0_H_ */