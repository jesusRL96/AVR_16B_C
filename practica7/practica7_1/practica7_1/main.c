/*
 * practica7_1.c
 *
 * Created: 06/11/2019 07:01:47 p.m.
 * Author : Jesus
 */ 

#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

int contador;

ISR(INT0_vect,ISR_NAKED) {
	//_delay_ms(25);
	//while(PORTD2);
	//_delay_ms(25);
	switch(contador) {
		case 1:
			if(OCR0 < 245) OCR0+= 10;
			else OCR0 = 255;			
			break;
		case 2:
			if(OCR1A < 245) OCR1A += 10;
			else OCR1A = 255;
			break;
		default:
			if(OCR2 < 245) OCR2+= 10;
			else OCR2 = 255;
	}
	reti();
}

ISR(INT1_vect,ISR_NAKED) {
	//_delay_ms(25);
	//while(PORTD3);
	//_delay_ms(25);
	switch (contador)
	{
		case 1:
			if(OCR0 > 10) OCR0 -= 10;
			else OCR0 = 0;			
			break;
		case 2:
			if(OCR1A > 10) OCR1A -= 10;
			else OCR1A = 0;
			break;
		default:
			if(OCR2 > 0) OCR2-= 10;
			else OCR2 = 0;
	}
	//_delay_ms(1000);
	reti();
}


int main(void)
{
	/* Replace with your application code */
	cli();
	DDRB |= (1<<DDB3);
	DDRD |= (1<<DDD5) | (1<<DDD7) | (0<<DDD2) | (0<<DDD3);
	DDRA = 0x00;
	
	// DDRD &= (0<<DDD2) & (0<<DDD3);
	// DDRB |= (0<<DDB2);
	
	TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<COM00);
	TCCR1A |= (0<<WGM11) | (1<<WGM10) | (1<<COM1A1) | (1<<COM1A0);
	TCCR1B |= (0<<WGM13) | (1<<WGM12);
	TCCR2 |= (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<COM20);
	
	TCCR0 |= (0<<CS02) |(1<<CS01) | (0<<CS00);		//8
	TCCR1B |= (0<<CS12) |(1<<CS11) | (0<<CS10);
	TCCR2 |= (0<<CS22) |(1<<CS21) | (0<<CS20);
	
	OCR0 = 0;
	OCR1A = 0;
	OCR2 = 0;
	//TIMSK = (1<<OCIE0) | (1<<OCIE1A) | (1<<OCIE2);
	GICR |= (1<<INT1) | (1<<INT0);
	MCUCR |= (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
	// MCUCSR |= (1 << ISC2);
	sei();
	
	while (1)
	{
		contador = PINA & 0x03;
	}
}
