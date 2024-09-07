#ifndef _UART_H
#define _UART_H
#include <ti/driverlib/dl_uart_extend.h>
#include <ti/driverlib/dl_uart_main.h>
#include "stdint.h"


extern uint16_t rx_data[200];
extern bool rx_flag;
void uart_init(void);
void uart_pro(void);

#endif
