/*
 * GccApplication1.c
 *
 * Created: 24/09/2019 02:54:52 p. m.
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

int cuenta = 0;
char conteo_c[5];

ISR(TIMER0_OVF_vect) {
	LIMPIA_LCD();
	REGRESO_CASA();
	ENVIA_CADENA("CONTEO TERMINADO ");
	ENVIA_CADENA(conteo_c);
	cuenta = 0;
	_delay_ms(2000);
}

int main(void)
{
	/* Replace with your application code */
	int pulsos = 0, i, conteo = 0;
	char pulsos_c[5];
	char dato;
	
	cli();
	TCCR0 |= (1 << CS02) | (1 << CS01) | (0 << CS00);
	//TIMSK |= (0 << TOIE0);
	DDRD = 0xFF;
	sei();
	LCD_INICIALIZA();
	COLUMNA_init();
	while (1)
	{
		i = 0;
		conteo = 0;
		dato = ' ';
		TIMSK &= (0 << TOIE0);
		LIMPIA_LCD();
		REGRESO_CASA();
		ENVIA_CADENA("NUMERO DE PULSOS: ");
		POS_LINEA2(0);
		_delay_ms(500);
		while (dato != '='){
			if (!(PINA == 0x0F)){
				dato = LEER_TECLADO();
				ENVIA_DATO(dato);
				if (dato != '=') pulsos_c[i] = dato;
				i++;
			}
		}
		pulsos = atoi(pulsos_c);
		TCNT0 = 255 - pulsos + 1;
		
		for (int e = 0; e <= 4; e++)
		{
			pulsos_c[e] = '0';			
		}			
		cuenta = 1;
		TIMSK |= (1 << TOIE0);
		
		while(cuenta == 1) {
			LIMPIA_LCD();
			ENVIA_CADENA("cuenta: ");
			conteo = 255 - TCNT0 + 1;
			itoa(conteo,conteo_c,10);
			ENVIA_CADENA(conteo_c);
			_delay_ms(500);
		}
		for(int e = 0; i == 3; i++) {
			pulsos_c[1] = ' ';
		}	
	}
}



// FUNCIONES
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
	
	COLUMNA_init();
	
	_delay_ms(20);
	while(!(PINA == 0x0F));
	_delay_ms(20);
	return caracter;
}

