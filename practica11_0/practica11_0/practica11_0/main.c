/*
 * practica11_0.c
 *
 * Created: 15/10/2019 04:52:07 p. m.
 * Author : jesus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

ISR(ADC_vect) {
	PORTB = ADCH;
	ADCSRA |= (1<<ADSC);
}


int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	DDRA = 0x00;
	cli();
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (0<<ADATE);
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADMUX |= (1<<REFS1) | (1<<REFS0) | (1<<ADLAR);
	sei();
	ADCSRA |= (1<<ADSC);
    while (1) 
    {
		_NOP();
		_NOP();
    }
}

