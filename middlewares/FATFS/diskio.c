/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "bsp_spi_flash.h"
#include "log.h"
/* Definitions of physical drive number for each drive */
#define DEV_FLASH		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		  1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		  2	/* Example: Map USB MSD to physical drive 2 */

int USB_disk_status(void);
int USB_disk_initialize(void);
int USB_disk_read(BYTE *buff, LBA_t sector, UINT count);
int USB_disk_write(const BYTE *buff, LBA_t sector, UINT count);
int USB_disk_ioctl(BYTE cmd, void *buff);
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	switch (pdrv) {
	case DEV_FLASH :
		/* SPI Flash状态检测：读取SPI Flash 设备ID */
			if (sFLASH_ID == SPI_Flash_ReadID()) {
					/* 设备ID读取结果正确 */
					stat &= ~STA_NOINIT;
			} else {
					/* 设备ID读取结果错误 */
					stat = STA_NOINIT;;
			}
		return stat;

	case DEV_MMC :
		
		// translate the reslut code here

		return stat;

	case DEV_USB :
		 
		stat = USB_disk_status();

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	switch (pdrv) {
	case DEV_FLASH :
		/* 初始化SPI Flash */
		sFLASH_Init();
		/* 获取SPI Flash芯片状态 */
		 stat=disk_status(DEV_FLASH);
		return stat;

	case DEV_MMC :
		

		// translate the reslut code here

		return stat;

	case DEV_USB :
		  stat = USB_disk_initialize();
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_OK;
	
	switch (pdrv) {
	case DEV_FLASH :
			for(;count>0;count--)
			{
				sFLASH_Read(buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
				sector++;
				buff+=FLASH_SECTOR_SIZE;
			}
		return res;

	case DEV_MMC :
		// translate the arguments here

		return res;

	case DEV_USB :
      res = USB_disk_read(buff, sector, count);
		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_OK;

	switch (pdrv) {
	case DEV_FLASH :
		for(;count>0;count--)
		{	
			sFlash_Write((uint8_t*)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
			sector++;
			buff+=FLASH_SECTOR_SIZE;
		}
		return res;

	case DEV_MMC :
		// translate the arguments here


		return res;

	case DEV_USB :
       res = USB_disk_write(buff, sector, count);
		return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	switch (pdrv) {
	case DEV_FLASH :

		switch (cmd) {
				//返回扇区个数
        case GET_SECTOR_COUNT:
            *(DWORD * )buff = FLASH_SECTOR_COUNT;
            break;
        /* 扇区大小  */
        case GET_SECTOR_SIZE :
            *(WORD * )buff = FLASH_SECTOR_SIZE;
            break;
        /* 同时擦除扇区个数 */
        case GET_BLOCK_SIZE :
            *(DWORD * )buff = FLASH_BLOCK_SIZE;
            break;
				default:
					break;
        }
				//log_info("##%s %d %s :%d\r\n",__FILE__,__LINE__,__FUNCTION__ ,cmd);
        res = RES_OK;
		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive
      res = USB_disk_ioctl(cmd,buff);
		return res;
	}

	return RES_PARERR;
}


__weak DWORD get_fattime(void) {
    /* Return current timestamp */
    return    ((DWORD)(2025 - 1980) << 25)  /* Year  */
            | ((DWORD)3  << 21)             /* Month */
            | ((DWORD)12 << 16)             /* Mday  */
            | ((DWORD)16 << 11)             /* Hour  */
            | ((DWORD)30 << 5)              /* Min   */
            | ((DWORD)0  << 0);             /* Sec   */
}
