#ifndef _KEY_H
#define _KEY_H

#include "stdint.h"


void delay_ms(uint16_t ms);
void delay_us(uint16_t us);
void delay_ns(uint8_t ns);
// void delay_ns(uint16_t ns);
void key_pro(void);

uint8_t key1_get(void);
uint8_t key2_get(void);

#endif
