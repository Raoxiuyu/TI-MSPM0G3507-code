#include "Hardware/adc.h"
#include <ti/driverlib/dl_adc12.h>

bool adc_falg;
float adc_value;


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

 
void ADC0_IRQHandler(void)
{
	switch(DL_ADC12_getPendingInterrupt(ADC0))
	{
		case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
			adc_falg = true;
			break;
		default:
			break;
	}
}