/*
 * practica12_0.c
 *
 * Created: 15/10/2019 05:08:58 p. m.
 * Author : jesus
 */ 

#define bit_is_clear(sfr,bit) \
		(!(_SFR_BYTE(sfr) & _BV(bit)))
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(ANA_COMP_vect) {
	if(bit_is_clear(ACSR,ACO)) PORTD = 0xFF;
	else PORTD = 0x00;
}

int main(void)
{
    /* Replace with your application code */
	cli();
	DDRB = 0x00;
	DDRD = 0xFF;
	ACSR |= (1<<ACIE);
	sei();
    while (1) 
    {
    }
}

