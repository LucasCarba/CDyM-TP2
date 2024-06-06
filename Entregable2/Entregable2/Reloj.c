/*
 * Reloj.c
 *
 * Created: 11/5/2024 17:16:08
 *  Author: LENOVO
 */ 

#include "Reloj.h"
 static uint8_t mili;
 static uint8_t segundo;
 static uint8_t minuto;
	
//inicializacion 
void RELOJ_Init(){
	mili=0;
	segundo=0;
	minuto=0;
}
void RELOJ_Update(){
	mili++;
	if( mili==100){
		mili=0;
		segundo++;	
	}
	if(segundo==60){
		segundo=0;
		minuto++;
	}
}

void RELOJ_GetTiempo(uint8_t* tAct){ //Guarda en el puntero de parametro [MM:SS:MS]
	tAct[0] = (minuto/10) + '0';
	tAct[1] = (minuto%10) + '0';
	tAct[2] = ':';
	tAct[3] = (segundo/10) + '0';
	tAct[4] = (segundo%10) + '0';
	tAct[5] = ':';
	tAct[6] = (mili/100) + '0';
	tAct[7]=((mili-(mili/100)*100)/10 )+ '0';
	tAct[8] = (mili%10) + '0';
}
	
uint8_t getMili()
{
	return mili;
}	