#include "Hardware/key.h"
#include "Hardware/led.h"
#include "ti/driverlib/dl_gpio.h"
#include <ti/driverlib/m0p/dl_core.h>
#include "ti_msp_dl_config.h"
#include "stdio.h"

#define cyctime CPUCLK_FREQ/1000000               //


void key_pro(void)
{
    if(key1_get()==1)
    {
        printf("hello");
        LED2_blue_ON();
    }
    if(key2_get()==1)
    {
        LED2_blue_OFF();
    }   
}


void delay_ms(uint16_t ms)
{
	while(ms--)
		delay_cycles(cyctime*1000);  //
}

void delay_us(uint16_t us)
{
	while(us--)
		delay_cycles(cyctime);
}

// void delay_ns(uint16_t ns)
// {
// 	while(ns--)
// 		delay_cycles(cyctime/1000);
// }

void delay_ns(uint8_t t)
{
	do {
			;
	} while (--t); 
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

