/*
 * practica1.c
 *
 * Created: 14/08/2019 09:57:44 p. m.
 * Author : jesus
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// Configuracion Inicial
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	// Variables
	int registro1;
	
    while (1) 
    {		
		
		for (int j = 0; j <= 7; j++)
		{
			if (j <= 3) registro1 = 0b00000001;
			else registro1 = 0b1000000;
						
			for (int i = 0; i <= 7; i++)
			{
				// copia = registro1;
				if (j == 0 || j == 7) PORTA = registro1;
				else if (j == 1 || j == 6) PORTB = registro1;
				else if (j == 2 || j == 5) PORTC = registro1;
				else  PORTD = registro1;				
				
				_delay_ms(70);				
				if (j <= 3) registro1 = registro1 << 1;
				else registro1 = registro1 >> 1;
								
			}
			
			PORTA = 0x00;
			PORTB = 0x00;
			PORTC = 0x00;
			PORTD = 0x00;
			
		}
    }
}

