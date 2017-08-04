/*
 * freertos_init.c
 *
 *  Created on: Aug 4, 2017
 *      Author: johan
 */

#include <FreeRTOS.h>

unsigned int freertos_clock_hz = 0;
unsigned int freertos_tick_rate_hz = 0;

void freertos_set_clocks(unsigned int clock_hz, unsigned int tick_rate_hz) {
	freertos_clock_hz = clock_hz;
	freertos_tick_rate_hz = tick_rate_hz;
}
