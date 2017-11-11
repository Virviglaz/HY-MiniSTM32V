#include "HY-MiniSTM32V.h"

/* Redefine stdlib functions */
void * malloc(size_t s) { return pvPortMalloc(s); }
void free( void *pv ) { vPortFree( pv ); }

void vApplicationMallocFailedHook( void )
{
	/* Out of memory */
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName )
{
	/* Stack overflow */
}

void AssertFailed (void)
{
	/* Bad parameters */
}

