/*
 * practica4_0.c
 *
 * Created: 03/09/2019 12:03:45 p. m.
 * Author : jesus
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int i, j = 1, a = 0x55, b = 0xAA, c = 0x00;

ISR (INT0_vect) {
	for (i = 0; i < 5; i++) {
		PORTB = a;
		_delay_ms(1000);
		PORTB = b;
		_delay_ms(1000);
		PORTB = c;
		_delay_ms(1000);		
		}
	
	}



int main(void)
{
    /* Replace with your application code */
	cli();
	DDRB = 0xFF;
	DDRD = 0x00;
	GICR = (1 << INT0);
	MCUCR = (1 << ISC01) | (1 << ISC00);
	sei(); 
    while (1) 
    {
		PORTB = j;
		_delay_ms(500);
		j = j << 2;
		if(j > 0x80) j = 1;
    }
}

