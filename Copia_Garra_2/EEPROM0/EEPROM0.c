/*
 * EEPROM0.c
 *
 * Created: 19/05/2024 13:27:50
 *  Author: luisa
 */ 
#include "EEPROM0.h"
#define F_CPU 16000000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>


void writeEeprom (uint8_t address, uint8_t data){
	while (EECR & (1<<EEPE)); //esperar a una escritura previa
	switch(address){
		case ch1:
		EEAR = ch1;
		EEDR = data;
		break;
		
		case ch2:
		EEAR = ch2;
		EEDR = data;
		break;
		
		case ch3:
		EEAR = ch3;
		EEDR = data;
		break;
		
		case ch4:
		EEAR = ch4;
		EEDR = data;
		break;
	}
}

void readEeprom(uint8_t address){
	while (EECR & (1<<EEPE)); //esperar a una escritura previa
	//Ve al lugar de la dirección seleccionada
	EEAR = address;
	
	//Empieza la Eeprom a leer al escribir en EERE
	EECR |= (1<<EERE);
	
	//Devuelve la información guardada en el resgitro
	return EEDR;
	
}