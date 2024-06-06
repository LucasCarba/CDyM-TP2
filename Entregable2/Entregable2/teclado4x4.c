/*
 * teclado4x4.c
 *
 * Created: 6/5/2024 11:45:48
 *  Author: LENOVO
 */
 
#include "Teclado4x4.h"

static const uint8_t teclado[4][4]= {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'0','*','#','D'}
};

static const uint8_t filas[4]={PINB4,PINB3,PINB0,PIND7};
static const uint8_t columnas[4]={PIND3,PIND5,PIND4,PIND2};

//Configuro las entradas y salidas de las filas y columnas
void KEYPAD_Init(){
	//filas como entradas
	DDRB &=  ~((1<< PORTB4)|(1<<PORTB3)|(1<<PORTB0));
	DDRD &=  ~((1<<PORTD7)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD2)|(1<<PORTD5));
	//seteo de las resistencias internas
	PORTB |= (1<<PORTB4)|(1<<PORTB3)|(1<<PORTB0);
	PORTD |= (1<<PORTD7);
	
	//COLUMNAS COMO SALIDAS
	//DDRD |=  (1<<PORTD3)|(1<<PORTD4)|(1<<(1<<PORTD2) |PORTD5);
	
	PORTD |=(1<<PORTD2)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD5); // pongo en uno las salidas
}

//Con ayuda de los profes de la practica decidimos volver a setear las entradas y las salidas 
//debido a que sin esto , no funcionaba correctamente

uint8_t KEYPAD_Scan(uint8_t *pkey){
	//escanear columnas
	for (uint8_t c=0;c<4;c++){
		DDRB &=  ~((1<< PORTB4)|(1<<PORTB3)|(1<<PORTB0));
		DDRD &=  ~((1<<PORTD7)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD2)|(1<<PORTD5));  
		DDRD|= (1<<columnas[c]); // pongo como salidas
		PORTD &=~(1<<columnas[c]);// escribo un cero
		//escanear filas
		for (uint8_t f=0;f<3;f++){
			if (!(PINB & (1<<filas[f]))){
				*pkey= teclado[f][c];// calculo el valor de la tecla
				return 1; // encontre la tecla
			}
		}
		if (!(PIND & (1<<PIND7))){
			*pkey= teclado[3][c];// calculo el valor de la tecla
			return 1; // encontre la tecla
		}
		
		// Vuelve a la configuracion inicial
		DDRD &= ~(1 << columnas[c]);
		PORTD |= (1 << columnas[c]);
		
		
	}
	return 0;// no encontre
}
