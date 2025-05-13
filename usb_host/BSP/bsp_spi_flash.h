#ifndef __BSP_SPI_FLASH_H
#define	__BSP_SPI_FLASH_H

#include "main.h"
#include "n32h47x_48x_spi.h"

#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128 	0XEF17

#define sFLASH_ID       W25Q128
/**
 * @brief  SPI Flash支持的命令
 */
#define sFLASH_CMD_WRITE 0x02 /*!< 写入内存指令 */
#define sFLASH_CMD_WRSR  0x01 /*!< 写入状态寄存器指令*/
#define sFLASH_CMD_WREN  0x06 /*!< 允许写入指令 */
#define sFLASH_CMD_READ  0x03 /*!< 从内存中读取指令*/
#define sFLASH_CMD_RDSR  0x05 /*!< 读取状态注册指令 */
#define sFLASH_CMD_RDID  0x9F /*!< 读识别ID */
#define sFLASH_CMD_SE    0x20 /*!< 部分擦除指令 */
#define sFLASH_CMD_BE    0x52 /*!< 块擦除指令 (32k)*/
#define sFLASH_CMD_CE    0xC7 /*!< 芯片擦除指令 */
//#define sFLASH_CMD_BE    0xD8 /*!< 块擦除指令 (64k)*/

#define sFLASH_WIP_FLAG 0x01 /*!< Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE   0xFF
#define sFLASH_SPI_PAGESIZE 4096
#define sFLASH_SPI_ONE_PAGE 256
#define FLASH_SECTOR_SIZE 	512			//是指一个扇区块的大小 512个字节
#define FLASH_BLOCK_SIZE  	8		    //一个扇区分成了8块，也就是4K的大小
//这一段的内容是指有多少个扇区块 1M含有1024*1024/512个扇区		 			    
#define	FLASH_SECTOR_COUNT	(2048*14) //可以划分为2部分，前14M作为用户，后面2M存储字库


#define sFLASH_W25Q128_ID       0x00EF4018
#define sFLASH_W25Q128_ID_DTR   0x00EF7018

#define sFLASH_M25P64_ID  0x202017

#define sFLASH_SPI_DMA            DMA1
#define sFLASH_SPI_DMA_CLK        RCC_AHB_PERIPHEN_DMA1
#define sFLASH_SPI_Rx_DMA_Channel DMA1_CH2
#define sFLASH_SPI_Rx_DMA_FLAG    DMA_FLAG_TC2
#define sFLASH_SPI_Tx_DMA_Channel DMA1_CH3
#define sFLASH_SPI_Tx_DMA_FLAG    DMA_FLAG_TC3

#define sFLASH_SPI                SPI1
#define sFLASH_SPI_CLK            RCC_APB2_PERIPH_SPI1
#define sFLASH_SPI_SCK_PIN        GPIO_PIN_5 /* PA.05 */
#define sFLASH_SPI_SCK_GPIO_PORT  GPIOA      /* GPIOA */
#define sFLASH_SPI_SCK_GPIO_CLK   RCC_AHB_PERIPHEN_GPIOA
#define sFLASH_SPI_SCK_GPIO_AF    GPIO_AF1
#define sFLASH_SPI_MISO_PIN       GPIO_PIN_6 /* PA.06 */
#define sFLASH_SPI_MISO_GPIO_PORT GPIOA      /* GPIOA */
#define sFLASH_SPI_MISO_GPIO_CLK  RCC_AHB_PERIPHEN_GPIOA
#define sFLASH_SPI_MISO_GPIO_AF   GPIO_AF1
#define sFLASH_SPI_MOSI_PIN       GPIO_PIN_7 /* PA.07 */
#define sFLASH_SPI_MOSI_GPIO_PORT GPIOA      /* GPIOA */
#define sFLASH_SPI_MOSI_GPIO_CLK  RCC_AHB_PERIPHEN_GPIOA
#define sFLASH_SPI_MOSI_GPIO_AF   GPIO_AF1
#define sFLASH_CS_PIN             GPIO_PIN_4 /* PA.04 */
#define sFLASH_CS_GPIO_PORT       GPIOA      /* GPIOA */
#define sFLASH_CS_GPIO_CLK        RCC_AHB_PERIPHEN_GPIOA
#define sFLASH_CS_GPIO_AF         GPIO_AF1

#define sFLASH_SPI_Rx_DMA_Remap		DMA_REMAP_SPI1_RX
#define sFLASH_SPI_Tx_DMA_Remap		DMA_REMAP_SPI1_TX

/** Select sFLASH: Chip Select pin low **/
#define sFLASH_CS_LOW() GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
/** Deselect sFLASH: Chip Select pin high **/
#define sFLASH_CS_HIGH() GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)


void sFLASH_Init(void);
void sFLASH_DeInit(void);
void sFLASH_EraseSector(uint32_t SectorAddr);
void sFLASH_EraseChip(void);
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFlash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void sFlash_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void sFLASH_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t sFLASH_ReadID(void);
uint16_t SPI_Flash_ReadID(void);
uint8_t sFLASH_ReadByte(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);


#endif /* __SPI_FLASH_H */


