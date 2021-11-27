/*
 * practica9_0.c
 *
 * Created: 22/10/2019 04:12:47 p.m.
 * Author : Jesus
 */ 

#define F_CPU 1000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/cpufunc.h>

int i = 250;

ISR(INT0_vect,ISR_NAKED) {
	i += 10;
	OCR0 = i;
	reti();
}
ISR(INT1_vect,ISR_NAKED) {
	i -= 10;
	OCR0 = i;
	reti();
}
ISR(TIMER0_COMP_vect, ISR_NAKED) {
	PORTB = PINB;
	reti();
}


int main(void)
{
	/* Replace with your application code */
	cli();
	DDRB = 0xff;
	DDRD = 0x00;
	PORTD = 255;
	TCCR0 |= (1<<WGM01) | (0<<WGM00) | (0<<COM01) |(1<<COM00) | (0<<CS02) | (1<<CS00);
	OCR0 = i;
	TIMSK |= (1<<OCIE0);
	
	GICR |= (1<<INT1) | (1<<INT0);
	MCUCR |= (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
	sei();
	while (1)
	{
		_NOP();
		_NOP();
	}
}

