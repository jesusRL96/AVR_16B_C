/*
 * Practica7.c
 *
 * Created: 08/10/2019 02:54:10 p. m.
 * Author : jesus
 */ 
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

int contador;

ISR (INT0_vect) {
	//_delay_ms(25);
	//while(PORTD2);
	//_delay_ms(25);
	switch(contador) {
		case 1:
			if(OCR0 < 250) OCR0+= 5;
			else OCR0 = 255;
			break;	
		case 2:
			if(OCR1A < 250) OCR1A+= 5;
			else OCR1A = 255;
			break;	
		case 3:
			if(OCR2 < 250) OCR2+= 5;
			else OCR2 = 255;
			break;
		//default:
			//OCR0 = 255;
			//OCR1A = 255;
			//OCR2 = 255;
	}
	//_delay_ms(1000);
}

ISR (INT1_vect) {
	//_delay_ms(25);
	//while(PORTD3);
	//_delay_ms(25);
	switch(contador) {
		case 1:
			if(OCR0 > 5) OCR0-= 5;
			else OCR0 = 0;
			break;
		case 2:
			if(OCR1A > 5) OCR1A-= 5;
			else OCR1A = 0;
			break;
		case 3:
			if(OCR2 > 5) OCR2-= 5;
			else OCR2 = 0;
			break;
		default:
			OCR0 = 0;
			OCR1A = 0;
			OCR2 = 0;
	}
	//_delay_ms(1000);
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
	
	TCCR0 |= (1<<WGM01) | (0<<WGM00) | (0<<COM01) | (1<<COM00);
	TCCR1A |= (0<<WGM11) | (0<<WGM10) | (0<<COM1A1) | (1<<COM1A0);
	TCCR1B |= (0<<WGM13) | (1<<WGM12);
	TCCR2 |= (1<<WGM21) | (0<<WGM20) | (0<<COM21) | (1<<COM20);
	
	TCCR0 |= (0<<CS02) |(1<<CS01) | (0<<CS00);
	TCCR1B |= (0<<CS12) |(1<<CS11) | (0<<CS10);
	TCCR2 |= (0<<CS22) |(1<<CS21) | (0<<CS20);
	
	OCR0 = 0;
	OCR1A = 0;
	OCR2 = 0;
	// TIMSK = (1<<OCIE0) | (1<<OCIE1A) | (1<<OCIE2);
	GICR = (1 << INT0) | (1 << INT1);
	MCUCR |= (1 << ISC01) | (0 << ISC00) | (1 << ISC11) | (0 << ISC10);
	// MCUCSR |= (1 << ISC2);
	sei();
	
	while (1)
	{
		contador = PINA & 0x03;		
	}
}

