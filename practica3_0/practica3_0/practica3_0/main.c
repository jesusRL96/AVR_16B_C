/*
 * practica3_0.c
 *
 * Created: 27/08/2019 02:23:40 p. m.
 * Author : jesus
 */ 
#define FCPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void LED_init(void);
void ENCIENDE_LED(unsigned char valor);
void COLUMNA_init(void);
void FILA_init(void);
unsigned char LEER_TECLADO(void);

int main(void)
{
    /* Replace with your application code */
	unsigned char led;
	LED_init();
	led = 0;
	COLUMNA_init();
    while (1) 
    {
		if (!(PIND == 0x0F))
		{
			led = LEER_TECLADO();			
		}
		ENCIENDE_LED(led);		
    }
}

// Funciones
void LED_init(void){
	DDRB = 0xFF;
	PORTB = 0xFF;
}
void ENCIENDE_LED(unsigned char valor){
	PORTB = ~valor;	
}
void COLUMNA_init(void){
	DDRD = 0xF0;
	PORTD = 0x0F;
	asm volatile("nop");
	asm volatile("nop");	
}
void FILA_init(void){
	DDRD = 0x0F;
	PORTD = 0xF0;
	asm volatile("nop");
	asm volatile("nop");
	_delay_ms(1);
}
unsigned char LEER_TECLADO(void){
	unsigned char valor;
	
	COLUMNA_init();
	valor = 0;
	if (!(PIND & 0x01))	valor = 3;
	else if (!(PIND & 0x02)) valor = 2;
	else if (!(PIND & 0x04)) valor = 1;
	else if (!(PIND & 0x08)) valor = 0;
	
	FILA_init();
	if (!(PIND & 0x10))	valor += 0x0D;
	else if (!(PIND & 0x20)) valor += 0x09;
	else if (!(PIND & 0x40)) valor += 0x05;
	else if (!(PIND & 0x80)) valor += 0x01;
	
	_delay_ms(1);	
	return valor;
}