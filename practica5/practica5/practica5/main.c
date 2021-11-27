/*
 * practica5.c
 *
 * Created: 10/09/2019 09:28:49 p.m.
 * Author : Jesus
 */ 

//1 55
//10 100
//15 234
//
//300 200
//500 84

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "lcd.h"
#include <stdlib.h>

void COLUMNA_init(void);
void FILA_init(void);
unsigned char LEER_TECLADO(void);

uint8_t direccion;
uint8_t dato;

int main(void)
{
	/* Replace with your application code */
	char indice;
	char direccion_t[5], dato_c[5];
	char caracter;
	int i;
	
	DDRC = 0x00;	// seleccion	
	COLUMNA_init();	// teclado	
	DDRB = 0xFF;	// lcd
	LCD_INICIALIZA();
	LIMPIA_LCD();
	REGRESO_CASA();
	
	while (1) {
		caracter = ' ';
		indice = ' ';
		LIMPIA_LCD();
		REGRESO_CASA();
		ENVIA_CADENA("1-leer");
		POS_LINEA2(0);
		ENVIA_CADENA("2-escribir");
		while (PIND == 0x0F);
		if (!(PIND == 0x0F)){
			indice = LEER_TECLADO();
		}
		ENVIA_DATO(indice);
		
		_delay_ms(1000);		
		// indice = PINC & 0x03;
		switch(indice) {
			case '1':		// LECTURA 
			i = 0;
			LIMPIA_LCD();
			REGRESO_CASA();
			ENVIA_CADENA("DIRECCION: ");
			while (caracter != '='){
				if (!(PIND == 0x0F)){
					caracter = LEER_TECLADO();
					if(caracter != '=') direccion_t[i] = caracter;
					i += 1;
					ENVIA_DATO(caracter);
					_delay_ms(20);
					while(!(PIND == 0x0F));
					_delay_ms(20);
				}
				
			}			
			direccion = atoi(direccion_t);
			dato = eeprom_read_byte(direccion);
			POS_LINEA2(0);
			ENVIA_CADENA("EL DATO ES:");
			itoa(dato,dato_c,10);
			ENVIA_CADENA(dato_c);
			_delay_ms(3000);		
			break;
			
			case '2':		// ESCRITURA
			i = 0;
			LIMPIA_LCD();
			REGRESO_CASA();
			ENVIA_CADENA("DIRECCION: ");
			while (caracter != '='){
				if (!(PIND == 0x0F)){
					caracter = LEER_TECLADO();
					if(caracter != '=') direccion_t[i] = caracter;
					i += 1;
					ENVIA_DATO(caracter);
					_delay_ms(20);
					while(!(PIND == 0x0F));
					_delay_ms(20);
				}
			}
			direccion = atoi(direccion_t);
			caracter = ' ';
			i = 0;
			POS_LINEA2(0);
			ENVIA_CADENA("DATO: ");
			while (caracter != '='){
				if (!(PIND == 0x0F)){
					caracter = LEER_TECLADO();
					if(caracter != '=') dato_c[i] = caracter;
					i += 1;
					ENVIA_DATO(caracter);
					_delay_ms(20);
					while(!(PIND == 0x0F));
					_delay_ms(20);
				}
			}
			dato = atoi(dato_c);
			_delay_ms(1000);
			
			
			LIMPIA_LCD();
			REGRESO_CASA();			
			eeprom_write_byte(direccion,dato);
			ENVIA_CADENA("DATO ESCRITO");
			POS_LINEA2(0);
			_delay_ms(1000);
			//PORTB = EEDR;
			//_delay_ms(1000);
			//PORTB = EEAR;
			//_delay_ms(1000);
			//PORTB = 0x00;
			//_delay_ms(1000);
			break;
			
			default:
			LIMPIA_LCD();
			REGRESO_CASA();
			ENVIA_CADENA("caracter no reconocido");
			_delay_ms(1000);
		}
	}
}


// FUNCIONES DE TECLADO MATRICIAL
void ESCRIBIR_dato(unsigned char valor){
	PORTB = valor;
}
void COLUMNA_init(void){
	DDRD = 0xF0;
	PORTD = 0x0F;
	asm volatile("nop");
	asm volatile("nop");
}
void FILA_init(void){
	DDRD = 0x0F;
	PORTD = 0xF0;
	asm volatile("nop");
	asm volatile("nop");
	_delay_ms(1);
}
unsigned char LEER_TECLADO(void){
	char valor, caracter;
	
	COLUMNA_init();
	valor = 0;
	if (!(PIND & 0x01))	valor = 3;
	else if (!(PIND & 0x02)) valor = 2;
	else if (!(PIND & 0x04)) valor = 1;
	else if (!(PIND & 0x08)) valor = 0;
	
	FILA_init();
	if (!(PIND & 0x10))	valor += 0x0D;
	else if (!(PIND & 0x20)) valor += 0x09;
	else if (!(PIND & 0x40)) valor += 0x05;
	else if (!(PIND & 0x80)) valor += 0x01;
	
	// DATOS
	if (valor == 1) caracter = '/';
	else if (valor == 2) caracter = '=';
	else if (valor == 3) caracter = '0';
	else if (valor == 4) caracter = '*';
	
	else if (valor == 5) caracter = '*';
	else if (valor == 6) caracter = '9';
	else if (valor == 7) caracter = '8';
	else if (valor == 8) caracter = '7';
	
	else if (valor == 9) caracter = '-';
	else if (valor == 10) caracter = '6';
	else if (valor == 11) caracter = '5';
	else if (valor == 12) caracter = '4';
	
	else if (valor == 13) caracter = '+';
	else if (valor == 14) caracter = '3';
	else if (valor == 15) caracter = '2';
	else if (valor == 16) caracter = '1';
	
	else caracter = '0';
	
	_delay_ms(1);
	COLUMNA_init();
	
	return caracter;
}

