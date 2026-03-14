#include <FreeRTOS.h>
#include <freertos_config.h>

/* This is an assumption we always want to place the heap in SDRAM
 * Or place it in freertos with a configurable section name */
#if configAPPLICATION_ALLOCATED_HEAP==1

#define STR1(x) #x
#define STR(x)  STR1(x)

uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((section(STR(configHEAP_SECTION))));
#endif