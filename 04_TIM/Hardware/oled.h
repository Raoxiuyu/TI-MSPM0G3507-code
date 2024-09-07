#ifndef __OLED_H__
#define __OLED_H__

#include "stdint.h"

void OLED_I2C_Init(void);

int I2C_WriteByte(uint8_t addr,uint8_t data);

void WriteCmd(unsigned char I2C_Command);

void WriteData(unsigned char I2C_Data);

void OLED_Init(void);

void OLED_SetPos(unsigned char x,unsigned char y);

void OLED_Fill(unsigned char Fill_Data);

void OLED_CLS(void);

void OLED_ON(void);
void OLED_OFF(void);

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif

