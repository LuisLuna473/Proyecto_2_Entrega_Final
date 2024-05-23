/*
 * ADC.h
 *
 * Created: 19/05/2024 13:22:36
 *  Author: luisa
 */ 


#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
#define PC7 7

void SetupADC(uint8_t PinADC);



#endif /* ADC_H_ */