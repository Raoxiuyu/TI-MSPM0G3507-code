#include "Hardware/interrupt.h"

#include <ti/driverlib/dl_timera.h>
#include <ti/driverlib/dl_timerg.h>
#include "Hardware/led.h"
#include "Hardware/uart.h"
#include "stdint.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timer.h"
#include "ti_msp_dl_config.h"
// #include "ti_msp_dl_config.h"



void TIMEG0_init(void)
{
	NVIC_EnableIRQ(TIMG0_INT_IRQn);  //
	DL_TimerG_startCounter(TIMG0);
}

void TIMG0_IRQHandler()            //
{
	DL_GPIO_togglePins(GPIOA,DL_GPIO_PIN_0);
}

//------------------------------------------------------   捕获 ----------------------------------------------------------------


void Capture_init()
{
    NVIC_EnableIRQ(TIMA1_INT_IRQn);
    DL_TimerG_startCounter(TIMA1);
}


uint32_t captureCent_Neg_Now;
uint32_t captuerCent_Neg_Past;
uint32_t captureCent_Pos_Now;
uint32_t captureCent_Pos_Past;


uint32_t PWM_Detect_period;
uint32_t PWM_Detect_duty;
uint32_t SYS_CLK=32000000;


float pwm_duty;
float PWM_period;


void Capture_pro()
{
    if((captureCent_Pos_Past>captureCent_Pos_Now)&&(captuerCent_Neg_Past>captureCent_Neg_Now))
    {
        PWM_period = (captureCent_Pos_Past - captureCent_Pos_Now);
        if(captureCent_Pos_Now>captureCent_Neg_Now)
        {
            pwm_duty = (captureCent_Pos_Now - captureCent_Neg_Now);
        }
        else {
            pwm_duty = (captureCent_Pos_Past - captureCent_Neg_Now);
        }
    }

    PWM_Detect_period = (float)SYS_CLK/PWM_period;
    PWM_Detect_duty = (float)pwm_duty / PWM_period*100;
}



bool gCheckEdgeCaptureTime = false;

void CAPTURE_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(CAPTURE_0_INST)) {
        case DL_TIMERG_IIDX_CC1_DN:
            gCheckEdgeCaptureTime = true;
            captureCent_Pos_Past = captureCent_Pos_Now;
            captureCent_Pos_Now=DL_TimerA_getCaptureCompareValue(CAPTURE_0_INST,DL_TIMER_CC_1_INDEX);
            break;
        case DL_TIMERG_IIDX_CC0_DN:
            captuerCent_Neg_Past = captureCent_Neg_Now;
            captureCent_Neg_Now=DL_TimerA_getCaptureCompareValue(CAPTURE_0_INST,DL_TIMER_CC_0_INDEX);
        default:
            break;
    }
}

//------------------------------------------------------   捕获 ----------------------------------------------------------------