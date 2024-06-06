/*
 * Teclado4x4.h
 *
 * Created: 6/5/2024 11:43:54
 *  Author: LENOVO
 */ 


#ifndef TECLADO4X4_H_
#define TECLADO4X4_H_

//#include "main.h"
#include <avr/io.h>

//Inicializacion del teclado
void KEYPAD_Init();

//Para ver si se presiono alguna tecla y devuelvo 1 si si o si no cero
uint8_t KEYPAD_Scan(uint8_t *key);



#endif /* TECLADO4X4_H_ */