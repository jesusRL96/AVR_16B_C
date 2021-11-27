/*
 * proyecto4.c
 *
 * Created: 01/11/2019 10:22:48 p.m.
 * Author : Jesus
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"


float ADC_leer();


int main(void)
{
	/* Replace with your application code */
	DDRC = 0xFF;
	DDRA = 0x00;
	ADCSRA |= (1<<ADEN) | (0<<ADIE) | (0<<ADATE);
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADMUX |= (0<<REFS1) | (1<<REFS0) | (1<<ADLAR);
	ADCSRA |= (0<<ADSC);
	LCD_INICIALIZA();
	float voltaje_temp, voltaje;
	
	//int adc_v;
	char adc_cadena[14];
	LIMPIA_LCD();
	REGRESO_CASA();
	while (1)
	{
		voltaje_temp = 0;
		voltaje = 0;
		for(int i = 0; i <= 200; i++) {
			voltaje_temp = ADC_leer();
			if(voltaje_temp > voltaje) voltaje = voltaje_temp;
		}
		//voltaje = ADC_leer();
		LIMPIA_LCD();
		REGRESO_CASA();
		ENVIA_CADENA("voltaje");
		voltaje *= (129.5);
		voltaje /= 3.05;
		voltaje += 2.4;
		if(voltaje < 5) voltaje = 0;
		dtostrf(voltaje, 6, 1, adc_cadena);
		POS_LINEA2(0);
		ENVIA_CADENA(adc_cadena);
		_delay_ms(500);
	}
}

float ADC_leer() {
	float adc_0;
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA|=(1<<ADIF);
	adc_0 = (ADC>>6);
	adc_0 =(adc_0 * 5) /  1024;
	return adc_0;
}