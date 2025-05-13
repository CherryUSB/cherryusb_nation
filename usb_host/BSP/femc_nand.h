/**
*     Copyright (c) 2023, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file femc_nand.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __FEMC_NAND_H__
#define __FEMC_NAND_H__

#include "n32h47x_48x.h"

#define BANK2_NAND_ADDR     ((uint32_t)0x70000000)
#define BANK3_NAND_ADDR     ((uint32_t)0x80000000)

typedef struct
{
    uint8_t Maker_ID;
    uint8_t Device_ID;
    uint8_t Third_ID;
    uint8_t Fourth_ID;
} NAND_IDModule;

typedef struct
{
    uint16_t Zone;
    uint16_t Block;
    uint16_t Page;
} NAND_ADDRESS;

/* NAND Area definition*/
#define CMD_AREA  (uint32_t)(1 << 16) /* A16 = CLE  high */
#define ADDR_AREA (uint32_t)(1 << 17) /* A17 = ALE high */

#define DATA_AREA ((uint32_t)0x00000000)

/* FEMC NAND memory command */
#define NAND_CMD_AREA_A      ((uint8_t)0x00)
#define NAND_CMD_AREA_B      ((uint8_t)0x01)
#define NAND_CMD_AREA_C      ((uint8_t)0x50)
#define NAND_CMD_AREA_TRUE1  ((uint8_t)0x30)

#define NAND_CMD_WRITE0      ((uint8_t)0x80)
#define NAND_CMD_WRITE_TRUE1 ((uint8_t)0x10)

#define NAND_CMD_ERASE0      ((uint8_t)0x60)
#define NAND_CMD_ERASE1      ((uint8_t)0xD0)

#define NAND_CMD_READID      ((uint8_t)0x90)
#define NAND_CMD_STATUS      ((uint8_t)0x70)
#define NAND_CMD_LOCK_STATUS ((uint8_t)0x7A)
#define NAND_CMD_RESET       ((uint8_t)0xFF)

/* NAND memory status */
#define NAND_VALID_ADDRESS   ((uint32_t)0x00000100)
#define NAND_INVALID_ADDRESS ((uint32_t)0x00000200)
#define NAND_TIMEOUT_ERROR   ((uint32_t)0x00000400)
#define NAND_BUSY            ((uint32_t)0x00000000)
#define NAND_ERROR           ((uint32_t)0x00000001)
#define NAND_READY           ((uint32_t)0x00000040)

/* FEMC NAND memory parameters */
#define NAND_PAGE_SIZE       ((uint16_t)0x0800) /* 2 * 1024 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE      ((uint16_t)0x0040) /* 64 page 128 * 1024 bytes pages per block */
#define NAND_ZONE_SIZE       ((uint16_t)0x0400) /* 1024 Block per zone */
#define NAND_SPARE_AREA_SIZE ((uint16_t)0x0040) /* last 64 bytes as spare area */
#define NAND_MAX_ZONE        ((uint16_t)0x0001) /* 1 zones of 1024 block */


/* FEMC NAND memory address computation */
#define ADDR_1st_CYCLE(ADDR) (uint8_t)((ADDR)&0xFF)               /* 1st addressing cycle */
#define ADDR_2nd_CYCLE(ADDR) (uint8_t)(((ADDR)&0xFF00) >> 8)      /* 2nd addressing cycle */
#define ADDR_3rd_CYCLE(ADDR) (uint8_t)(((ADDR)&0xFF0000) >> 16)   /* 3rd addressing cycle */
#define ADDR_4th_CYCLE(ADDR) (uint8_t)(((ADDR)&0xFF000000) >> 24) /* 4th addressing cycle */

/* FEMC NAND memory column computation */
#define COLUMN_1ST_CYCLE(ADDR)  (uint8_t)((ADDR)&0xFF)            /* 1st Column addressing cycle */
#define COLUMN_2ND_CYCLE(ADDR)  (uint8_t)(((ADDR)&0xFF00) >> 8)   /* 2nd Column addressing cycle */


/* DATA pin */
#define FEMC_D0_CLK                RCC_AHB_PERIPHEN_GPIOD   
#define FEMC_D0_PORT               GPIOD
#define FEMC_D0_PIN                GPIO_PIN_14
#define FEMC_D0_AF                 GPIO_AF10

#define FEMC_D1_CLK                RCC_AHB_PERIPHEN_GPIOD
#define FEMC_D1_PORT               GPIOD
#define FEMC_D1_PIN                GPIO_PIN_15
#define FEMC_D1_AF                 GPIO_AF10

#define FEMC_D2_CLK                RCC_AHB_PERIPHEN_GPIOD   
#define FEMC_D2_PORT               GPIOD
#define FEMC_D2_PIN                GPIO_PIN_0
#define FEMC_D2_AF                 GPIO_AF10

#define FEMC_D3_CLK                RCC_AHB_PERIPHEN_GPIOD  
#define FEMC_D3_PORT               GPIOD
#define FEMC_D3_PIN                GPIO_PIN_1
#define FEMC_D3_AF                 GPIO_AF10

#define FEMC_D4_CLK                RCC_AHB_PERIPHEN_GPIOE   
#define FEMC_D4_PORT               GPIOE
#define FEMC_D4_PIN                GPIO_PIN_7
#define FEMC_D4_AF                 GPIO_AF10

#define FEMC_D5_CLK                RCC_AHB_PERIPHEN_GPIOE   
#define FEMC_D5_PORT               GPIOE
#define FEMC_D5_PIN                GPIO_PIN_8
#define FEMC_D5_AF                 GPIO_AF10

#define FEMC_D6_CLK                RCC_AHB_PERIPHEN_GPIOE   
#define FEMC_D6_PORT               GPIOE
#define FEMC_D6_PIN                GPIO_PIN_9
#define FEMC_D6_AF                 GPIO_AF10

#define FEMC_D7_CLK                RCC_AHB_PERIPHEN_GPIOE  
#define FEMC_D7_PORT               GPIOE
#define FEMC_D7_PIN                GPIO_PIN_10
#define FEMC_D7_AF                 GPIO_AF10

/* NOE pin */
#define FEMC_NOE_CLK               RCC_AHB_PERIPHEN_GPIOD
#define FEMC_NOE_PORT              GPIOD
#define FEMC_NOE_PIN               GPIO_PIN_4
#define FEMC_NOE_AF                GPIO_AF10

/* NWE pin */
#define FEMC_NWE_CLK               RCC_AHB_PERIPHEN_GPIOD
#define FEMC_NWE_PORT              GPIOD
#define FEMC_NWE_PIN               GPIO_PIN_5
#define FEMC_NWE_AF                GPIO_AF10

/* CLE pin */
#define FEMC_CLE_CLK               RCC_AHB_PERIPHEN_GPIOD
#define FEMC_CLE_PORT              GPIOD
#define FEMC_CLE_PIN               GPIO_PIN_11
#define FEMC_CLE_AF                GPIO_AF11

/* ALE pin */
#define FEMC_ALE_CLK               RCC_AHB_PERIPHEN_GPIOD
#define FEMC_ALE_PORT              GPIOD
#define FEMC_ALE_PIN               GPIO_PIN_12
#define FEMC_ALE_AF                GPIO_AF11

/* NCE pin */
#define FEMC_NCE_CLK               RCC_AHB_PERIPHEN_GPIOG
#define FEMC_NCE_PORT              GPIOG
#define FEMC_NCE_PIN               GPIO_PIN_9               // NCE3
#define FEMC_NCE_AF                GPIO_AF11

/* NWAIT pin */
#define FEMC_NWAIT_CLK             RCC_AHB_PERIPHEN_GPIOD
#define FEMC_NWAIT_PORT            GPIOD
#define FEMC_NWAIT_PIN             GPIO_PIN_6
#define FEMC_NWAIT_AF              GPIO_AF10


void FEMC_Nand_Init(uint8_t bank_index, uint8_t bus_width);
void FEMC_Nand_ReadID(uint32_t Bank_NAND_Addr, NAND_IDModule* nand_id);
uint32_t FEMC_Nand_WritePage_Byte(uint32_t Bank_NAND_Addr, uint8_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite);
uint32_t FEMC_Nand_ReadPage_Byte(uint32_t Bank_NAND_Addr, uint8_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead);
uint32_t FEMC_Nand_WritePage_HalfWorld(uint32_t Bank_NAND_Addr, uint16_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite);
uint32_t FEMC_Nand_ReadPage_HalfWorld(uint32_t Bank_NAND_Addr, uint16_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead);
uint32_t FEMC_NAND_ReadSpareArea_Byte(uint32_t Bank_NAND_Addr, uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead);
uint32_t FEMC_NAND_ReadSpareArea_HalfWord(uint32_t Bank_NAND_Addr, uint16_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead);
uint32_t FEMC_NAND_WriteSpareArea_Byte(uint32_t Bank_NAND_Addr, uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite);
uint32_t FEMC_NAND_WriteSpareArea_HalfWord(uint32_t Bank_NAND_Addr, uint16_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite);

uint32_t FEMC_Nand_Erase_Block(uint32_t Bank_NAND_Addr, NAND_ADDRESS Address);
uint32_t FEMC_Nand_Reset(uint32_t Bank_NAND_Addr);
uint32_t FEMC_Nand_GetStatus(uint32_t Bank_NAND_Addr);
uint32_t FEMC_Nand_ReadStatus(uint32_t Bank_NAND_Addr);
uint32_t FEMC_Nand_AddressIncrement(NAND_ADDRESS* Address);

#endif /* __FEMC_NAND_H__ */
