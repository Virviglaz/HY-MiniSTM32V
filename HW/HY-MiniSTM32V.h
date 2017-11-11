#ifndef HY_MINISTM32V_H
#define HY_MINISTM32V_H

/* Include standart headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Include FreeRTOS headers */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

/* Include standart STM32F103 header */
#include "stm32f10x.h"

/* Drivers include */
#include "SSD1289.h"

#define LCD_REG              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x60020000)) /* RS = 1 */

#ifndef TRACE
	#define TRACE(fmt, ...) \
							do { printf(fmt, ##__VA_ARGS__); printf("\n"); } while (0)
#endif

#ifndef	DEBUG
	#define DEBUG(fmt, ...) \
							do \
							{ \
								printf("%s:%d:%s(): ", __FILE__, __LINE__, __func__); \
								printf(fmt, ##__VA_ARGS__); \
								printf("\n"); \
							}while (0)					
#endif

/* Define FreeRTOS debug functions */
void vApplicationMallocFailedHook( void );
void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName );
void AssertFailed (void);

/* GLCD HW init functions */
void SSD1289_GPIOConfig (void);
void SSD1289_FSMCConfig (void);
							
/* GLCD Public functions */
void GLCD_Print (char * text);

/* GLCD Driver functions */
void GLCD_WriteReg (uint8_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t GLCD_ReadReg (uint8_t LCD_Reg);
void GLCD_RamPrepare (void);
void GLCD_WriteRam (uint16_t RGB);
void Delay (uint16_t ms);
#endif
