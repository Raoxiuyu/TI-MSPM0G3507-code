#include "Hardware/adc.h"
#include <stdbool.h>
#include <ti/driverlib/dl_adc12.h>
#include "ti_msp_dl_config.h"

bool adc_falg;
float adc_value;

#define ADC_SAMPLE_SIZE (2048)
//当启用FIFO时，2个转换结果会被压缩为一个32位存放在FIFODATA寄存器
//所以,读取FIFO的次数要减半,右移一位
#define ADC_FIFO_SAMPLES (ADC_SAMPLE_SIZE >> 1)
uint16_t gADCSamples[ADC_SAMPLE_SIZE];
bool check_dma_ADC;


void adc_init(void)
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
    DL_ADC12_startConversion(ADC0);
    DL_DMA_setSrcAddr(DMA, 0,(uint32_t) DL_ADC12_getFIFOAddress(ADC0));
    DL_DMA_setDestAddr(DMA, 0, (uint32_t) &gADCSamples[0]);
    DL_DMA_setTransferSize(DMA, 0, ADC_FIFO_SAMPLES);
    DL_DMA_enableChannel(DMA, 0);
}



 
void ADC0_IRQHandler(void)
{
	switch(DL_ADC12_getPendingInterrupt(ADC0))
	{
		// case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
        case DL_ADC12_IIDX_DMA_DONE:
			check_dma_ADC = true;
			break;
		default:
			break;
	}
}