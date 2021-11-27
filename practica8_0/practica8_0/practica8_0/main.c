/*
 * practica8_0.c
 *
 * Created: 08/10/2019 05:21:46 p. m.
 * Author : jesus
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <stdlib.h>
// Contadores de desvorde
volatile uint16_t T1Ovs1, T1Ovs2;
// Estampas de tiempo
volatile uint16_t Capt1, Capt2, Capt3;
// Contador de paso actual
volatile uint8_t Paso;
// Configurar timer 1
void InitTimer1(void) {
	// Establece valor inicial de timer1
	TCNT1 = 0;
	// Captura en flanco positivo
	TCCR1B |= (1 << ICES1);
	// Habilita la interrupcion del timer por captura de evento y por desvorde
	TIMSK |= (1 << TICIE1) | (1 << TOIE1);	
}
void StartTimer1(void) {
	// Arranca timer 1 sin prescalador
	TCCR1B |= (1 << CS10);
	// Habilita bandera global de interrupciones
	sei();
}
// Funcion de interrupcion por captura
ISR(TIMER1_CAPT_vect) {
	if(Paso == 1) {
		// Guarda contador registro de captura en flanco positivo
		Capt1 = ICR1;
		// Cambia para captura en flanco negativo
		TCCR1B &= ~(1 << ICES1);
		// Borrar desbordes
		T1Ovs2 = 0; 
	}
	if(Paso == 2) {
		Capt2 = ICR1;
		// Cambia captura en flanco positivo
		TCCR1B |= (1 << ICES1);
		// Guarda primer contador por desvorde
		T1Ovs1 = T1Ovs2;
	}
	if(Paso == 3) {
		Capt3 = ICR1;
		// Detiene interrupcion por captura y overflow
		TIMSK &= ~((1 << TICIE1) | (1 << TOIE1));
	}
	// Incrementa el paso
	Paso++;
}

// Rutina de interrupcion por desborde
ISR(TIMER1_OVF_vect) {
	// Incrementa contador de desbordes
	T1Ovs2++;
}



int main(void)
{
    /* Replace with your application code */
	// Variable de ciclo activo
	volatile uint8_t DutyCycle;
	char DutyCycle_c[6];
	DDRC = 0xFF;
	DDRD = 0x00;
	InitTimer1();
	StartTimer1();	
	LCD_INICIALIZA();
    while (1) 
    {
		// Calcula duty cycle
		if(Paso == 4) {
			TIMSK &= (0 << TICIE1) & (0 << TOIE1);
			LIMPIA_LCD();
			REGRESO_CASA(); 
			DutyCycle = (uint8_t)((((uint32_t)(Capt2 - Capt1) + ((uint32_t)T1Ovs1 * 0x10000L)) * 100L) / ((uint32_t)(Capt3 - Capt1) + ((uint32_t)T1Ovs2 * 0x10000L)));
			// Envia ciclo a LCD o la UART
			itoa(DutyCycle,DutyCycle_c,10);
			ENVIA_CADENA(DutyCycle_c);
				
			_delay_ms(500);
			// Inicia Pasos
			Paso = 1;
			// Limpia contadores de desborde
			T1Ovs1 = 0;
			T1Ovs2 = 0;
			// Limia banderas de captura y desborde para eliminar peticiones de interrupcion
			TIFR = (1 << ICF1) | (1 << TOV1);
			// Habilita interrupciones por captura y desborde
			TIMSK |= (1 << TICIE1) | (1 << TOIE1); 		
		}
    }
}

