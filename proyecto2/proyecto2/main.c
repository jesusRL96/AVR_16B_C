/*
* proyecto2.c
*
* Created: 24/09/2019 05:53:16 p. m.
* Author : jesus
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

void COLUMNA_init(void);
void FILA_init(void);
unsigned char LEER_TECLADO(void);

int conteo, val;

ISR(TIMER1_OVF_vect) {
	LIMPIA_LCD();
	REGRESO_CASA();
	val = 0;
	reti();
}

int main(void)
{
	/* Replace with your application code */
	int i, clave_real = 123, clave;
	char clave_c[5];
	char dato = ' ';
	cli();
	TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
	TIMSK &= (0 << TOIE1);
	DDRC = 0xFF;
	DDRA = 0xFF;
	sei();
	LCD_INICIALIZA();
	COLUMNA_init();
	conteo = 0;
	while (1)
	{
		TIMSK &= (0 << TOIE1);
		dato = ' ';
		i = 0;
		PORTA = 0;
		TIMSK &= (0 << TOIE1);
		LIMPIA_LCD();
		REGRESO_CASA();
		ENVIA_CADENA("clave: ");
		// POS_LINEA2(0);
		while (dato != '='){
			if (!(PIND == 0x0F)){
				dato = LEER_TECLADO();
				ENVIA_DATO(dato);
				if (dato != '=') clave_c[i] = dato;
				i++;
			}
		}
		clave = atoi(clave_c);
		if(clave == clave_real) {
			LIMPIA_LCD();
			REGRESO_CASA();
			ENVIA_CADENA("clave correcta");
			PORTA = 1;
			_delay_ms(2000);
			PORTA = 0;
			conteo = 0;
		}
		else {
			conteo += 1;
		}
		
		if(conteo == 3) {
			LIMPIA_LCD();
			REGRESO_CASA();
			ENVIA_CADENA("Espere");			
			TCNT1 = 0;
			TIMSK |= (1 << TOIE1);
			val = 1;
			while(val == 1);
			TIMSK &= (0 << TOIE1);
			LIMPIA_LCD();
			REGRESO_CASA();
			ENVIA_CADENA("Fin");
			conteo = 0;
			}
		for (int e = 0; e <= 4; e++){
			clave_c[e] = ' ';
		}
	}
}



// FUNCIONES


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
	if (valor == 1) caracter = '1';
	else if (valor == 2) caracter = '2';
	else if (valor == 3) caracter = '3';
	else if (valor == 4) caracter = 'A';
	
	else if (valor == 5) caracter = '4';
	else if (valor == 6) caracter = '5';
	else if (valor == 7) caracter = '6';
	else if (valor == 8) caracter = 'B';
	
	else if (valor == 9) caracter = '7';
	else if (valor == 10) caracter = '8';
	else if (valor == 11) caracter = '9';
	else if (valor == 12) caracter = 'C';
	
	else if (valor == 13) caracter = '*';
	else if (valor == 14) caracter = '0';
	else if (valor == 15) caracter = '=';
	else if (valor == 16) caracter = 'D';
	
	else caracter = '0';

	COLUMNA_init();
	_delay_ms(20);
	while(!(PIND == 0x0F));
	_delay_ms(20);
	return caracter;
}