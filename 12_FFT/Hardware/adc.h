#ifndef _ADC_H
#define _ADC_H
#include "stdint.h"
#include "string.h"
#include "stdbool.h"
extern float adc_value;

void adc_init(void);
void ADC0_IRQHandler(void);
void adc_get(void);
void dma_init(void);

#define ADC_SAMPLE_SIZE (1024)
#define ADC_FIFO_SAMPLES (ADC_SAMPLE_SIZE >> 1)

void Create_data2handle(uint16_t *p);
void FFT_pro(void);

extern uint16_t gADCSamples[ADC_SAMPLE_SIZE];
extern bool check_dma_ADC;
#endif