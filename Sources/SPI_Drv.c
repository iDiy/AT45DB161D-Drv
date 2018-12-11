#include "SPI_Drv.h"

void SPI_Init(SPI_PT *port, SPI_PT *pConf)
{
    port->CR1 = pConf->CR1;
    port->CR2 = pConf->CR2;
    port->BR = pConf->BR;
}

void SPI_SendByte(SPI_PT *port, uint8_t data)
{
    while (!(port->SR & (0x01<<5)));
    port->DRL = data;
}

void SPI_SendData(SPI_PT *port, uint8_t *data, uint16_t len)
{
    uint16_t i;

    for (i = 0; i < len; i++)
    {
        while (!(port->SR & (0x01<<5)));
        port->DRL = data[i];
    }
}

uint8_t SPI_RecvByte(SPI_PT *port)
{
    while (!(port->SR & (0x01<<7)));
    return port->DRL;
}

void SPI_RecvData(SPI_PT *port, uint8_t *data, uint16_t len)
{
    uint16_t i;

    for (i = 0; i < len; i++)
    {
        while (!(port->SR & (0x01<<7)));
        data[i] = port->DRL;
    }
}
