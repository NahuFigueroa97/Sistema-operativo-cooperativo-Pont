/*
 * debouncing.h
 *
 *  Created on: 15 abr. 2021
 *      Author: nahuu
 */

#ifndef LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_DEBOUNCING_H_
#define LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_DEBOUNCING_H_

typedef void (*funcion_t)(void*);


typedef enum {
	no_apretado, apretando, apretado, soltando
} estados_t;

typedef enum {
	boton_no_apretado,boton_apretado,
} eventos_t;

typedef enum {
	none,arriba,abajo
} boton_t;


uint8_t debouncing(gpioMap_t boton);
tick_t time_diff();

#endif /* LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_DEBOUNCING_H_ */
