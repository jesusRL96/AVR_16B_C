/*
 * proyecto3.c
 *
 * Created: 31/10/2019 04:31:43 p. m.
 * Author : jesus
 */ 

#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

#define corchea 125		// medio tiempo
#define negra 250		// tiempo
#define blanca 500		// dos tiempos
#define tiempo 20
// Funciones
void espera();

// Notas
void Do();
void Do_s();
void Re_0();
void Re();
void Re_s();
void Mi();
void Fa();
void Fa_s();
void Sol();
void Sol_s();
void La();
void La_s();
void Si();

int main(void)
{
	/* Replace with your application code */
	cli();
	DDRB |= (1<<DDB3);
	DDRD |= (1<<DDD5) | (1<<DDD7) | (0<<DDD2) | (0<<DDD3);
	DDRA = 0x00;
	
	TCCR0 |= (1<<WGM01) | (0<<WGM00) | (0<<COM01) | (1<<COM00);
		
	TCCR0 |= (0<<CS02) |(1<<CS01) | (1<<CS00);		// prescaler 64
	
	OCR0 = 0;

	// TIMSK = (1<<OCIE0) | (1<<OCIE1A) | (1<<OCIE2);
	// MCUCSR |= (1 << ISC2);
	sei();
	
	while (1)
	{
		Si();
		_delay_ms(blanca);
		espera();
		
		Do();
		_delay_ms(negra);
		espera();
		
		Re();
		_delay_ms(negra);
		espera();
		
		Re();
		_delay_ms(negra);
		espera();
		
		Do();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(negra);
		_delay_ms(corchea);
		espera();
		
		La();
		_delay_ms(corchea);
		espera();
		
		La();
		_delay_ms(blanca);
		espera();
		
		Si();
		_delay_ms(blanca);
		espera();
		
		Do();
		_delay_ms(negra);
		espera();
		
		Re();
		_delay_ms(negra);
		espera();
		
		Re();
		_delay_ms(negra);
		espera();
		
		Do();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		_delay_ms(corchea);
		espera();
		
		Sol();
		_delay_ms(corchea);
		espera();
		
		Sol();
		_delay_ms(blanca);
		espera();
		
		///// ** /////
		
		La();
		_delay_ms(blanca);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(corchea);
		espera();
		
		Do();
		_delay_ms(corchea);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(corchea);
		espera();
		
		Do();
		_delay_ms(corchea);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Re_0();
		_delay_ms(blanca);
		espera();
		
		Si();
		_delay_ms(blanca);
		espera();
		
		Do();
		_delay_ms(negra);
		espera();
		
		Re();
		_delay_ms(negra);
		espera();
		
		Re();
		_delay_ms(negra);
		espera();
		
		Do();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		Sol();
		_delay_ms(negra);
		espera();
		
		
		La();
		_delay_ms(negra);
		espera();
		
		Si();
		_delay_ms(negra);
		espera();
		
		La();
		_delay_ms(negra);
		_delay_ms(corchea);
		espera();
		
		Sol();
		_delay_ms(corchea);
		espera();
		
		Sol();
		_delay_ms(blanca);
		espera();
		
		TCCR0 &= (0<<WGM01) & (0<<WGM00);
		PORTB &= (0<<PORTB3);
		_delay_ms(3000);
		TCCR0 |= (1<<WGM01) | (0<<WGM00) | (0<<COM01) | (1<<COM00);
		TCCR0 |= (0<<CS02) |(1<<CS01) | (1<<CS00);		// prescaler 64
	}
}

// Funciones 
//void Do() {
	//OCR0 = 29;			// do
//}
void Do_s() {
	OCR0 = 27;			// do#
}
void Re_0() {
	OCR0 = 26;			// re
}
void Re_s() {
	OCR0 = 25;			// re#
}
void Mi() {
	OCR0 = 23;			// mi
}
void Fa() {
	OCR0 = 21;			// fa
}
void Fa_s() {
	OCR0 = 20;			// fa#
}
void Sol() {
	OCR0 = 19;			// sol
}
void Sol_s() {
	OCR0 = 18;			// sol#
}
void La() {
	OCR0 = 17;			// la
}
void La_s() {
	OCR0 = 16;			// la#
}
void Si() {
	OCR0 = 15;			// si
}
void Do() {
	OCR0 = 14;			// do#
}
void Re() {
	OCR0 = 12;			// re
}

void espera() {
	TCCR0 &= (0<<WGM01) & (0<<WGM00);
	PORTB &= (0<<PORTB3);
	_delay_ms(tiempo);
	TCCR0 |= (1<<WGM01) | (0<<WGM00) | (0<<COM01) | (1<<COM00);	
	TCCR0 |= (0<<CS02) |(1<<CS01) | (1<<CS00);		// prescaler 64
}




