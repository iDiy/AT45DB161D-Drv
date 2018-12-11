#include "AT45DB161D.h"

#define AT45_TEST (1)

#if (AT45_TEST)
static uint8_t at45_status_reg = 0;
static uint8_t test_buf1[AT_PAGE_SIZE] = {0};
static uint8_t test_buf2[AT_PAGE_SIZE] = {0};
static uint8_t test_buf3[AT_PAGE_SIZE] = {0};
#endif

static SPI_PT * const port = (SPI_PT*)SPI1_BASE;

static SPI_PT const SPI_PortConfig = {
    0x50,
    0x00,
    0x00,
    0,
    0,
    0
};

void AT45_init(void)
{
    /* buzzer */
    DDRK_DDRK1 = 1;
    PORTK_PK1 = 0;

    /* CS */
    DDRP_DDRP3 = 1;
    PTP_PTP3 = 1;

    /* /WP */
    DDRP_DDRP4 = 1;
    PTP_PTP4 = 1;

    /* /RESET */
    DDRP_DDRP5 = 1;
    PTP_PTP5 = 1;

    SPI_Init(port, (SPI_PT*const)&SPI_PortConfig);
}

void AT45_Writebyte(uint8_t data)
{
    SPI_SendByte(port, data);
    (void)SPI_RecvByte(port);
}
uint8_t AT45_ReadByte(void)
{
    SPI_SendByte(port, 0xFF);
    return SPI_RecvByte(port);
}

uint8_t AT45_ReadStatus(void)
{
    AT_CS_ASSERT
    AT45_Writebyte(AT_STATUS_REG_READ);
    at45_status_reg = AT45_ReadByte();
    AT_CS_DEASSERT
    return (at45_status_reg);
}

uint8_t AT45_IsBusy(void)
{
    return ((AT45_ReadStatus() & 0x80) == 0);
}

void AT45_ReadFlash(uint16_t page, uint16_t offset, uint16_t sizes, uint8_t *buf)
{
    uint32_t addr = (((uint32_t)page) << 10) + offset;

    while (AT45_IsBusy());

    AT_CS_ASSERT
    AT45_Writebyte(AT_CONTINUE_ARRAY_READ);
    AT45_Writebyte((uint8_t)(addr >> 16));
    AT45_Writebyte((uint8_t)(addr >> 8));
    AT45_Writebyte((uint8_t)(addr >> 0));
    AT45_Writebyte(0);

    while (sizes)
    {
        *buf = AT45_ReadByte();
        buf += 1;
        sizes -= 1;
    }
    AT_CS_DEASSERT
}
void AT45_ReadBuffer1(uint16_t offset, uint16_t sizes, uint8_t *buf)
{
    while (AT45_IsBusy());

    AT_CS_ASSERT
    AT45_Writebyte(AT_BUFFER1_READ);
    AT45_Writebyte(0);
    AT45_Writebyte((uint8_t)(offset >> 8));
    AT45_Writebyte((uint8_t)(offset >> 0));
    AT45_Writebyte(0);

    while (sizes)
    {
        *buf = AT45_ReadByte();
        buf += 1;
        sizes -= 1;
    }
    AT_CS_DEASSERT
}
void AT45_WriteBuffer1(uint16_t offset, uint16_t sizes, uint8_t *buf)
{
    while (AT45_IsBusy());

    AT_CS_ASSERT
    AT45_Writebyte(AT_BUFFER1_WRITE);
    AT45_Writebyte(0);
    AT45_Writebyte((uint8_t)(offset >> 8));
    AT45_Writebyte((uint8_t)(offset >> 0));

    while (sizes)
    {
        AT45_Writebyte(*buf);
        buf += 1;
        sizes -= 1;
    }
    AT_CS_DEASSERT
}
void AT45_Buffer1ToPage(uint16_t page)
{
    while (AT45_IsBusy());

    AT_CS_ASSERT
    AT45_Writebyte(AT_BUFFER1_TO_PAGE_WITH_ERASE);
    AT45_Writebyte((uint8_t)(page >> 6));
    AT45_Writebyte((uint8_t)(page << 2));
    AT45_Writebyte(0);
    AT_CS_DEASSERT
}
void AT45_PageToBuffer1(uint16_t page)
{
    while (AT45_IsBusy());

    AT_CS_ASSERT
    AT45_Writebyte(AT_PAGE_TO_BUFFER1_TRANSFER);
    AT45_Writebyte((uint8_t)(page >> 6));
    AT45_Writebyte((uint8_t)(page << 2));
    AT45_Writebyte(0);
    AT_CS_DEASSERT
}

void AT45_Test(void)
{
    #if (AT45_TEST)
    int i;
    while (AT45_IsBusy());
    for (i = 0; i < AT_PAGE_SIZE; i++)
    {
        test_buf1[i] = (uint8_t)i;
    }
    AT45_WriteBuffer1(0, AT_PAGE_SIZE, test_buf1);
    AT45_Buffer1ToPage(0);
    AT45_PageToBuffer1(0);
    AT45_ReadBuffer1(0, AT_PAGE_SIZE, test_buf2);
    AT45_ReadFlash(0, 0, AT_PAGE_SIZE, test_buf3);
    #endif
}
