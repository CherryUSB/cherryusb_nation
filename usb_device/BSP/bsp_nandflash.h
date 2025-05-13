#ifndef __BSP_NANDFLASH_H
#define __BSP_NANDFLASH_H

void  NandFlash_Read(uint8_t *buff, uint32_t sector);
void  NandFlash_ReadPages(uint8_t *buff, uint32_t sector, uint32_t count);

void  NandFlash_Write(const uint8_t *buff, uint32_t sector);
void  NandFlash_WritePages(const uint8_t *buff, uint32_t sector, uint32_t count);

void  NandFlash_ReadPages_4k(uint8_t *buff, uint32_t sector, uint32_t count);
void  NandFlash_WritePages_4k(const uint8_t *buff, uint32_t sector, uint32_t count);

void NandFlash_EraseBlock(uint32_t sector);

#endif

