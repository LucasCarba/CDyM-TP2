/*
 * mef.c
 *
 * Created: 6/5/2024 16:11:34
 *  Author: LENOVO
 */ 
#include "mef.h"

static uint8_t cantTecla=0;
static uint8_t num;
static uint8_t numRandom;
uint8_t key;
static uint8_t teclasPresionada[2];



void JUEGO_Init(){ //Inicializa en estado INICIO y el count de ticks en 0.
	estado = INICIO;
	State_call_count = 0;
}


uint8_t	DentroDelRango(){
	  //Convierto a numero 
	  num=0;
	  for (uint8_t i=0;i<2;i++)
	  {
		  num=num*10+(teclasPresionada[i] - '0');
	  }
	  //Chequeo que no se pase del rango permitido 
	  if(num<0 || num>99){
		    return 0; // fuera de rango
	  }
	  else {
	     return 1;
	  } 
	  
	  
}

uint8_t IntroducirNro(){
	// Hay nuevo dato en el buffer de teclado?
	if(KEYPAD_Scan(&key) == 0){
		return 0; // No Hay dato nuevo 
	}
	
	// Se ha apretado una tecla, se espera 10seg mas para ver si se ingresa otra tecla
	if(State_call_count> 300)
	{
		// timeout, no se completo el ingreso de la clave, reiniciar
		State_call_count= 0;
		cantTecla=0;
		return 0;
	}
	 //guardo tecla presionada
	 if ((key>='0')&&(key <='9'))// verifico que es un digito
	 {
	 teclasPresionada[cantTecla++] = key;
	 }
	// tengo las 2teclas?
	if(cantTecla==2) {
		cantTecla=0;
		return  DentroDelRango();//Verifico que sea un numero y que este dentro del rango
	} else
	return 0; //no tengo las cuatro teclas aún
}


void JUEGO_Update(void){//llamada cada 100 ms
	//Contar numero de interrupciones
	State_call_count++;
	switch(estado){
		case INICIO: 
		             State_call_count=0;
		             LCDGotoXY(0,0);
		             LCDstring("BIENVENIDO",10);
		             LCDGotoXY(0,1);
		             LCDstring("P/ JUGAR PULSE A",16);
					 if(KEYPAD_Scan(&key)!=0){//Si presiono alguna tecla avanza al siguiente estado
					      estado=INICIO_JUGANDO;
					 }
		       break;
		
		 case INICIO_JUGANDO:
		                   //Chequeamos tecla presionada   
							if(key=='A'){
				               srand(getMili());// Semilla para la generación de números aleatorios
				               numRandom = rand() % 100;  // Genera un número aleatorio entre 0 y 99
							   RELOJ_Init();
							   estado=JUGANDO;			            
							}
							else {//Ingresa tecla incorrecta
				               //LCDclr();
				               LCDGotoXY(0,0);
				               LCDstring("   Error  ",10);
							   _delay_ms(3000);
				               estado=INICIO;
			                } 
		                    break;
		
		 case JUGANDO: 
		                if(State_call_count==1){ //Muestra en el display "JUGANDO"
			               LCDGotoXY(0,0);
			               LCDstring("  JUGANDO ",10);
			               LCDGotoXY(0,1);
			               LCDstring("INGRESE NUM     ",16);
			               if(IntroducirNro()==1){
							  if ( num==numRandom){
								 estado = GANADOR;
							  } 
							  else if (num > numRandom){
									 LCDGotoXY(12,1);
									 LCDstring(teclasPresionada,2);
									 LCDGotoXY(14,1);
									 LCDsendChar('>');
									 _delay_ms(1000);
									 estado = JUGANDO;
								   }
								   else if ( num < numRandom){
									 LCDGotoXY(12,1);
									 LCDstring(teclasPresionada,2);
									 LCDGotoXY(14,1);
									 LCDsendChar('<');
									 _delay_ms(1000);
									 estado = JUGANDO;
								  }
							     
						     
					    }
						
						else if (key == 'D'){
					        //Vuelvo al inicio luego de presionar D en el teclado.
					             estado = INICIO;
				             }
						}
					
					
			
			            break;
		
		case GANADOR:
		            //LCDclr();
			        LCDGotoXY(0,0);
			        LCDstring("  GANADOR ",10);
			        uint8_t tAct[9];
					
					RELOJ_GetTiempo(tAct);
					LCDGotoXY(9,1);
					LCDstring("       ",6);
			        LCDGotoXY(0,1);
					LCDstring(tAct,9);
					
					
			        //Luego de 3 segundos volvemos al inicio.
			        _delay_ms(3000);
			        estado = INICIO;
			        break;
		}
	}


