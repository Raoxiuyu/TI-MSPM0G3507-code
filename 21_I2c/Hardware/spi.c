#include "Hardware/spi.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"
#include <machine/_stdint.h>

bool cs_flag=0;
int8_t count=0;
uint8_t spi_data;

void spi_init(void)
{
    NVIC_EnableIRQ(GPIO_SPI_GPIOB_INT_IRQN);
    NVIC_EnableIRQ(GPIO_SPI_GPIOA_INT_IRQN);
}

void GROUP1_IRQHandler(void)
{
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
    {
        case GPIO_SPI_PIN_CS_IIDX:
            count=7;
            cs_flag=1;
        break;
    }

    if(cs_flag==1)
    {
        switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
        {
            case GPIO_SPI_PIN_CK_IIDX:
                spi_data += DL_GPIO_readPins(GPIO_SPI_PIN_DA_PORT,GPIO_SPI_PIN_DA_PIN)<<count;
                count--;
                if(count<0)
                {
                    cs_flag=0;
                }
                break;
        }

    }
}