/*============================================================================
 * Autor: Nahuel Figueroa
 * Licencia:
 * Fecha: 24/01/2021
 *===========================================================================*/

// Inlcusiones
#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "seos_pont_2014_isr.h"       // <= own header
#include "seos_pont_2014_scheduler.h" // <= dispatcher and task management header
#include "debouncing.h"

#define time_debouncing 40
#define number_tec 4

typedef struct {
	gpioMap_t tecla;
	gpioMap_t led;
} dato_t;

dato_t data[number_tec];
gpioMap_t tec;
uint8_t state[number_tec] = {ON};
uint8_t i = 0;

static void asignacion(dato_t data[]);

void task_LED(void * led_t) {
	dato_t *datos_led = (dato_t*) led_t;
	if (state[datos_led->led-TEC1]) {
		gpioWrite(datos_led->led, state[datos_led->led-TEC1]);
		state[datos_led->led-TEC1] = !state[datos_led->led-TEC1];
		schedulerAddTask(task_LED, led_t, time_diff(datos_led->tecla), 0);
	} else if (!state[datos_led->led-TEC1]) {
		gpioWrite(datos_led->led, state[datos_led->led-TEC1]);
		state[datos_led->led-TEC1] = !state[datos_led->led-TEC1];
	}
}

void task_tecla(void * tecla_t) {
	dato_t *datos_tecla = (dato_t*) tecla_t;
	tec = datos_tecla->tecla;
	if (debouncing(tec) == arriba) {
		schedulerAddTask(task_LED, tecla_t, 0, 0);
	}
}

int main(void) {

	boardConfig();
	asignacion(data);
	schedulerInit();
	schedulerAddTask(task_tecla, &data[0], 0, time_debouncing);
	schedulerAddTask(task_tecla, &data[1], 0, time_debouncing);
	schedulerAddTask(task_tecla, &data[2], 0, time_debouncing);
	schedulerAddTask(task_tecla, &data[3], 0, time_debouncing);
	schedulerStart(1);

	while ( TRUE) {

		schedulerDispatchTasks();

	}
	return 0;
}

static void asignacion(dato_t data[]) {
	for (i = 0; i < number_tec; i++) {
		if (i == 0) {
			data[i].tecla = TEC1;
			data[i].led = LEDB;
		} else if (i == 1) {
			data[i].tecla = TEC2;
			data[i].led = LED1;
		} else if (i == 2) {
			data[i].tecla = TEC3;
			data[i].led = LED2;
		} else if (i == 3) {
			data[i].tecla = TEC4;
			data[i].led = LED3;
		}
	}
}

