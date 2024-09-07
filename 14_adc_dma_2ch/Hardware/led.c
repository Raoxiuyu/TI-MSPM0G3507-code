#include "Hardware/led.h"
#include "ti/driverlib/dl_gpio.h"

void LED1_ON(void)
{
	DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_0);
}

void LED1_OFF(void)
{
	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_0);
}


void LED2_blue_ON(void)
{
	DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_22);
}

void LED2_blue_OFF(void)
{
	DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_22);
}