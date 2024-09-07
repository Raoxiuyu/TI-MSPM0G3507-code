#include "Hardware/interrupt.h"
#include <machine/_stdint.h>
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

uint16_t cent1=0;                  //触发的次数
uint16_t cent2=0;                  //当前触发
uint16_t freq1=0;                  //

void TIMG0_IRQHandler()            //
{
	DL_GPIO_togglePins(GPIOA,DL_GPIO_PIN_0);                //一秒中断


    //捕获内容
    cent2= DL_TimerA_getCaptureCompareValue(CAPTURE_1_INST,DL_TIMER_CC_0_INDEX);
    freq1= cent2+cent1*65535;
    // cent1=0;
    // cent2=0;
}

//------------------------------------------------------   捕获 ----------------------------------------------------------------


void Capture_init()
{
    NVIC_EnableIRQ(TIMA1_INT_IRQn);
    DL_TimerA_startCounter(TIMA1);

    NVIC_EnableIRQ(TIMG8_INT_IRQn);
    DL_TimerG_startCounter(TIMG8);
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


bool gCheckEdgeCaptureTime = false;

void Capture_pro()
{
    if(gCheckEdgeCaptureTime == true)
    {
        gCheckEdgeCaptureTime = false;
        // if((captureCent_Pos_Past>captureCent_Pos_Now)&&(captuerCent_Neg_Past>captureCent_Neg_Now))
        // {
            PWM_period = (captureCent_Pos_Past - captureCent_Pos_Now);
        //     if(captureCent_Pos_Now>captureCent_Neg_Now)
        //     {
        //         pwm_duty = (captureCent_Pos_Now - captureCent_Neg_Now);
        //     }
        //     else {
                pwm_duty = (captureCent_Pos_Past - captureCent_Neg_Now);
        //     }
        // }

        PWM_Detect_period = (float)SYS_CLK/PWM_period;
        PWM_Detect_duty = (float)pwm_duty / PWM_period*100;
    }
}


void CAPTURE_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(CAPTURE_0_INST)) {
        case DL_TIMERG_IIDX_CC1_DN:
            gCheckEdgeCaptureTime = true;
            captureCent_Pos_Past = captureCent_Pos_Now;
            captureCent_Pos_Now=DL_TimerA_getCaptureCompareValue(CAPTURE_0_INST,DL_TIMER_CC_1_INDEX);
            DL_TimerG_setTimerCount(CAPTURE_0_INST, DL_TimerG_getLoadValue(CAPTURE_0_INST));
            break;
        case DL_TIMERG_IIDX_CC0_DN:
            // DL_TimerG_setTimerCount(CAPTURE_0_INST, DL_TimerG_getLoadValue(CAPTURE_0_INST));
            captuerCent_Neg_Past = captureCent_Neg_Now;
            captureCent_Neg_Now=DL_TimerA_getCaptureCompareValue(CAPTURE_0_INST,DL_TIMER_CC_0_INDEX);
        default:
            break;
    }


   
}

void CAPTURE_1_INST_IRQHandler(void)
{
    cent1++;
 switch (DL_TimerG_getPendingInterrupt(CAPTURE_1_INST)) {
        case DL_TIMERG_IIDX_CC0_DN:
            cent1++;
            // captuerCent_Neg_Past = captureCent_Neg_Now;
            // captureCent_Neg_Now=DL_TimerA_getCaptureCompareValue(CAPTURE_0_INST,DL_TIMER_CC_0_INDEX);
        default:
            break;
    }
}
//------------------------------------------------------   捕获 ----------------------------------------------------------------