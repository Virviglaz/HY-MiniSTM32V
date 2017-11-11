#include "HY-MiniSTM32V.h"

void MainTask (void * pvPar);

void Init (void)
{
	extern void GLCD_FreeRTOS_Init (uint16_t StartDelay);
	extern ErrorStatus USART_STD_Init (USART_TypeDef* USARTx, uint32_t USART_BaudRate);

	GLCD_FreeRTOS_Init(1000);
	USART_STD_Init(USART1, 9600);
	
	xTaskCreate(MainTask, "GLCD", 100, NULL, tskIDLE_PRIORITY + 1, NULL);
}

void MainTask (void * pvPar)
{
	char * buf = malloc(100);
	uint16_t v = 0;
	
	while(1)
	{
		sprintf(buf, "Value = %u        ", v++);
		
		//GLCD_Print("Hello world\nSecondRow");
		GLCD_Print(buf);
		//vTaskDelete(NULL);
		vTaskDelay(10);
	}
}
