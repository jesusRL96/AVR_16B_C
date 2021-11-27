/*
 * practica1_0.c
 *
 * Created: 14/08/2019 10:37:52 p. m.
 * Author : jesus
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int a = 0b10101010;
int b = 0b01010101;
int c = 0;
int frida = 0;

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRA = 0x00;
    while (1) 
    {
		PORTD = a;
		frida = PINA;
		PORTB = frida;
		
		_delay_ms(250);
		PORTD = b;
		frida = PINA;
		PORTB = frida;
		
		_delay_ms(250);
		PORTD = c;
		frida = PINA;
		PORTB = frida;	
		_delay_ms(250);	
    }
	
	return 0;
}

