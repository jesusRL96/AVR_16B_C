/*
 * practica3.c
 *
 * Created: 27/08/2019 03:11:41 p. m.
 * Author : jesus
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#include <stdlib.h>

void COLUMNA_init(void);
void FILA_init(void);
unsigned char LEER_TECLADO(void);



int main(void)
{
	/* Replace with your application code */
	char caracter;
	char val1_c[7] = "", val2_c[7] = "", total_c[14] = "";
	int val1 = 0, val2 = 0, indice = 0;
	int total;
	int caracter_select = 0, operador = 0;
	COLUMNA_init();
	// LCD
	DDRB = 0xFF;
	LCD_INICIALIZA();
	LIMPIA_LCD();
	REGRESO_CASA();
	while (1)
	{
		if (!(PIND == 0x0F))
		{
			caracter = LEER_TECLADO();
			if (caracter == '=')
			{
				LIMPIA_LCD();
				REGRESO_CASA();
				val1 = atoi(val1_c);
				val2 = atoi(val2_c);
				
				if (operador == 1) total = val1 + val2;
				else if (operador == 2) total = val1 - val2;
				else if (operador == 3) total = val1 * val2;
				else total = val1 / val2;
				
				// enviar a lcd
				itoa(total,total_c,10);
				//POS_LINEA1(11);				
				//ENVIA_DATO(total % 10 + 48);
				//
				//total = total / 10;
				//POS_LINEA1(10);
				//ENVIA_DATO(total % 10 + 48);
				//
				//total = total / 10;
				//POS_LINEA1(9);
				//ENVIA_DATO(total % 10 + 48);
				//
				//total = total / 10;
				//POS_LINEA1(8);
				//ENVIA_DATO(total % 10 + 48);
				//
				//total = total / 10;
				//POS_LINEA1(7);
				//ENVIA_DATO(total % 10 + 48);
				//ENVIA_CADENA(val1_c);
				//ENVIA_CADENA(val2_c);
				ENVIA_CADENA(total_c);
				
				caracter_select = 0;
				// Limpiar valores
				total = 0;
				for (int i = 0; i <= 4; i++)
				{
					val1_c[i] = 0;
					val2_c[i] = 0;
					total_c[i] = 0;
					
				}
				indice = 0;
				_delay_ms(2000);
				LIMPIA_LCD();
				REGRESO_CASA();
			}
			else if(caracter == '+'){
				operador = 1;
				caracter_select = 1;
				indice = 0;
				LIMPIA_LCD();
				REGRESO_CASA();
				
			}
			else if(caracter == '-'){
				operador = 2;
				caracter_select = 1;
				indice = 0;
				LIMPIA_LCD();
				REGRESO_CASA();
			}
			else if(caracter == '*'){
				operador = 3;
				caracter_select = 1;
				indice = 0;
				LIMPIA_LCD();
				REGRESO_CASA();
			}
			else if(caracter == '/'){
				operador = 4;
				caracter_select = 1;
				indice = 0;
				LIMPIA_LCD();
				REGRESO_CASA();
			}
			
			// Numeros
			else{
				if (caracter_select == 0)
				{
					//strcat(val1_c,caracter);
					//val1_c['\0'] = caracter;
					val1_c[indice] = caracter;
					indice += 1;
				}
				else
				{
					//val2_c['\0'] = caracter;	
					val2_c[indice] = caracter;	
					indice += 1;
				}
				
			}
			if(caracter != '=')	ENVIA_DATO(caracter);
			
			COLUMNA_init();
			_delay_ms(20);
			while(!(PIND == 0x0F));
			_delay_ms(20);
			while((PIND == 0x0F));
			_delay_ms(20);
			
		}
		
	}
}

// Funciones

void ESCRIBIR_dato(unsigned char valor){
	PORTB = valor;
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
	char valor, caracter;
	
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
	
	// DATOS
	if (valor == 1) caracter = '/';
	else if (valor == 2) caracter = '=';
	else if (valor == 3) caracter = '0';
	else if (valor == 4) caracter = '*';
	
	else if (valor == 5) caracter = '*';
	else if (valor == 6) caracter = '9';
	else if (valor == 7) caracter = '8';
	else if (valor == 8) caracter = '7';
	
	else if (valor == 9) caracter = '-';
	else if (valor == 10) caracter = '6';
	else if (valor == 11) caracter = '5';
	else if (valor == 12) caracter = '4';
	
	else if (valor == 13) caracter = '+';
	else if (valor == 14) caracter = '3';
	else if (valor == 15) caracter = '2';
	else if (valor == 16) caracter = '1';
	
	else caracter = '0';
	
	_delay_ms(1);
	return caracter;
}

