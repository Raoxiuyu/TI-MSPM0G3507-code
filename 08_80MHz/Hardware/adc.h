#ifndef _ADC_H
#define _ADC_H

extern float adc_value;

void adc_init(void);
void ADC0_IRQHandler(void);
void adc_get(void);

#endif