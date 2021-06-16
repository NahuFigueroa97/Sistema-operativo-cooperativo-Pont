/*
 * debouncing.c
 *
 *  Created on: 15 abr. 2021
 *      Author: nahuu
 */
#include "board.h"
#include "sapi.h"
#include "debouncing.h"

uint8_t estado[4]={no_apretado};
uint8_t evento[4]={boton_no_apretado};
uint8_t ev= none;
tick_t duracion,time_actual,time_pasado;

tick_t time_diff(){
	return duracion;
}

uint8_t debouncing(gpioMap_t boton) {

	switch (estado[boton-36]) {

	case no_apretado:


		evento[boton-36] =(gpioRead(boton) == 1) ? boton_no_apretado : boton_apretado;
		estado[boton-36] = (evento[boton-36] == boton_apretado) ? apretando : no_apretado;
        ev=none;

            break;

	case apretando:

		evento[boton-36] =(gpioRead(boton) == 1) ? boton_no_apretado : boton_apretado;
		estado[boton-36] = (evento[boton-36] == boton_apretado) ? apretado : no_apretado;
		time_pasado= tickRead();

		if(estado[boton-36] == apretado){
					    ev=abajo;
					}else{
						ev=none;
					}

		break;

	case apretado:

		evento[boton-36] = (gpioRead(boton) == 1) ? boton_no_apretado : boton_apretado;
		estado[boton-36] = (evento[boton-36] == boton_apretado) ? apretado : soltando;
		ev=none;

		break;

	case soltando:

			evento[boton-36] = (gpioRead(boton) == 1) ? boton_no_apretado : boton_apretado;
			estado[boton-36] = (evento[boton-36] == boton_apretado) ? apretando : no_apretado;
			time_actual= tickRead();

			if(estado[boton-36] == no_apretado){
				duracion= time_actual-time_pasado;
			    ev=arriba;
			}else{
				ev=none;
			}

			break;
	}
	return ev;
}
