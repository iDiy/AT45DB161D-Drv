#ifndef AT45DB161D_H
#define AT45DB161D_H
#include "SPI_Drv.h"

#define AT_PAGE_SIZE (528)

#define AT_CS_ASSERT {PTP_PTP3 = 0;}
#define AT_CS_DEASSERT {PTP_PTP3 = 1;}

#define AT_STATUS_REG_READ (0xD7)
#define AT_CONTINUE_ARRAY_READ (0x0B)
#define AT_BUFFER1_READ (0xD4)
#define AT_BUFFER1_WRITE (0x84)
#define AT_BUFFER1_TO_PAGE_WITH_ERASE (0x83)
#define AT_PAGE_TO_BUFFER1_TRANSFER (0x53)

void AT45_init(void);
uint8_t AT45_IsBusy(void);
void AT45_ReadFlash(uint16_t page, uint16_t offset, uint16_t sizes, uint8_t *out);
void AT45_ReadBuffer1(uint16_t offset, uint16_t sizes, uint8_t *buf);

#endif /* AT45DB161D_H */
