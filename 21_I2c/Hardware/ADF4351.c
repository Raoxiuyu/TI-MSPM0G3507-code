


#include "ADF4351.h"
#include "key.h"
#include "ti/driverlib/dl_gpio.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


#define ADF4351_R0			((u32)0X2C8018)
#define ADF4351_R1			((u32)0X8029)
#define ADF4351_R2			((u32)0X10E42)
#define ADF4351_R3			((u32)0X4B3)
#define ADF4351_R4			((u32)0XEC803C)
#define ADF4351_R5			((u32)0X580005)

#define ADF4351_R1_Base	((u32)0X8001)
#define ADF4351_R4_Base	((u32)0X8C803C)
#define ADF4351_R4_ON	  ((u32)0X8C803C)
#define ADF4351_R4_OFF	((u32)0X8C883C)

#define ADF4351_RF_OFF	((u32)0XEC801C)

#define ADF4351_PD_ON		((u32)0X10E42)
#define ADF4351_PD_OFF	((u32)0X10E02)

// void ADF_Output_GPIOInit(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStruct;
	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
// 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
// 	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
// }

// void ADF_Input_GPIOInit(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStruct;
	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
// 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
// 	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
// 	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 
// 	GPIO_Init(GPIOB, &GPIO_InitStruct);	
// }

void delay (int length)
{
	while (length >0)
    	length--;
}

void WriteToADF4351(u8 count, u8 *buf)
{
	u8 ValueToWrite = 0;
	u8 i = 0;
	u8 j = 0;
	
//	ADF_Output_GPIOInit();
	DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_DATA_IOMUX);

    
	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_13);
	delay_us(1);
	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_6);
	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_16);;
	delay_us(1);
	
	for(i = count; i>0; i--)
	{
		ValueToWrite = *(buf+i-1);
		for(j=0; j<8; j++)
		{
			if(0x80 == (ValueToWrite & 0x80))
			{
                
				DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_0);
			}
			else
			{
				DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_0);
			}
			delay_us(1);
			DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_6);
			delay_us(1);
			ValueToWrite <<= 1;
			DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_6);	
		}
	}
	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_0);
	delay_us(1);
	DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_16);;
	delay_us(1);
	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_16);;
}


// void ReadToADF4351(u8 count, u8 *buf)
// {
// 	u8 i = 0;
// 	u8 j = 0;
// 	u8 iTemp = 0;
// 	u8 RotateData = 0;
	
//     DL_GPIO_initDigitalInput(GPIO_ADF_PIN_DATA_IOMUX);
// 	// ADF_Input_GPIOInit();
// 	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_13);
// 	delay_us(1);
// 	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_6);
// 	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_16);
// 	delay_us(1);
	
// 	for(i = count; i>0; i--)
// 	{
// 		for(j = 0; j<8; j++)
// 		{
// 			RotateData <<=1;
// 			delay_us(1);
// 			iTemp = (bool)DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_0);
// 			DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_6);
// 			if(0x01 == (iTemp&0x01))
// 			{
// 				RotateData |= 1;
// 			}
// 			delay_us(1);
// 			DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_6);
// 		}
// 		*(buf+i-1) = RotateData;
// 	}
// 	delay_us(1);
// 	DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_16);
// 	delay_us(1);
// 	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_16);

// }

void ADF4351Init(void)
{
	u8 buf[4] = {0,0,0,0};
	
	// ADF_Output_GPIOInit();
	DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_CLK_IOMUX);

	buf[3] = 0x00;				//35M
	buf[2] = 0x58;
	buf[1] = 0x00;				//write communication register 0x00580005 to control the progress 
 	buf[0] = 0x05;				//to write Register 5 to set digital lock detector
	WriteToADF4351(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0xec;				//(DB23=1)The signal is taken from the VCO directly;(DB22-20:4H)the RF divider is 16;(DB19-12:50H)R is 80
	buf[1] = 0x80;				//(DB11=0)VCO powerd up;
 	buf[0] = 0x3C;				//(DB5=1)RF output is enabled;(DB4-3=3H)Output power level is 5
	WriteToADF4351(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0x00;
	buf[1] = 0x04;				//(DB14-3:96H)clock divider value is 150.
 	buf[0] = 0xB3;
	WriteToADF4351(4,buf);	

	buf[3] = 0x00;
	buf[2] = 0x01;				//(DB6=1)set PD polarity is positive;(DB7=1)LDP is 6nS;
	buf[1] = 0x0E;				//(DB8=0)enable fractional-N digital lock detect;
 	buf[0] = 0x42;				//(DB12-9:7H)set Icp 2.50 mA;
	WriteToADF4351(4,buf);		//(DB23-14:1H)R counter is 1

	buf[3] = 0x00;
	buf[2] = 0x00;
	buf[1] = 0x80;			   //(DB14-3:6H)MOD counter is 6;
 	buf[0] = 0x29;			   //(DB26-15:6H)PHASE word is 1,neither the phase resync 
	WriteToADF4351(4,buf);	   //nor the spurious optimization functions are being used
							   //(DB27=1)prescaler value is 8/9

	buf[3] = 0x00;
	buf[2] = 0x2c;
	buf[1] = 0x80;
 	buf[0] = 0x18;				//(DB14-3:0H)FRAC value is 0;
	WriteToADF4351(4,buf);		//(DB30-15:140H)INT value is 320;	
}

void WriteOneRegToADF4351(u32 Regster)
{
	u8 buf[4] = {0,0,0,0};
	buf[3] = (u8)((Regster>>24)&(0X000000FF));
	buf[2] = (u8)((Regster>>16)&(0X000000FF));
	buf[1] = (u8)((Regster>>8) &(0X000000FF));
	buf[0] = (u8)((Regster)&(0X000000FF));
	WriteToADF4351(4,buf);	
}
void ADF4351_Init_some(void)
{
	WriteOneRegToADF4351(ADF4351_R2);
	WriteOneRegToADF4351(ADF4351_R3);
	WriteOneRegToADF4351(ADF4351_R5);
}

void ADF4351WriteFreq(float Fre)		//	fre单位MHz -> (xx.x) M Hz
{
	u16 Fre_temp, N_Mul = 1, Mul_Core = 0;
	u16 INT_Fre, Frac_temp, Mod_temp, i;
	u32 W_ADF4351_R0 = 0, W_ADF4351_R1 = 0, W_ADF4351_R4 = 0;
	float multiple;
	
	if(Fre < 35.0)
		Fre = 35.0;
	if(Fre > 4400.0)
		Fre = 4400.0;
	Mod_temp = 1000;
	Fre = ((float)((u32)(Fre*10)))/10;
	
	Fre_temp = Fre;
	for(i = 0; i < 10; i++)
	{
		if(((Fre_temp*N_Mul) >= 2199.9) && ((Fre_temp*N_Mul) <= 4400.1))
			break;
		Mul_Core++;
		N_Mul = N_Mul*2;
	}
	
	multiple = (Fre*N_Mul)/25;		//25：鉴相频率，板载100M参考，经寄存器4分频得25M鉴相。若用户更改为80M参考输入，需将25改为20；10M参考输入，需将25改为2.5，以此类推。。。
	INT_Fre = (u16)multiple;
	Frac_temp = ((u32)(multiple*1000))%1000;
	while(((Frac_temp%5) == 0) && ((Mod_temp%5) == 0))
	{
		Frac_temp = Frac_temp/5;
		Mod_temp = Mod_temp/5;
	}
	while(((Frac_temp%2) == 0)&&((Mod_temp%2) == 0))
	{
		Frac_temp = Frac_temp/2;
		Mod_temp = Mod_temp/2;
	}
	
	Mul_Core %= 7;
	W_ADF4351_R0 = (INT_Fre<<15)+(Frac_temp<<3);
	W_ADF4351_R1 = ADF4351_R1_Base + (Mod_temp<<3);
	W_ADF4351_R4 = ADF4351_R4_ON + (Mul_Core<<20);
	
	WriteOneRegToADF4351(ADF4351_RF_OFF);
	WriteOneRegToADF4351(W_ADF4351_R0);
	WriteOneRegToADF4351(W_ADF4351_R1);
	WriteOneRegToADF4351(W_ADF4351_R4);
}


