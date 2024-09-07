//-----------------------------------------------------------------
//-----------------------------------------------------------------
#ifndef _AD9910_H
#define _AD9910_H

#include "ti/driverlib/dl_gpio.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


#define AD9910_MRT_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_12))         
#define AD9910_MRT_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_12))

#define AD9910_CSN_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_17))         
#define AD9910_CSN_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_17))

#define AD9910_SCK_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_15))         
#define AD9910_SCK_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_15))

#define AD9910_SDI_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_6))         
#define AD9910_SDI_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_6))

#define AD9910_IUP_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_0))         
#define AD9910_IUP_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_0))

#define AD9910_DRH_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_16))         
#define AD9910_DRH_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_16))

#define AD9910_DRC_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_4))         
#define AD9910_DRC_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_4))

#define AD9910_PF0_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_20))         
#define AD9910_PF0_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_20))

#define AD9910_PF1_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_13))         
#define AD9910_PF1_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_13))

#define AD9910_PF2_Set (DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_12))         
#define AD9910_PF2_Clr (DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_12))

#define AD9910_OSK_Set (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_1))      
#define AD9910_OSK_Clr (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_1))

//#define AD9910_TE_Set (MAP_GPIO_setOutputHighOnPin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET))         
//#define AD9910_TE_Clr (MAP_GPIO_setOutputLowOnPin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET))

//#define AD9910_PC_Set (MAP_GPIO_setOutputHighOnPin(GPIOA,GPIO_PIN_14,GPIO_PIN_SET))         
//#define AD9910_PC_Clr (MAP_GPIO_setOutputLowOnPin(GPIOA,GPIO_PIN_14,GPIO_PIN_RESET))

void init_9910(void);
extern void Write_8bit(u8 dat)	;
extern void Write_32bit(u32 dat)	;

extern void AD9910_Init(void);

extern void AD9910_Singal_Profile_Init(void);
extern void AD9910_Singal_Profile_Set(u8 addr,u32 Freq,u16 Amp ,u16 Pha);
extern void Set_Profile(u8 num);

extern void AD9910_Osk_Init(void);
extern void AD9910_Osk_Set(void);

extern void AD9910_DRG_Fre_Init(void);
extern void AD9910_DRG_Freq_set(u32 upper_limit , u32 lower_limit ,u32 dec_step , u32 inc_step , u16 neg_rate ,u16 pos_rate);

extern void AD9910_DRG_AMP_Init(void);
extern void AD9910_DRG_Amp_Set( u32 upper_limit , u32 lower_limit ,u32 dec_step , u32 inc_step , u16 neg_rate ,u16 pos_rate);

extern void AD9910_RAM_Init(void);
extern void AD9910_RAM_ZB_Fre_Init(void);
extern void AD9910_RAM_ZB_Fre_Set(u32 Freq);

extern void AD9910_RAM_Fre_W(void);
extern void AD9910_RAM_AMP_W(void);
extern void AD9910_WAVE_RAM_AMP_W(int mode);
extern void AD9910_RAM_DIR_Fre_R(void);
extern void AD9910_RAM_DIR_AMP_R(void);

extern void AD9910_RAM_RAMP_UP_ONE_Fre_R(void);
extern void AD9910_RAM_RAMP_UP_ONE_AMP_R(void);

extern void AD9910_RAM_RAMP_UP_TWO_Fre_R(void);
extern void AD9910_RAM_RAMP_UP_TWO_AMP_R(void);

extern void AD9910_RAM_BID_RAMP_Fre_R(void);
extern void AD9910_RAM_BID_RAMP_AMP_R(void);

extern void AD9910_RAM_CON_BID_RAMP_Fre_R(void);
extern void AD9910_RAM_CON_BID_RAMP_AMP_R(void);

extern void AD9910_RAM_CON_RECIR_Fre_R(void);
extern void AD9910_RAM_CON_RECIR_AMP_R(void);

extern void AD9910_DRG_Pha_Init(void);
extern void AD9910_DRG_Pha_Set( u32 upper_limit , u32 lower_limit ,u32 dec_step , u32 inc_step , u16 neg_rate ,u16 pos_rate);

extern void AD9910_RAM_Pha_W(void);
extern void AD9910_RAM_DIR_PHA_R(void);
extern void AD9910_RAM_RAMP_UP_ONE_PHA_R(void);
extern void AD9910_RAM_RAMP_UP_TWO_PHA_R(void);
extern void AD9910_RAM_BID_RAMP_PHA_R(void);
extern void AD9910_RAM_CON_BID_RAMP_PHA_R(void);
extern void AD9910_RAM_CON_RECIR_PHA_R(void);

void Par_mod(u8 des ,u16 FF);
void AD9910_Init_Sin(int gain);
void Freq_convert(u32 Freq);
#endif
