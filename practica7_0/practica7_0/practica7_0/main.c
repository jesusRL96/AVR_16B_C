/*
 * practica7_0.c
 *
 * Created: 07/10/2019 03:17:07 p.m.
 * Author : Jesus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

ISR(TIMER0_COMP_vect) {
	// PORTB = PINB;
}

int main(void)
{
    /* Replace with your application code */
	cli();
	DDRB |= (1<<DDB3);
	TCCR0 = (1<<WGM01) | (0<<WGM00) | (0<<COM01) | (1<<COM00);
	TCCR0 |= (1<<CS02) |(0<<CS01) | (1<<CS00);
	OCR0 = 255;
	TIMSK = (1<<OCIE0);
    while (1) 
    {
    }
}

