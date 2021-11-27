/*
 * practica9.c
 *
 * Created: 31/10/2019 04:18:16 p. m.
 * Author : jesus
 */ 

#define F_CPU 1000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/cpufunc.h>
#include <stdio.h>
#include "lcd.h"

char dato[3];
ISR(INT0_vect,ISR_NAKED) {
	_delay_ms(25);
	if(OCR0 <= 245) OCR0 += 10;
	else 255;
	LIMPIA_LCD();
	REGRESO_CASA();
	ENVIA_CADENA("OCR0 = ");
	itoa(OCR0, dato, 10);
	ENVIA_CADENA(dato);
	reti();
}
ISR(INT1_vect,ISR_NAKED) {
	_delay_ms(25);
	if(OCR0 >= 10) OCR0 -= 10;
	else OCR0 = 0;
	LIMPIA_LCD();
	REGRESO_CASA();
	ENVIA_CADENA("OCR0 = ");
	itoa(OCR0, dato, 10);
	ENVIA_CADENA(dato);
	reti();
}

int main(void)
{
	/* Replace with your application code */
	cli();
	DDRB = 0xff;
	DDRD = 0x00;
	DDRC = 0xff;
	//PORTD = 255;
	TCCR0 |= (0<<WGM01) | (1<<WGM00) | (1<<COM01) |(0<<COM00) | (0<<CS02) | (0<<CS01) | (1<<CS00);
	OCR0 = 0;
	//TIMSK |= (1<<OCIE0);
	
	GICR |= (1<<INT1) | (1<<INT0);
	MCUCR |= (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
	sei();
	LCD_INICIALIZA();
	LIMPIA_LCD();
	REGRESO_CASA();
	ENVIA_CADENA("OCR0 = ");
	itoa(OCR0, dato, 10);
	ENVIA_CADENA(dato);
	while (1)
	{
		_NOP();
		_NOP();
	}
}



