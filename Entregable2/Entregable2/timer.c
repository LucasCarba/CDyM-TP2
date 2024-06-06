/*
 * timer.c
 *
 * Created: 6/5/2024 16:11:16
 *  Author: LENOVO
 */ 

#include "timer.h"

static uint8_t contMEF=0;
void timer_init(){
	//Primero me aseguro que esten deshabilitadas las interrupciones
	TIMSK0 &=~((1<<OCIE0A));
	
	// Modo CTC
	TCCR0A|=(1<<WGM01); 
	
	//Configuramos TCCR0B con preescaler en 256
	//TCCR0B|=(1<<CS00);
	TCCR0B|=(1<<CS02);
	
	//Inicializo contador
	TCNT0=0;
	//Valor para la comparacion
	OCR0A=249;
	
	//Hablito interrupciones por compareA
	TIMSK0=(1<<OCIE0A);
	//Habilito interrupciones globales
	sei();
}
	
	ISR(TIMER0_COMPA_vect){
		if(++contMEF==10){
			contMEF=0;
		}
		RELOJ_Update();
	}
	