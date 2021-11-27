/*
 * practica11.c
 *
 * Created: 15/10/2019 05:20:49 p. m.
 * Author : jesus
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <stdlib.h>
#include "lcd.h"

int adc_v;
char adc_cadena[8];

ISR(ADC_vect) {
	adc_v = ADCH;
	//adc_v = (adc_v * 63) / 255;
	LIMPIA_LCD();
	REGRESO_CASA();
	itoa(adc_v,adc_cadena,10);
	ENVIA_CADENA(adc_cadena);
	
	adc_v = (ADC>>6);
	POS_LINEA2(0);
	itoa(adc_v,adc_cadena,10);
	ENVIA_CADENA(adc_cadena);
	ADCSRA |= (1<<ADSC);
	_delay_ms(500);
}


int main(void)
{
	/* Replace with your application code */
	DDRC = 0xFF;
	DDRA = 0x00;
	cli();
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (0<<ADATE);
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADMUX |= (1<<REFS1) | (0<<REFS0) | (1<<ADLAR);
	sei();
	ADCSRA |= (1<<ADSC);
	LCD_INICIALIZA();
	while (1)
	{
		_NOP();
		_NOP();
	}
}

