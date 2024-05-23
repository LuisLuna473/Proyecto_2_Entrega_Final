/*
 * Copia_Garra_2.c
 *
 * Created: 18/05/2024 12:17:53
 * Author : luisa
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <stddef.h>
#include <avr/eeprom.h>   // Usar función para activar EEPROM
#include "ADC/ADC.h"
#include "TIMERS/timer.h"
#include "PWM/PWM1.h"
#include "UART/UART0.h"
#include "EEPROM0/EEPROM0.h"



uint8_t ValorADC1 = 0;
uint8_t ValorADC2 = 0;
uint8_t ValorADC3 = 0;
uint8_t ValorADC4 = 0;

volatile uint8_t contador = 0;
volatile uint8_t mem = 0; 
 
volatile uint8_t btta = 0;

volatile uint8_t Turno = 0;
volatile uint8_t bufferTX; 
volatile uint8_t ValorADC_S =0; 
long PWM; 

void setup(void);
void initPcint1(void);
void resultado(void); 
void Cambio(void); 

//Función de mapeo 
long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



int unir(int n1, int n2, int n3){
	ValorADC_S = n1*100+n2*10+n3; 
	return ValorADC_S; 
}

int main(void)
{
	//PORTD |= (1<<PIND6);
	setup(); 
	initPcint1();
				 

    while (1)
    {
		switch(contador)
		{
			case 0: //Modo Manual
				_delay_ms(200);
				PORTD &= ~(1<<PORTD4);
				PORTD &= ~(1<<PORTD5);
				
				/*//Brazo izquierdo 
				PWM = map(ValorADC1, 0, 255, 5, 23); 
				ciclo_traba1A(PWM/6);
				
				//Brazo derecho
				PWM = map(ValorADC2, 0, 255, 8, 23); 
				ciclo_traba1B(PWM/6); 
				
				//Base 
				PWM = map(ValorADC3, 0, 255, 5, 37); 
				ciclo_traba2A(PWM/6);
				
				//Garra
				PWM = map(ValorADC4, 0, 255, 5, 23);
				ciclo_traba2B(PWM/6); */
				
				OCR1A =  ValorADC1/6;
				OCR1B = ValorADC2/6;
				OCR2A = ValorADC3/6;
				OCR2B = ValorADC4/6;
				
				break;
			case 1: //Modo AdaFruit
				
				_delay_ms(200);
				PORTD |= (1<<PORTD4);
				PORTD &= ~(1<<PORTD5);
				void resultado(void);
				
				
				break;
			case 2: //Modo Escribir EEPROM
				_delay_ms(200);
				PORTD &= ~(1<<PORTD4);
				PORTD |= (1<<PORTD5);
				break;
			case 3: //Modo Leer EEPROM
				_delay_ms(200);
				PORTD |= (1<<PORTD4);
				PORTD |= (1<<PORTD5);
				break;
		}
		
    }
}

void setup(void){
	cli();
	SetupADC(PC2);
	SetupADC(PC3);
	SetupADC(PC4);
	SetupADC(PC6);
	SetupTimer0(1024,250);
	SetupPWM1(Fast8,Positivo,A,1024);   //Salida D9
	SetupPWM1(Fast8,Positivo,B,1024);   //Salida D10
	
	SetupPWM2(Fast8,Positivo,A,1024);   //Salida D11
	SetupPWM2(Fast8,Positivo,B,1024);   //Salida D3
	
	SetupUART0(M9600);      //Velocidad 9600 Fast 
	
	   
	DDRC &= ~(1<<DDC0);//Push buttons
	DDRC &= ~(1<<DDC1);
	DDRC &= ~(1<<DDC5);
	PORTC |= (1<<PORTC0)|(1<<PORTC1)|(1<<PORTC5);

	
	DDRD |= (1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); //LEDS
	PORTD &= ~(1<<PORTD4);
	PORTD &= ~(1<<PORTD5);
	PORTD &= ~(1<<PORTD6);
	PORTD &= ~(1<<PORTD7);
	
	DDRB |= (1<<DDB0);
	PORTB &= ~(1<<PORTB0);
	
	
	sei();
}

void initPcint1(void){
	                //PC5       //PC1        //PC0
	 PCMSK1 |= (1<<PCINT13)|(1<<PCINT9)|(1<<PCINT8);
	 PCICR |= (1<< PCIE1);
}

void resultado(void){
	switch(bufferTX){
		case 'a': //Serv1 Brazo Izquierdo 
			if(bufferTX = 'e'){
				OCR1A = 0; 
			}else if(bufferTX = 'f'){
				OCR1A = 10; 
			}else if(bufferTX = 'g'){
				OCR1A = 20; 
			}else if(bufferTX = 'h'){
				OCR1A = 30; 
			}else if(bufferTX = 'i'){
				OCR1A = 40; 
			}else if(bufferTX = 'j'){
				OCR1A = 50; 
			}else if(bufferTX = 'k'){
				OCR1A = 60; 
			}else if(bufferTX = 'l'){
				OCR1A = 70;
			}else if(bufferTX ='m'){
				OCR1A = 80; 
			}else if(bufferTX = 'n'){
				OCR1A = 90; 
			}else if(bufferTX = 'o'){
				OCR1A = 100; 
			}else if(bufferTX = 'p'){
				OCR1A = 110; 
			}else if(bufferTX = 'q'){
				OCR1A = 120; 
			}else if(bufferTX = 'r'){
				OCR1A = 130; 
			}else if(bufferTX = 's'){
				OCR1A = 150; 
			}else if(bufferTX = 't'){
				OCR1A = 170; 
			}else if(bufferTX = 'u'){
				OCR1A = 180; 
			}else if(bufferTX = 'v'){
				OCR1A = 190;
			}else if(bufferTX = 'w'){
				OCR1A = 200; 
			}else if(bufferTX = 'x'){
				OCR1A = 210; 
			}else if(bufferTX = 'y'){
				OCR1A = 220; 
			}else if(bufferTX = 'x'){
				OCR1A = 230; 
			}
		
		
		break;
		case 'b': //Serv2 Brazo derecho 
			if(bufferTX = 'e'){
				OCR1B = 0; 
			}else if(bufferTX = 'f'){
				OCR1B = 10; 
			}else if(bufferTX = 'g'){
				OCR1B = 20; 
			}else if(bufferTX = 'h'){
				OCR1B = 30; 
			}else if(bufferTX = 'i'){
				OCR1B = 40; 
			}else if(bufferTX = 'j'){
				OCR1B = 50; 
			}else if(bufferTX = 'k'){
				OCR1B = 60; 
			}else if(bufferTX = 'l'){
				OCR1B = 70;
			}else if(bufferTX ='m'){
				OCR1B = 80; 
			}else if(bufferTX = 'n'){
				OCR1B = 90; 
			}else if(bufferTX = 'o'){
				OCR1B = 100; 
			}else if(bufferTX = 'p'){
				OCR1B = 110; 
			}else if(bufferTX = 'q'){
				OCR1B = 120; 
			}else if(bufferTX = 'r'){
				OCR1B = 130; 
			}else if(bufferTX = 's'){
				OCR1B = 150; 
			}else if(bufferTX = 't'){
				OCR1B = 170; 
			}else if(bufferTX = 'u'){
				OCR1B = 180; 
			}else if(bufferTX = 'v'){
				OCR1B = 190;
			}else if(bufferTX = 'w'){
				OCR1B = 200; 
			}else if(bufferTX = 'x'){
				OCR1B = 210; 
			}else if(bufferTX = 'y'){
				OCR1B = 220; 
			}else if(bufferTX = 'x'){
				OCR1B = 230; 
			}
		//Valores del payload
		break;
		case 'c': //Serv3 Base
		//Valores del payload
			if(bufferTX = 'e'){
				OCR2A = 0;
				}else if(bufferTX = 'f'){
				OCR2A = 10;
				}else if(bufferTX = 'g'){
				OCR2A = 20;
				}else if(bufferTX = 'h'){
				OCR2A = 30;
				}else if(bufferTX = 'i'){
				OCR2A = 40;
				}else if(bufferTX = 'j'){
				OCR2A = 50;
				}else if(bufferTX = 'k'){
				OCR2A = 60;
				}else if(bufferTX = 'l'){
				OCR2A = 70;
				}else if(bufferTX ='m'){
				OCR2A = 80;
				}else if(bufferTX = 'n'){
				OCR2A = 90;
				}else if(bufferTX = 'o'){
				OCR2A = 100;
				}else if(bufferTX = 'p'){
				OCR2A = 110;
				}else if(bufferTX = 'q'){
				OCR2A = 120;
				}else if(bufferTX = 'r'){
				OCR2A = 130;
				}else if(bufferTX = 's'){
				OCR2A = 150;
				}else if(bufferTX = 't'){
				OCR2A = 170;
				}else if(bufferTX = 'u'){
				OCR2A = 180;
				}else if(bufferTX = 'v'){
				OCR2A = 190;
				}else if(bufferTX = 'w'){
				OCR2A = 200;
				}else if(bufferTX = 'x'){
				OCR2A = 210;
				}else if(bufferTX = 'y'){
				OCR2A = 220;
				}else if(bufferTX = 'x'){
				OCR2A = 230;
			}
		break;
		case 'd': //Serv4 Garra 
			if(bufferTX = 'e'){
				OCR2B = 0;
				}else if(bufferTX = 'f'){
				OCR2B = 10;
				}else if(bufferTX = 'g'){
				OCR2B = 20;
				}else if(bufferTX = 'h'){
				OCR2B = 30;
				}else if(bufferTX = 'i'){
				OCR2B = 40;
				}else if(bufferTX = 'j'){
				OCR2B = 50;
				}else if(bufferTX = 'k'){
				OCR2B = 60;
				}else if(bufferTX = 'l'){
				OCR2B = 70;
				}else if(bufferTX ='m'){
				OCR2B = 80;
				}else if(bufferTX = 'n'){
				OCR2B = 90;
				}else if(bufferTX = 'o'){
				OCR2B = 100;
				}else if(bufferTX = 'p'){
				OCR2B = 110;
				}else if(bufferTX = 'q'){
				OCR2B = 120;
				}else if(bufferTX = 'r'){
				OCR2B = 130;
				}else if(bufferTX = 's'){
				OCR2B = 150;
				}else if(bufferTX = 't'){
				OCR2B = 170;
				}else if(bufferTX = 'u'){
				OCR2B = 180;
				}else if(bufferTX = 'v'){
				OCR2B = 190;
				}else if(bufferTX = 'w'){
				OCR2B = 200;
				}else if(bufferTX = 'x'){
				OCR2B = 210;
				}else if(bufferTX = 'y'){
				OCR2B = 220;
				}else if(bufferTX = 'x'){
				OCR2B = 230;
			}
		//valores del payload
		break;	
	}
		 
}
void Cambio(void){
	switch (bufferTX){
		case '1':
			//aa
		break; 
	}
}


/*
	------------------------------------------------------
	INTERRUPCIONES
	------------------------------------------------------
*/
ISR(TIMER0_OVF_vect){
	switch (Turno)
	{
	case 0:
		Turno=1;
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0)); 
		ADMUX |= (1<< MUX1);                              //ADC2
		break;
	case 1:
		Turno=2;
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX1)|(1<<MUX0);                     //ADC3
		break;
	case 2:
		Turno=3;
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX|=(1<<MUX2);                                 //ADC4
		break;
	case 3: 
		Turno = 0;
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX2)|(1<<MUX1);                      //ADC6
		break; 
	}
	ADCSRA |= (1<<ADSC);
	//TCNT0 = 250;
	TCNT0 = 220;
	TIFR0 |= (1 << TOV0);
}

ISR(ADC_vect){
	switch (Turno)
	{
	case 0:
		ValorADC1 = ADCH;
		break;
	case 1:
		ValorADC2 = ADCH;
		break;
	case 2:
		ValorADC3 = ADCH;
		break;
	case 3:
		ValorADC4 = ADCH; 
		break;
	default:
		break;
	}
	ADCSRA |= (1<<ADIF);
}

ISR (PCINT1_vect){
	
	if ((PINC & (1<<PINC0)) == 0){
		//Función para cambiar el modo
		contador++;
		if (contador == 4){
			contador = 0; 
		}

	}
	if ((PINC & (1<<PINC1)) == 0){
		//Write EEPROM Función para leer valores ADC
		//eeprom_write_byte(uint8_t*address, uint8_t ValorADC1);
		//encender otro led para indicar que se guardo algo

		PORTD &= ~(1<<PORTD6);
		if(contador == 2){
			
			PORTD |= (1<<PORTD6);
			if(mem == 0){
				eeprom_write_byte((uint8_t*)0, OCR1A);
				eeprom_write_byte((uint8_t*)1, OCR1B);
				eeprom_write_byte((uint8_t*)2, OCR2A);
				eeprom_write_byte((uint8_t*)3, OCR2B);
			}
			if (mem == 1){
				eeprom_write_byte((uint8_t*)4, OCR1A);
				eeprom_write_byte((uint8_t*)5, OCR1B);
				eeprom_write_byte((uint8_t*)6, OCR2A);
				eeprom_write_byte((uint8_t*)7, OCR2B);
			}
			if(mem == 2){
				eeprom_write_byte((uint8_t*)8, OCR1A);
				eeprom_write_byte((uint8_t*)9, OCR1B);
				eeprom_write_byte((uint8_t*)10, OCR2A);
				eeprom_write_byte((uint8_t*)11, OCR2B);
			}
			if(mem == 3){
				eeprom_write_byte((uint8_t*)12, OCR1A);
				eeprom_write_byte((uint8_t*)13, OCR1B);
				eeprom_write_byte((uint8_t*)14, OCR2A);
				eeprom_write_byte((uint8_t*)15, OCR2B);
			}
		}else if(contador == 3){
			PORTD |= (1<<PORTD6);
			if(mem == 0){
				ValorADC1 = eeprom_read_byte((uint8_t*)0);
				OCR1A = ValorADC1; 
				ValorADC2 = eeprom_read_byte((uint8_t*)1); 
				OCR1B = ValorADC2; 
				ValorADC3 = eeprom_read_byte((uint8_t*)2);
				OCR2A = ValorADC3; 
				ValorADC4 = eeprom_read_byte((uint8_t*)3);
				OCR2B = ValorADC4; 
			}
			if(mem == 1){
				ValorADC1 = eeprom_read_byte((uint8_t*)4);
				OCR1A = ValorADC1;
				ValorADC2 = eeprom_read_byte((uint8_t*)5);
				OCR1B = ValorADC2;
				ValorADC3 = eeprom_read_byte((uint8_t*)6);
				OCR2A = ValorADC3;
				ValorADC4 = eeprom_read_byte((uint8_t*)7);
				OCR2B = ValorADC4;
			}
			if(mem == 2){
				ValorADC1 = eeprom_read_byte((uint8_t*)8);
				OCR1A = ValorADC1;
				ValorADC2 = eeprom_read_byte((uint8_t*)9);
				OCR1B = ValorADC2;
				ValorADC3 = eeprom_read_byte((uint8_t*)10);
				OCR2A = ValorADC3;
				ValorADC4 = eeprom_read_byte((uint8_t*)11);
				OCR2B = ValorADC4;
			}
			if(mem == 3){
				ValorADC1 = eeprom_read_byte((uint8_t*)12);
				OCR1A = ValorADC1;
				ValorADC2 = eeprom_read_byte((uint8_t*)13);
				OCR1B = ValorADC2;
				ValorADC3 = eeprom_read_byte((uint8_t*)14);
				OCR2A = ValorADC3;
				ValorADC4 = eeprom_read_byte((uint8_t*)15);
				OCR2B = ValorADC4;
			}
		}
	}
	if ((PINC & (1<<PINC5)) == 0){ 
		//Sumo una variable para cambiar la posición de las 4 posiciones guardadas
		mem++;
		
		if(mem == 4){
			mem = 0; 
		}
		if(mem == 0){
			//Encender Nada
			PORTB &= ~(1<<PORTB0);
			PORTD &= ~(1<<PORTD7);
		}
		if(mem == 1){
			//Encender LED1
			PORTD |= (1<<PORTD7);
			PORTB &= ~(1<<PORTB0);
		}
		if(mem == 2){
			//Encender LED2
			PORTD &= ~(1<<PORTD7);
			PORTB |= (1<<PORTB0);
			
		}
		if(mem == 3){
			//Encer Led1 y 2
			PORTD |= (1<<PORTD7);
			PORTB |= (1<<PORTB0);
		}
	}
}

ISR(USART_RX_vect){
	bufferTX = UDR0;
	while(!(UCSR0A & (1<<UDRE0)));
	//UDR0 = bufferTX;		
		
}


