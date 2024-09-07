
#ifndef _ADF4351_H_
#define _ADF4351_H_


#include "ti_msp_dl_config.h"



#define ADF4351_CLK CLK()
#define ADF4351_OUTPUT_DATA DATA_OUT()
#define ADF4351_LE LE()
#define ADF4351_CE CE()

#define ADF4351_INPUT_DATA DATA_IN()



#define  u32 uint32_t
#define  u8 uint8_t

void ADF4351Init(void);
void ReadToADF4351(u8 count, u8 *buf);
void WriteToADF4351(u8 count, u8 *buf);
void WriteOneRegToADF4351(u32 Regster);
void ADF4351_Init_some(void);
void ADF4351WriteFreq(float Fre);		//	(xx.x) M Hz






// uint8_t CLK()
// {
//     DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_CLK_IOMUX);
// }

// uint8_t DATA_OUT()
// {
//     DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_DATA_IOMUX);
// }
// uint8_t DATA_IN()
// {
//    DL_GPIO_initDigitalInput(GPIO_ADF_PIN_DATA_IOMUX);
// }


// uint8_t LE()
// {
//    DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_LE_IOMUX);
// }

// uint8_t CE()
// {
//     DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_CE_IOMUX);
// }


// DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_CLK_IOMUX);

// DL_GPIO_initDigitalInput(GPIO_ADF_PIN_DATA_IOMUX);

// DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_LE_IOMUX);

// DL_GPIO_initDigitalOutput(GPIO_ADF_PIN_CE_IOMUX);

#endif

