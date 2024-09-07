#include "oled.h"
#include "ti/driverlib/dl_i2c.h"
#include <ti/driverlib/m0p/dl_core.h>

#include "oled.h"
#include "ti_msp_dl_config.h"
#include "key.h"
#include "font.h"

//***********  SCL -> PA31  *********************//
//***********  SDA -> PA28 *********************//

#define OLED_ADDR   0x3C

void OLED_I2C_Init(void)
{
	
}

//向OLED寄存器地址写一个byte的数据
int I2C_WriteByte(uint8_t addr,uint8_t data)
{
  uint8_t buff[2] = {0};
  buff[0] = addr;
  buff[1] = data;
  /* Wait for I2C to be Idle */
  while (!(DL_I2C_getControllerStatus(I2C0) & DL_I2C_CONTROLLER_STATUS_IDLE));
  /* Send the packet to the controller.
   * This function will send Start + Stop automatically.
   */
  DL_I2C_startControllerTransfer(I2C0, OLED_ADDR,DL_I2C_CONTROLLER_DIRECTION_TX, 2);
  DL_I2C_fillControllerTXFIFO(I2C0, &buff[0], 2);
  /* Poll until the Controller writes all bytes */
  while (DL_I2C_getControllerStatus(I2C0) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

  /* Trap if there was an error */
  if (DL_I2C_getControllerStatus(I2C0) & DL_I2C_CONTROLLER_STATUS_ERROR)
	{
     /* LED will remain high if there is an error */
     __BKPT(0);
  }
  return 0;
}



//写指令
void WriteCmd(unsigned char I2C_Command)
{
   I2C_WriteByte(0x00,I2C_Command);
}

//写数据
void WriteData(unsigned char I2C_Data)
{
   I2C_WriteByte(0x40,I2C_Data);
}

//厂家初始化代码
void OLED_Init(void)
{
    OLED_I2C_Init();
    delay_ms(100);
    WriteCmd(0xAE); //display off
    WriteCmd(0x20); //Set Memory Addressing Mode
    WriteCmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    WriteCmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
    WriteCmd(0xc8); //Set COM Output Scan Direction
    WriteCmd(0x00); //---set low column address
    WriteCmd(0x10); //---set high column address
    WriteCmd(0x40); //--set start line address
    WriteCmd(0x81); //--set contrast control register
    WriteCmd(0xff); //áá?èμ÷?ú 0x00~0xff
    WriteCmd(0xa1); //--set segment re-map 0 to 127
    WriteCmd(0xa6); //--set normal display
    WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
    WriteCmd(0x3F); //
    WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    WriteCmd(0xd3); //-set display offset
    WriteCmd(0x00); //-not offset
    WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
    WriteCmd(0xf0); //--set divide ratio
    WriteCmd(0xd9); //--set pre-charge period
    WriteCmd(0x22); //
    WriteCmd(0xda); //--set com pins hardware configuration
    WriteCmd(0x12);
    WriteCmd(0xdb); //--set vcomh
    WriteCmd(0x20); //0x20,0.77xVcc
    WriteCmd(0x8d); //--set DC-DC enable
    WriteCmd(0x14); //
    WriteCmd(0xaf); //--turn on oled panel
		OLED_CLS();
}

//设置光标起始坐标（x,y）
void OLED_SetPos(unsigned char y,unsigned char x)
{
        WriteCmd(0xb0+y);
        WriteCmd( (x & 0xf0) >> 4 | 0x10 );
        WriteCmd( (x & 0x0f) | 0x01 );
}

//填充整个屏幕
void OLED_Fill(unsigned char Fill_Data)
{
        unsigned char m,n;

        for(m=0;m<8;m++)
        {
                WriteCmd(0xb0+m);
                WriteCmd(0x00);
                WriteCmd(0x10);

                for(n=0;n<128;n++)
                {
                        WriteData(Fill_Data);
                }
        }
}

//清屏
void OLED_CLS(void)
{
        OLED_Fill(0x00);
}

//将OLED从休眠中唤醒
void OLED_ON(void)
{
        WriteCmd(0xAF);
        WriteCmd(0x8D);
        WriteCmd(0x14);
}

//让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
void OLED_OFF(void)
{
        WriteCmd(0xAE);
        WriteCmd(0x8D);
        WriteCmd(0x10);
}



/**
  * @brief  OLED显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetPos((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		WriteData(F8X16[Char - ' '][i]);			//显示上半部分内容
	}
	OLED_SetPos((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		WriteData(F8X16[Char - ' '][i + 8]);		//显示下半部分内容
	}
}

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */

void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, '0' + (Number / OLED_Pow(10, Length - i - 1) % 10 ));
	}
}

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

