#ifndef SPI_DRV_H
#define SPI_DRV_H
#include "mc9s12xep100.h"

#define SPI0_BASE (0x00D8)
#define SPI1_BASE (0x00F0)
#define SPI2_BASE (0x00F8)

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef struct spi_pt SPI_PT;

typedef struct spi_pt
{
    uint8_t CR1;
    uint8_t CR2;
    uint8_t BR;
    uint8_t SR;
    uint8_t DRH;
    uint8_t DRL;
    uint8_t RSVD1;
    uint8_t RSVD2;
};

enum
{
    SPI_PORT_0,
    SPI_PORT_1,
    SPI_PORT_2,
    SPI_PORT_NUM
};

void SPI_Init(SPI_PT *port, SPI_PT *pConf);
void SPI_SendByte(SPI_PT *port, uint8_t data);
void SPI_SendData(SPI_PT *port, uint8_t *data, uint16_t len);
uint8_t SPI_RecvByte(SPI_PT *port);
void SPI_RecvData(SPI_PT *port, uint8_t *data, uint16_t len);

#endif /* SPI_DRV_H */
