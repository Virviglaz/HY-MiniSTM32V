#include "HY-MiniSTM32V.h"

int main (void)
{
	extern void Init (void);
	Init();
	
	vTaskStartScheduler();
	
}
