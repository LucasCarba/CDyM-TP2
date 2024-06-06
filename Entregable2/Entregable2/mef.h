/*
 * mef.h
 *
 * Created: 6/5/2024 16:10:25
 *  Author: LENOVO
 */ 


#ifndef MEF_H_
#define MEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#include "Reloj.h"
#include "Teclado4x4.h"
#include "lcd.h"
#include "timer.h"

typedef enum { INICIO,INICIO_JUGANDO,JUGANDO,GANADOR} MEF_STATE;
 MEF_STATE estado;

uint8_t State_call_count;

void JUEGO_Init();
void JUEGO_Update();
uint8_t ValidarTecla();
uint8_t IntroducirNro();


#endif /* MEF_H_ */