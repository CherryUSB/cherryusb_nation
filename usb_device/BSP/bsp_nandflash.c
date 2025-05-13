#include "femc_nand.h"
#include "string.h"
#include "bsp_nandflash.h"

#define MIN(a,b) ((a)>(b)?(b):(a))
#define BLN_SIZE  (4096)
#define PAGE_SIZE (2048)
#define BLOCK_NUM (64)

#define TMP_BLOCK_SIZE  (PAGE_SIZE*BLOCK_NUM)
static uint8_t block_Buff[TMP_BLOCK_SIZE];


uint32_t NandFlash_CheckSpare(uint32_t sector)
{
	uint8_t *page_buff = block_Buff;
	
	NandFlash_Read(page_buff, sector);

	for(int i=0; i<2048; i++)
	{
		if(page_buff[i] != 0xFF)
		{
			return 0;
		}
	}

	return 1;
}

void  NandFlash_Read(uint8_t *buff, uint32_t sector)
{
    HAL_StatusTypeDef flag;
    NAND_AddressTypeDef tmp_addr = {0};
    tmp_addr.Page = sector % hnand1.Config.BlockSize;
    tmp_addr.Block = sector / hnand1.Config.BlockSize % hnand1.Config.BlockNbr;
    tmp_addr.Plane = sector / hnand1.Config.PlaneSize;
    flag = HAL_NAND_Read_Page_8b(&hnand1, &tmp_addr, buff, 1);

}

void  NandFlash_ReadPages(uint8_t *buff, uint32_t sector, uint32_t count)
{
    for(int i=0; i<count; i++)
    {
      NandFlash_Read(buff,sector);
      buff += PAGE_SIZE;
      sector++;
    }
}

void  NandFlash_Read_4k(uint8_t *buff, uint32_t sector)
{
  NandFlash_Read(buff, sector*2);
  NandFlash_Read(buff+PAGE_SIZE, sector*2+1);

}

void  NandFlash_ReadPages_4k(uint8_t *buff, uint32_t sector, uint32_t count)
{
    for(int i=0; i<count; i++)
    {
      NandFlash_Read_4k(buff,sector);
      buff += BLN_SIZE;
      sector++;
    }
}


void  NandFlash_ReadBlock(uint8_t *buff, uint32_t sector)
{
    NAND_AddressTypeDef tmp_addr = {0};
    tmp_addr.Page = 0;
    tmp_addr.Block = sector / hnand1.Config.BlockSize % hnand1.Config.BlockNbr;
    tmp_addr.Plane = sector / hnand1.Config.PlaneSize;
    HAL_NAND_Read_Page_8b(&hnand1, &tmp_addr, buff, BLOCK_NUM);
} 

void  NandFlash_WriteNoCheck(const uint8_t *buff, uint32_t sector)
{
    NAND_AddressTypeDef tmp_addr = {0};
        
    tmp_addr.Page = sector % hnand1.Config.BlockSize;
    tmp_addr.Block = sector / hnand1.Config.BlockSize % hnand1.Config.BlockNbr;
    tmp_addr.Plane = sector / hnand1.Config.PlaneSize;
    HAL_NAND_Write_Page_8b(&hnand1, &tmp_addr, buff, 1);
}

void NandFlash_WriteBlock(const uint8_t *buff, uint32_t sector)
{
    NAND_AddressTypeDef tmp_addr = {0};
        
    tmp_addr.Page = 0;
    tmp_addr.Block = sector / hnand1.Config.BlockSize % hnand1.Config.BlockNbr;
    tmp_addr.Plane = sector / hnand1.Config.PlaneSize;
    
    HAL_NAND_Erase_Block(&hnand1, &tmp_addr);
    HAL_NAND_Write_Page_8b(&hnand1, &tmp_addr, buff, BLOCK_NUM);
}

void NandFlash_EraseBlock(uint32_t sector)
{
    NAND_AddressTypeDef tmp_addr = {0};
        
    tmp_addr.Page = 0;
    tmp_addr.Block = sector / hnand1.Config.BlockSize % hnand1.Config.BlockNbr;
    tmp_addr.Plane = sector / hnand1.Config.PlaneSize;
    
    HAL_NAND_Erase_Block(&hnand1, &tmp_addr);
}

void  NandFlash_Write(const uint8_t *buff, uint32_t sector)
{
    HAL_StatusTypeDef flag;
    uint32_t buff_addr;
    NAND_AddressTypeDef tmp_addr = {0};

    if(NandFlash_CheckSpare(sector))
    {
      NandFlash_WriteNoCheck(buff, sector);
      return ;
    }

    NandFlash_ReadBlock(block_Buff, sector);

    tmp_addr.Page = sector % hnand1.Config.BlockSize;
    tmp_addr.Block = sector / hnand1.Config.BlockSize % hnand1.Config.BlockNbr;
    tmp_addr.Plane = sector / hnand1.Config.PlaneSize;
    buff_addr = tmp_addr.Page * PAGE_SIZE;
    memcpy(&block_Buff[buff_addr], buff, PAGE_SIZE);
            
    tmp_addr.Page = 0;
    HAL_NAND_Erase_Block(&hnand1, &tmp_addr);
    HAL_NAND_Write_Page_8b(&hnand1, &tmp_addr, block_Buff, BLOCK_NUM);
}

void  NandFlash_WritePages(const uint8_t *buff, uint32_t sector, uint32_t count)
{
  for(int i=0; i<count; i++)
  {
    NandFlash_Write(buff,sector);
    buff += PAGE_SIZE;
    sector++;
  }
}

void  NandFlash_Write_4k(const uint8_t *buff, uint32_t sector)
{
  NandFlash_Write(buff, sector*2);
  NandFlash_Write(buff+PAGE_SIZE, sector*2+1);
}

void  NandFlash_WritePages_4k(const uint8_t *buff, uint32_t sector, uint32_t count)
{
  for(int i=0; i<count; i++)
  {
    NandFlash_Write_4k(buff,sector);
    buff += BLN_SIZE;
    sector++;
  }
}

















