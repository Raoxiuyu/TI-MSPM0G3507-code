#include "Hardware/key.h"
#include "ti/driverlib/dl_gpio.h"
#include <ti/driverlib/m0p/dl_core.h>

#define cyctime 32               //ʱ��Ƶ��Ϊ��׼

void delay_ms(uint16_t ms)
{
	while(ms--)
		delay_cycles(cyctime*100);  //��ʱ�ӵ�Ƶ��ѭ��   1/32M    �ǵü�ͷ�ļ� #include <ti/driverlib/m0p/dl_core.h>
}

void delay_us(uint16_t us)
{
	while(us--)
		delay_cycles(cyctime);
}


uint8_t key1_get(void)
{
	uint8_t KeyNum=0;
	if(DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_18) >0  )
	{
		delay_ms(15);
		if(DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_18) >0 )
		{
			while(DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_18));
			KeyNum=1;
		}
		else
			KeyNum=0;
	}
	return KeyNum;
}


uint8_t key2_get(void)
{
	uint8_t KeyNum=0;
	if(DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_21) == 0)
	{
		delay_ms(15);
		if(DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_21) == 0)
		{
//			while(!DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_21));
			KeyNum=1;
		}
		else
			KeyNum=0;
	}
	return KeyNum;
}

