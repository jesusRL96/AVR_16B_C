/*
 * practica3.c
 *
 * Created: 27/08/2019 03:11:41 p. m.
 * Author : jesus
 */ 

#define FCPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void COLUMNA_init(void);
void FILA_init(void);
unsigned char LEER_TECLADO(void);



int main(void)
{
	/* Replace with your application code */
	char caracter;
	caracter = 0;
	COLUMNA_init();
	// LCD
	DDRB = 0xFF;
	LCD_INICIALIZA();
	LIMPIA_LCD();
	REGRESO_CASA();
	while (1)
	{
		if (!(PIND == 0x0F))
		{
			caracter = LEER_TECLADO();
			LIMPIA_LCD();
			REGRESO_CASA();
			ENVIA_DATO(caracter);
			COLUMNA_init();
			_delay_ms(20);
			while(!(PIND == 0x0F));			
			_delay_ms(20);
			while((PIND == 0x0F));
			_delay_ms(20);
			
		}
	}
}

// Funciones


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
	if (valor == 1) caracter = 'D';
	else if (valor == 2) caracter = '#';
	else if (valor == 3) caracter = '0';
	else if (valor == 4) caracter = '*';
	
	else if (valor == 5) caracter = 'C';
	else if (valor == 6) caracter = '9';
	else if (valor == 7) caracter = '8';
	else if (valor == 8) caracter = '7';
	
	else if (valor == 9) caracter = 'B';
	else if (valor == 10) caracter = '6';
	else if (valor == 11) caracter = '5';
	else if (valor == 12) caracter = '4';
	
	else if (valor == 13) caracter = 'A';
	else if (valor == 14) caracter = '3';
	else if (valor == 15) caracter = '2';
	else if (valor == 16) caracter = '1';
	
	_delay_ms(1);
	return caracter;
}

