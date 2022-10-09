#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#include <hal_sleep.h>

extern void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
extern void vApplicationMallocFailedHook(void);
extern void vApplicationIdleHook(void);

#if configSUPPORT_STATIC_ALLOCATION
/* static memory allocation for the IDLE task */
static StaticTask_t xIdleTaskTCBBuffer;

__attribute__((section(".noinit")))
StackType_t xIdleStack[128];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = 128;
}
#endif

#if (configSUPPORT_DYNAMIC_ALLOCATION == 0)
char * __heap_start = 0;
char * __heap_end = 0;
#endif

/**
 * \brief Called if stack overflow during execution
 */
extern void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
	printf("stack overflow %p %s\r\n", pxTask, pcTaskName);
	/* If the parameters have been corrupted then inspect pxCurrentTCB to
	 * identify which task has overflowed its stack.
	 */
	for (;;) {
	}
}

extern void vApplicationMallocFailedHook(void)
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

	/* Force an assert. */
	printf("Malloc failed\n");
}

void vApplicationTickHook(void) {
}

extern void vApplicationIdleHook(void) {
	sleep(0);
}

extern void __attribute__((weak)) cpu_reset(void);
void cpu_reset(void) {
	_reset_mcu();
}

int usleep(__useconds_t __useconds) {
	vTaskDelay((__useconds / 1000) * (1000 / configTICK_RATE_HZ));
	return 0;
}

void vConfigureTimerForRunTimeStats(void) {
	return;
}

uint64_t clock_get_nsec_from_isr(void);
uint32_t vGetRunTimeCounterValue(void) {
	uint32_t usec = clock_get_nsec_from_isr() / 1000;
	return usec;
}
