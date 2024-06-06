/*
 * Reloj.h
 *
 * Created: 11/5/2024 17:15:46
 *  Author: LENOVO
 */ 


#ifndef RELOJ_H_
#define RELOJ_H_

#include <avr/io.h>
void RELOJ_Init();
void RELOJ_Update();
void RELOJ_GetTiempo(uint8_t* );
#include <stdint.h>
uint8_t getMili();



#endif /* RELOJ_H_ */