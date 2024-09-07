#include "Hardware/interrupt.h"

#include <ti/driverlib/dl_timera.h>
#include <ti/driverlib/dl_timerg.h>
#include "stdint.h"
#include "ti/driverlib/dl_gpio.h"

void TIMEG0_init(void)
{
	NVIC_EnableIRQ(TIMG0_INT_IRQn);  //ʹ�ܶ�ʱ��G0
	DL_TimerG_startCounter(TIMG0);
}

void TIMG0_IRQHandler()            //�жϷ�����    �Ѿ��궨�����
{
	DL_GPIO_togglePins(GPIOA,DL_GPIO_PIN_0);
}