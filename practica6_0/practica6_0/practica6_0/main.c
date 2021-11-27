/*
 * practica6_0.c
 *
 * Created: 24/09/2019 02:43:09 p. m.
 * Author : jesus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

short int i = 0;
ISR(TIMER0_OVF_vect) {
	PORTB = i;
	i++;
}

int main(void)
{
    /* Replace with your application code */
	cli();
	TCCR0 |= (1 << CS02) | (0 << CS01) | (1 << CS00);
	TIMSK |= (1 << TOIE0);
	DDRB = 0xFF;
	sei(); 
    while (1) 
    {
		
    }
}

