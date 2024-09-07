#include "Hardware/adc.h"
#include <stdbool.h>
#include <ti/driverlib/dl_adc12.h>
#include "Hardware/led.h"
#include "ti/driverlib/dl_flashctl.h"
#include "ti_msp_dl_config.h"
#include "arm_math.h"
#include "arm_const_structs.h"          //必须包含，要不然找不到arm_cfft_sR_f32_len1024
bool adc_falg;
float adc_value;
float adc_avge=0;  //直流分量
#define ADC_SAMPLE_SIZE (1024)
//当启用FIFO时，2个转换结果会被压缩为一个32位存放在FIFODATA寄存器
//所以,读取FIFO的次数要减半,右移一位
#define ADC_FIFO_SAMPLES (ADC_SAMPLE_SIZE >> 1)
uint16_t gADCSamples[ADC_SAMPLE_SIZE];
bool check_dma_ADC;


void adc_init(void)          //使用DMA不用，中断使用
{
	NVIC_EnableIRQ(ADC0_INT_IRQn);
	adc_falg = false;
}


void adc_get(void)
{
	adc_falg =false;
	
	DL_ADC12_startConversion(ADC0);
	
	// while(adc_falg==false);
	
	adc_value =  DL_ADC12_getMemResult(ADC0,DL_ADC12_MEM_IDX_0)*3.3/4096;
	
	DL_ADC12_enableConversions(ADC0);
	
}

void dma_init()
{
    check_dma_ADC=false;
    NVIC_EnableIRQ(ADC0_INT_IRQn);
    DL_ADC12_startConversion(ADC0);
    DL_DMA_setSrcAddr(DMA, 0,(uint32_t) DL_ADC12_getFIFOAddress(ADC0));
    DL_DMA_setDestAddr(DMA, 0, (uint32_t) &gADCSamples[0]);
    DL_DMA_setTransferSize(DMA, 0, ADC_FIFO_SAMPLES);
    DL_DMA_enableChannel(DMA, 0);
}

//***************************************************************   FFT   start  ********************************
float data2handle[2 * ADC_SAMPLE_SIZE];               //处理虚实部的数组
float FFT_Output[ADC_SAMPLE_SIZE];                //结果

void FFT_pro(void) 
{
    if(check_dma_ADC == true)
    {

        // FFT process here
        //...
        check_dma_ADC = false;
        DL_ADC12_disableConversions(ADC0);
        DL_DMA_disableChannel(DMA, 0);
        //...
        // After FFT process, you can get the result from gADCSamples[] array.
        //...
        Create_data2handle(gADCSamples);      
        arm_cfft_f32(&arm_cfft_sR_f32_len1024,data2handle, 0, 1);                        //FFT处理
        arm_cmplx_mag_f32(data2handle,FFT_Output,ADC_SAMPLE_SIZE);
    }
}

void Create_data2handle(uint16_t *p)
{
    for(uint16_t i = 0; i < ADC_SAMPLE_SIZE; i++)//求平均值，去除直流分量
    {
        adc_avge += gADCSamples[i]*3.3/4096.0f;                                   
    }
    adc_avge = adc_avge/ADC_SAMPLE_SIZE;

    for(uint16_t i = 0;i < ADC_SAMPLE_SIZE; i++)
    {
        data2handle[2 * i]     = p[i]*3.3/4096.0f-adc_avge;      //去除直流分量
        data2handle[2 * i + 1] = 0;
    }
}

//****************************************************************     FFT over        ********************************
void ADC0_IRQHandler(void)
{
	switch(DL_ADC12_getPendingInterrupt(ADC0))
	{
		// case DL_ADC12_IIDX_MEM0_RESULT_LOADED:   //中断
        case DL_ADC12_IIDX_DMA_DONE:
			check_dma_ADC = true;
			break;
		default:
			break;
	}
}