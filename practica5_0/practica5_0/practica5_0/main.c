/*
 * practica5_0.c
 *
 * Created: 10/09/2019 04:59:29 p.m.
 * Author : Jesus
 */
//1 55
//10 100
//15 234
//
//300 200
//500 84 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

uint8_t EEMEM *direccion;
uint8_t dato;

int main(void)
{
    /* Replace with your application code */
	short int indice;
	
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0x00;
	PORTC = 0xFF;
	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFF;
	
    while (1) {
		indice = PINC & 0x03;
		switch(indice) {
			case 1:
			direccion = PINA;
			dato = eeprom_read_byte(direccion);
			_delay_ms(1000);
			PORTB = dato;
			break;
			
			case 2:
			direccion = PINA;
			dato = PIND;
			eeprom_write_byte(direccion,dato);
			_delay_ms(1000);
			PORTB = EEDR;
			_delay_ms(1000);
			PORTB = EEAR;
			_delay_ms(1000);
			PORTB = 0x00;
			_delay_ms(1000);
			break;								
		}		
    }
}

