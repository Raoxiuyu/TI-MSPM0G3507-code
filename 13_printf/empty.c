/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"

#include "Hardware/interrupt.h"
#include "Hardware/led.h"
#include "Hardware/key.h"
#include "Hardware/oled.h"
#include "Hardware/adc.h"
#include "Hardware/uart.h"
#include "stdio.h"
#include "stdint.h"
#include "arm_math.h"



uint16_t lcd_buf[20];

int main(void)
{
    SYSCFG_DL_init();


    OLED_Init();
    OLED_CLS();

    TIMEG0_init();             //打开定时器

    OLED_ShowString(2,2, "DATE 2024-4-14");
    


    DL_Timer_startCounter(TIMG6);   //PB引脚PWM    PWM产生只需要这个开启就行
	//DL_TimerG_setCaptureCompareValue();   //修改占空比

    

    adc_init();
    uart_init();
    dma_init();


    while (1)
    {
        // adc_get();

        sprintf((char*)lcd_buf,"%.2f",adc_value);
       
        OLED_ShowString(3,2, (char*)lcd_buf);

        
        key_pro();
        // if(check_dma_ADC==true)
        // {
        //     for(uint16_t i=0;i<1024;i++)
        //     {
        //         printf("%.2f ",gADCSamples);
        //     }
        // }

        if(rx_flag==1)
        {
            delay_ms(5);
            rx_flag=0;
            uart_pro();
        }
    }
}
