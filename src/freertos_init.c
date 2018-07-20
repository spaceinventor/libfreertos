/*
 * freertos_init.c
 *
 *  Created on: Aug 4, 2017
 *      Author: johan
 */

#include <FreeRTOS.h>
#include <string.h>

unsigned int freertos_clock_hz = 0;
unsigned int freertos_tick_rate_hz = 0;

void freertos_set_clocks(unsigned int clock_hz, unsigned int tick_rate_hz) {
	freertos_clock_hz = clock_hz;
	freertos_tick_rate_hz = tick_rate_hz;
}

#if configSUPPORT_STATIC_ALLOCATION
/* static memory allocation for the IDLE task */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
#endif

