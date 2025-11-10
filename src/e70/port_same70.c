#include <stdio.h>
#include <inttypes.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Atmel START */
#include "parts.h"

void vApplicationAssert( const char *pcFileName, uint32_t ulLine ) __attribute__((weak));

void vApplicationAssert( const char *pcFileName, uint32_t ulLine )
{
volatile const char *pcLocalFileName = pcFileName; /* To prevent pcFileName being optimized away. */
volatile uint32_t ulLocalLine = ulLine; /* To prevent ulLine being optimized away. */

	/* Prevent compile warnings about the following two variables being set but
	not referenced.  They are intended for viewing in the debugger. */
	( void ) pcLocalFileName;
	( void ) ulLocalLine;

	printf( "Assert failed in file %s, line %lu\r\n", pcLocalFileName, ulLocalLine );

	NVIC_SystemReset();
}
