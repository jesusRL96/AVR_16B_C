/*
 * practica4.c
 *
 * Created: 03/09/2019 03:02:39 p. m.
 * Author : jesus
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "lcd.h"

int conteo = 0;

ISR (INT0_vect) {
	//_delay_ms(25);
	if(conteo < 255) conteo += 1;
	else conteo = 255;
	while(!PORTD2);
	_delay_ms(100);	
}

ISR (INT1_vect) {
	//_delay_ms(25);
	if(conteo > 0) conteo -= 1;
	else conteo = 0;
	while(!PORTD3);
	_delay_ms(100);
}


int main(void)
{
	/* Replace with your application code */
	char conteo_t[3];
	cli();
	DDRB = 0xFF;
	DDRD = 0x00;	// D2 y D3
	GICR = (1 << INT0) | (1 << INT1);
	MCUCR |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10);
	sei();
	ENVIA_CADENA("Conteo: ");
	LCD_INICIALIZA();
	while (1){
		LIMPIA_LCD();
		REGRESO_CASA();
		ENVIA_CADENA("Conteo: ");
		itoa(conteo, conteo_t, 10);
		ENVIA_CADENA(conteo_t);
		_delay_ms(300);		
	}
}


