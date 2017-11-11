#ifndef GLCD_H
#define GLCD_H

typedef enum
{
	LCD_MSG_Text,
	LCD_MSG_Pic,
}LCD_MSG_EnumTypeDef;

typedef struct
{
	LCD_MSG_EnumTypeDef MSG_Type;
	char * buf;
}LCD_MSG_StructTypeDef;

#endif
