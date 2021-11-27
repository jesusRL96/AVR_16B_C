/*
 * practica10_1.c
 *
 * Created: 07/11/2019 06:35:53 p. m.
 * Author : jesus
 */ 
/*
 * practica10.c
 *
 * Created: 22/10/2019 06:54:53 p.m.
 * Author : Jesus
 */ 

#define F_CPU 1000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/cpufunc.h>
#include "lcd.h"
#include <stdlib.h>

void COLUMNA_init(void);
void FILA_init(void);
unsigned char LEER_TECLADO(void);

int posicion = 1, angulo;
float valor;
float porcen;
char angulo_c[14];
void calcular(void);


int main(void)
{
	/* Replace with your application code */
	DDRC = 0xff;
	DDRD = 0x20;
	// PORTD = 255;
	TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (0<<COM01) | (1<<WGM11) | (0<<WGM10);
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (0<<CS12) | (0<<CS11) | (0<<CS10);
	TCNT1 = 0;
	ICR1 = 2499;	// 50Hz -> 20000us
	TIMSK = 0;
	
	LCD_INICIALIZA();
	COLUMNA_init();
	posicion = 1;
	calcular();
	TCCR1B |= (0<<CS12) | (1<<CS11) | (0<<CS10);
	
	char dato;
	int i;
	while (1)
	{
		i = 0;
		dato = ' ';
		posicion = 0;
		LIMPIA_LCD();
		REGRESO_CASA();
		ENVIA_CADENA("Angulo: ");
		while (dato != '='){
			if (!(PINA == 0x0F)){
				dato = LEER_TECLADO();
				ENVIA_DATO(dato);
				if (dato != '=') angulo_c[i] = dato;
				i++;
			}
			
		}
		
		posicion = atoi(angulo_c);
		if(posicion <= 180) {
			POS_LINEA2(0);
			ENVIA_CADENA(angulo_c);
		}
		else {
			POS_LINEA2(0);
			ENVIA_CADENA("Fuera de rango");
			posicion = 1;
		}
		calcular();
		for(int j = 0; j <= 14; j++) {
			angulo_c[j] = ' ';
		}
		_delay_ms(1000);
	}
}

// funciones
void calcular(void) {
	posicion = posicion;
	valor = 500 + (posicion * 11);
	valor = valor * 2499;
	valor = (int)(valor / 20000);	
	OCR1A = valor;	
}

// Teclado     
void COLUMNA_init(void){
	DDRA = 0xF0;
	PORTA = 0x0F;
	asm volatile("nop");
	asm volatile("nop");
}
void FILA_init(void){
	DDRA = 0x0F;
	PORTA = 0xF0;
	asm volatile("nop");
	asm volatile("nop");
	_delay_ms(1);
}
unsigned char LEER_TECLADO(void){
	char valor, caracter;
	
	COLUMNA_init();
	valor = 0;
	if (!(PINA & 0x01))	valor = 3;
	else if (!(PINA & 0x02)) valor = 2;
	else if (!(PINA & 0x04)) valor = 1;
	else if (!(PINA & 0x08)) valor = 0;
	
	FILA_init();
	if (!(PINA & 0x10))	valor += 0x0D;
	else if (!(PINA & 0x20)) valor += 0x09;
	else if (!(PINA & 0x40)) valor += 0x05;
	else if (!(PINA & 0x80)) valor += 0x01;
	
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
	while(!(PINA == 0x0F));
	_delay_ms(20);
	return caracter;
}

