#include "Hardware/interrupt.h"

#include <ti/driverlib/dl_timera.h>
#include <ti/driverlib/dl_timerg.h>
#include "stdint.h"
#include "ti/driverlib/dl_gpio.h"

void TIMEG0_init(void)
{
	NVIC_EnableIRQ(TIMG0_INT_IRQn);  //使能定时器G0
	DL_TimerG_startCounter(TIMG0);
}

void TIMG0_IRQHandler()            //中断服务函数    已经宏定义好了
{
	DL_GPIO_togglePins(GPIOA,DL_GPIO_PIN_0);
}