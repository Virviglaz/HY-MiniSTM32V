#include "HY-MiniSTM32V.h"
#include "GLCD_FreeRTOS.h"
#include "font8x8_basic.h"

QueueHandle_t GLCD_Queue;

void GLCD_Handler (void * pvPar);
void GLCD_PrintMessage (LCD_MSG_StructTypeDef * LCD_MSG);

void GLCD_FreeRTOS_Init (uint16_t StartDelay)
{
	static uint16_t startdelay;
	startdelay = StartDelay;

	/* Init STM32 HW */
	SSD1289_GPIOConfig();
	SSD1289_FSMCConfig();
	
	/* Create a queue for GLCD handler task */
	GLCD_Queue = xQueueCreate(10, sizeof(LCD_MSG_StructTypeDef*));
	
	/* Create task for GLCD handler */
	xTaskCreate(GLCD_Handler, "GLCD", 100, &startdelay, tskIDLE_PRIORITY + 1, NULL);
}

void GLCD_Handler (void * pvPar)
{
	static SSD1289_StructTypeDef GLCD;
	LCD_MSG_StructTypeDef * LCD_MSG;
	TickType_t * par = pvPar;
	vTaskDelay(* par);
	
	/* GLCD driver init */
	GLCD.DelayFunc = Delay;
	GLCD.RamPrepare = GLCD_RamPrepare;
	GLCD.ReadReg = GLCD_ReadReg;
	GLCD.WriteRam = GLCD_WriteRam;
	GLCD.WriteReg = GLCD_WriteReg;
	GLCD.Fontbuffer = malloc (8 * 8 * 2);
	
	SSD1289_Init(&GLCD);
	SSD1289_Clear(Black);
	
	while(1)
		if (xQueueReceive(GLCD_Queue, &LCD_MSG, portMAX_DELAY) == pdTRUE)
			GLCD_PrintMessage(LCD_MSG);
}

void GLCD_Print (char * text)
{
	LCD_MSG_StructTypeDef * LCD_MSG = malloc(sizeof(*LCD_MSG));
	char * buf = malloc(strlen(text));
	strcpy(buf, text);
	LCD_MSG->buf = buf;
	LCD_MSG->MSG_Type = LCD_MSG_Text;
	xQueueSend(GLCD_Queue, &LCD_MSG, 0);
}

void GLCD_PrintMessage (LCD_MSG_StructTypeDef * LCD_MSG)
{
	static uint16_t Row = 0;
	Row += SSD1289_PrintText(0, Row, 8, 8, (char*)font8x8_basic, LCD_MSG->buf, White, Black);

	free(LCD_MSG->buf);
	free(LCD_MSG);

	if (Row < 320 - 8)
		Row += 8;
	else
	{
		Row = 0;
		SSD1289_Clear(Black);
	}
}
