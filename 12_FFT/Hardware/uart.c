#include "Hardware/uart.h"
#include <ti/driverlib/dl_uart_extend.h>
#include <ti/driverlib/dl_uart_main.h>

#include "Hardware/led.h"
#include "string.h"
#include "stdio.h"


uint16_t rx_data[200];
uint16_t rx_cent=0;
bool rx_flag=0;


void uart_init(void)
{
	NVIC_ClearPendingIRQ(UART0_INT_IRQn);   //清除
	NVIC_EnableIRQ(UART0_INT_IRQn);
}

void UART0_IRQHandler()
{
	switch (DL_UART_Main_getPendingInterrupt(UART0))
	{
		case DL_UART_MAIN_IIDX_RX:
			rx_flag=1;
			LED2_blue_ON();
			rx_data[rx_cent++]=DL_UART_Main_receiveData(UART0);
			printf("666");
			break;
		default:
			break;
	}
}

void uart_pro(void)
{
	DL_UART_transmitData(UART0,rx_data[0]);
	rx_flag=0;
	memset(rx_data,0,200);
	rx_cent=0;
}

int fputc(int ch, FILE *f)
{
	DL_UART_Extend_transmitDataBlocking(UART0,ch);
	return ch;
}

