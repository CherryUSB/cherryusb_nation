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
*\*\file femc_nand.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "femc_nand.h"
#include "n32h47x_48x_femc.h"
#include "n32h47x_48x_gpio.h"
#include "n32h47x_48x_rcc.h"
#include "log.h"



#define ROW_ADDRESS (Address.Page + (Address.Block + (Address.Zone * NAND_ZONE_SIZE)) * NAND_BLOCK_SIZE)

#define COLUMN_ADDRESS (NAND_PAGE_SIZE)

/**
*\*\name    FEMC_GPIO_Init.
*\*\fun     FEMC gpio initialized.
*\*\param   bank_index:
*\*\            - 2     bank 2
*\*\            - 3     bank 3
*\*\return  none 
**/
void FEMC_GPIO_Init(uint8_t bank_index)
{
    GPIO_InitType GPIO_InitStructure;
    
    RCC_EnableAHB1PeriphClk(FEMC_NOE_CLK | FEMC_NWE_CLK | FEMC_CLE_CLK   |\
                            FEMC_ALE_CLK | FEMC_NCE_CLK | FEMC_NWAIT_CLK |\
                            FEMC_D0_CLK  | FEMC_D1_CLK  | FEMC_D2_CLK    |\
                            FEMC_D3_CLK  | FEMC_D4_CLK  | FEMC_D5_CLK    |\
                            FEMC_D6_CLK  | FEMC_D7_CLK , ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    
    /*-- GPIO Configuration ------------------------------------------------------*/
    /*  DATA pin configuration  */
    GPIO_InitStructure.Pin            = FEMC_D0_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D0_AF;
    GPIO_InitPeripheral(FEMC_D0_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = FEMC_D1_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D1_AF;
    GPIO_InitPeripheral(FEMC_D1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = FEMC_D2_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D2_AF;
    GPIO_InitPeripheral(FEMC_D2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = FEMC_D3_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D3_AF;
    GPIO_InitPeripheral(FEMC_D3_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = FEMC_D4_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D4_AF;
    GPIO_InitPeripheral(FEMC_D4_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = FEMC_D5_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D5_AF;
    GPIO_InitPeripheral(FEMC_D5_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = FEMC_D6_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D6_AF;
    GPIO_InitPeripheral(FEMC_D6_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = FEMC_D7_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_D7_AF;
    GPIO_InitPeripheral(FEMC_D7_PORT, &GPIO_InitStructure);
        
    /* NOE pin configuration */
    GPIO_InitStructure.Pin = FEMC_NOE_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_NOE_AF;
    GPIO_InitPeripheral(FEMC_NOE_PORT, &GPIO_InitStructure);
    
    /* NWE pin configuration */
    GPIO_InitStructure.Pin = FEMC_NWE_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_NWE_AF;
    GPIO_InitPeripheral(FEMC_NWE_PORT, &GPIO_InitStructure);
    
    /* CLE pin configuration  */
    GPIO_InitStructure.Pin = FEMC_CLE_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_CLE_AF;
    GPIO_InitPeripheral(FEMC_CLE_PORT, &GPIO_InitStructure);
    
    /* ALE pin configuration  */
    GPIO_InitStructure.Pin = FEMC_ALE_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_ALE_AF;
    GPIO_InitPeripheral(FEMC_ALE_PORT, &GPIO_InitStructure);

    /* NCE pin configuration*/
    GPIO_InitStructure.Pin = FEMC_NCE_PIN;
    GPIO_InitStructure.GPIO_Alternate = FEMC_NCE_AF;
    GPIO_InitPeripheral(FEMC_NCE_PORT, &GPIO_InitStructure);

    /* NWAIT pin configuration */
    GPIO_InitStructure.Pin        = FEMC_NWAIT_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Alternate = FEMC_NWAIT_AF;
    GPIO_InitPeripheral(FEMC_NWAIT_PORT, &GPIO_InitStructure);
}

/**
*\*\name    FEMC_Nand_Init.
*\*\fun     Configures the FEMC and GPIOs to interface with the NAND memory. This function must be called before any write/read operation on the NAND.
*\*\param   bank_index:
*\*\            - 2     bank 2
*\*\            - 3     bank 3
*\*\param   bus_width:
*\*\            - 8     FEMC_NAND_BUS_WIDTH_8B
*\*\            - 16    FEMC_NAND_BUS_WIDTH_16B
*\*\return  none 
**/
void FEMC_Nand_Init(uint8_t bank_index, uint8_t bus_width)
{
    
    FEMC_NandInitType FEMC_NANDInitStructure;
    FEMC_NandTimingInitType p;
    FEMC_NAND_Bank *nand_bank;

    /*-- FEMC Configuration ------------------------------------------------------*/
    /* Enable the FEMC Clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_FEMC, ENABLE);
    
    FEMC_GPIO_Init(bank_index);

    p.SetTime     = FEMC_NAND_SETUP_TIME(0x4);
    p.WaitSetTime = FEMC_NAND_WAIT_TIME(0x6);
    p.HoldSetTime = FEMC_NAND_HOLD_TIME(0x5);
    p.HiZSetTime  = FEMC_NAND_HIZ_TIME(0x5);
    
    if(bank_index == 2)
    {
        nand_bank = FEMC_NAND_BANK2;
    }
    else if(bank_index == 3)
    {
        nand_bank = FEMC_NAND_BANK3;
    }
    
    FEMC_InitNandStruct(&FEMC_NANDInitStructure);
    FEMC_NANDInitStructure.Bank                  = nand_bank;
    FEMC_NANDInitStructure.WaitFeatureEnable     = FEMC_NAND_NWAIT_ENABLE;
    FEMC_NANDInitStructure.MemDataWidth          = bus_width == 8 ? FEMC_NAND_BUS_WIDTH_8B : FEMC_NAND_BUS_WIDTH_16B;
    FEMC_NANDInitStructure.EccEnable             = FEMC_NAND_ECC_DISABLE;
    FEMC_NANDInitStructure.EccPageSize           = FEMC_NAND_ECC_PAGE_2048BYTES;
    FEMC_NANDInitStructure.TCLRSetTime           = FEMC_NAND_CLE_DELAY_1HCLK;
    FEMC_NANDInitStructure.TARSetTime            = FEMC_NAND_ALE_DELAY_1HCLK;
    FEMC_NANDInitStructure.CommSpaceTimingStruct = &p;
    FEMC_NANDInitStructure.AttrSpaceTimingStruct = &p;

    FEMC_InitNand(&FEMC_NANDInitStructure);

    /* FEMC NAND Bank Cmd Test */
    FEMC_EnableNand(nand_bank, ENABLE);
}

/**
*\*\name    Flash_Write_Command.
*\*\fun     NAND Flash write command.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   Cmd: Command to be written
*\*\return  none 
**/
void Flash_Write_Command(uint32_t Bank_NAND_Addr, uint8_t Cmd)
{
    *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA) = Cmd;
}

/**
*\*\name    Flash_Write_DataByte.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\fun     NAND Flash write command.
*\*\param   Data: data to be written
*\*\return  none 
**/
void Flash_Write_DataByte(uint32_t Bank_NAND_Addr, uint8_t Data)
{
    *(__IO uint8_t*)(Bank_NAND_Addr | DATA_AREA) = Data;
}

/**
*\*\name    Flash_Write_Addr.
*\*\fun     NAND Flash write command.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   Addr address to bo written
*\*\return  none 
**/
void Flash_Write_Addr(uint32_t Bank_NAND_Addr, uint8_t Addr)
{
    *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = Addr;
}

/**
*\*\name    Flash_Read_DataByte.
*\*\fun     Flash read a byte data.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\return  Date 
**/
uint8_t Flash_Read_DataByte(uint32_t Bank_NAND_Addr)
{
    uint8_t Data;
    Data = *(__IO uint8_t*)(Bank_NAND_Addr | DATA_AREA);
    return Data;
}

/**
*\*\name    FEMC_Nand_ReadID.
*\*\fun     Reads NAND memory's ID.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   nand_id: pointer to a NAND_IDType structure which will hold the Manufacturer and Device ID.
*\*\return  none 
**/
void FEMC_Nand_ReadID(uint32_t Bank_NAND_Addr, NAND_IDModule* nand_id)
{
    uint32_t data = 0;

    // Send Command to the command area
    Flash_Write_Command(Bank_NAND_Addr, NAND_CMD_READID);
    Flash_Write_Addr(Bank_NAND_Addr, 0x00);

    // Sequence to read ID from NAND flash
    data = *(__IO uint32_t*)(Bank_NAND_Addr | DATA_AREA);

    nand_id->Maker_ID  = ADDR_1st_CYCLE(data); // manufacturer number
    nand_id->Device_ID = ADDR_2nd_CYCLE(data); // device identifier
    nand_id->Third_ID  = ADDR_3rd_CYCLE(data);
    nand_id->Fourth_ID = ADDR_4th_CYCLE(data);
    
    log_info("NAND Manufacturer ID = 0x%x\r\n", nand_id->Maker_ID);
    log_info("NAND Device ID = 0x%x\r\n", nand_id->Device_ID);
    log_info("NAND Third ID = 0x%x\r\n", nand_id->Third_ID);
    log_info("NAND Fourth ID = 0x%x\r\n", nand_id->Fourth_ID);
}

/**
*\*\name    FEMC_Nand_WritePage_Byte.
*\*\fun     This routine is for writing one or more Page size byte data.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer containing data to be written.
*\*\param   Address: First page address.
*\*\param   NumPageToWrite: Number of page to write.
*\*\return  New status of the NAND operation. 
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\            And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address 
**/
uint32_t FEMC_Nand_WritePage_Byte(uint32_t Bank_NAND_Addr, uint8_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite)
{
    uint32_t index = 0x00, numpagewritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;

    if(Bank_NAND_Addr == BANK2_NAND_ADDR)
    {
        if((FEMC_NAND_BANK2->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, ENABLE);
        }
    }
    else if(Bank_NAND_Addr == BANK3_NAND_ADDR)
    {
        if((FEMC_NAND_BANK3->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, ENABLE);
        }
    }
    
    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }
    
    while ((NumPageToWrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /* Page write command */
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_AREA_A;
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_WRITE0;
        
        if(NAND_PAGE_SIZE <= 512)
        {
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }
            else
            {
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }
        }
        else
        {
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
            else                                                                                
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }
        }

        /* Calculate the size */
        size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpagewritten);
        /* Write data */
        for (; index < size; index++)
        {
            *(__IO uint8_t*)(Bank_NAND_Addr | DATA_AREA) = pBuffer[index];
        }

        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE_TRUE1;

        /* Check status for successful operation */
        status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

        if (status == NAND_READY)
        {
            numpagewritten++;

            NumPageToWrite--;

            /* Calculate Next page Address */
            addressstatus = FEMC_Nand_AddressIncrement(&Address);
        }
    }
    return (status | addressstatus);
}

/**
*\*\name    FEMC_Nand_WritePage_HalfWorld.
*\*\fun     This routine is for writing one or more Page size half world data.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer containing data to be written.
*\*\param   Address: First page address.
*\*\param   NumPageToWrite: Number of page to write.
*\*\return  New status of the NAND operation. 
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\            And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address 
**/
uint32_t FEMC_Nand_WritePage_HalfWorld(uint32_t Bank_NAND_Addr, uint16_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite)
{
    uint32_t index = 0x00, numpagewritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;

    if(Bank_NAND_Addr == BANK2_NAND_ADDR)
    {
        if((FEMC_NAND_BANK2->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, ENABLE);
        }
    }
    else if(Bank_NAND_Addr == BANK3_NAND_ADDR)
    {
        if((FEMC_NAND_BANK3->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, ENABLE);
        }
    }
    
    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }
    
    while ((NumPageToWrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /* Page write command */
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_AREA_A;
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_WRITE0;
        
        if(NAND_PAGE_SIZE <= 512)
        {
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
            else                                                                                
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
        }                                                                                       
        else                                                                                    
        {                                                                                       
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)                                        
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
            else                                                                                
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }
        }

        /* Calculate the size */
        size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpagewritten);

        /* Write data */
        for (; index < size / 2; index++)
        {
            *(__IO uint16_t*)(Bank_NAND_Addr | DATA_AREA) = pBuffer[index];
        }

        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE_TRUE1;

        /* Check status for successful operation */
        status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

        if (status == NAND_READY)
        {
            numpagewritten++;

            NumPageToWrite--;

            /* Calculate Next page Address */
            addressstatus = FEMC_Nand_AddressIncrement(&Address);
        }
    }
    return (status | addressstatus);
}

/**
*\*\name    FEMC_Nand_ReadPage_Byte.
*\*\fun     This routine is for sequential read from one or several Page size byte data.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer to fill.
*\*\param   Address: First page address.
*\*\param   NumPageToRead Number of page to read
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\        And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address
**/
uint32_t FEMC_Nand_ReadPage_Byte(uint32_t Bank_NAND_Addr, uint8_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead)
{
    uint32_t index = 0x00, numpageread = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;
    
    
    if(Bank_NAND_Addr == BANK2_NAND_ADDR)
    {
        if((FEMC_NAND_BANK2->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, ENABLE);
        }
    }
    else if(Bank_NAND_Addr == BANK3_NAND_ADDR)
    {
        if((FEMC_NAND_BANK3->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, ENABLE);
        }
    }

    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }
    
    while ((NumPageToRead != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /* Page read command */
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_AREA_A;
        
        if(NAND_PAGE_SIZE <= 512)
        {
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
            else                                                                                
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
        }                                                                                       
        else                                                                                    
        {                                                                                       
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)                                        
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
            else                                                                                
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }
        }
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_AREA_TRUE1;

        /* Calculate the size */
        size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpageread);
        /* Get Data into Buffer */
        for (; index < size; index++)
        {
            pBuffer[index] = *(__IO uint8_t*)(Bank_NAND_Addr | DATA_AREA);
        }

        numpageread++;

        NumPageToRead--;

        /* Calculate next page address */
        addressstatus = FEMC_Nand_AddressIncrement(&Address);
    }

    status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

    return (status | addressstatus);
}

/**
*\*\name    FEMC_Nand_ReadPage_HalfWorld.
*\*\fun     This routine is for sequential read from one or several Page size HalfWorld data.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer to fill.
*\*\param   Address: First page address.
*\*\param   NumPageToRead Number of page to read
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\        And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address
**/
uint32_t FEMC_Nand_ReadPage_HalfWorld(uint32_t Bank_NAND_Addr, uint16_t* pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead)
{
    uint32_t index = 0x00, numpageread = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;

    if(Bank_NAND_Addr == BANK2_NAND_ADDR)
    {
        if((FEMC_NAND_BANK2->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK2, ENABLE);
        }
    }
    else if(Bank_NAND_Addr == BANK3_NAND_ADDR)
    {
        if((FEMC_NAND_BANK3->CTRL & FEMC_NAND_ECC_ENABLE) != RESET)
        {
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, DISABLE);
            FEMC_EnableNandEcc(FEMC_NAND_BANK3, ENABLE);
        }
    }
    
    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }
    
    while ((NumPageToRead != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /* Page read command */
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_AREA_A;
        
        if(NAND_PAGE_SIZE <= 512)
        {
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
            else                                                                                
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }
        }
        else
        {                                                                                       
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)                                        
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
            }                                                                                   
            else                                                                                
            {                                                                                   
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = 0x00;                            // column address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);     // row address
                *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);     // row address
            }
        }
        
        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_AREA_TRUE1;
        
        /* Calculate the size */
        size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpageread);

        /* Get Data into Buffer */
        for (; index < size / 2; index++)
        {
            pBuffer[index] = *(__IO uint16_t*)(Bank_NAND_Addr | DATA_AREA);
        }

        numpageread++;

        NumPageToRead--;

        /* Calculate page address */
        addressstatus = FEMC_Nand_AddressIncrement(&Address);
    }

    status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

    return (status | addressstatus);
}

/**
*\*\name    FEMC_NAND_WriteSpareArea_Byte.
*\*\fun     Write Spare area(s) to NAND memory (8-bits addressing).
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer containing data to be written 
*\*\param   Address: First page address
*\*\param   NumSpareAreaTowrite: Number of Spare Area to write
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\        And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address
**/
uint32_t FEMC_NAND_WriteSpareArea_Byte(uint32_t Bank_NAND_Addr, uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite)
{
    uint32_t index = 0x00, numsparesreawritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;
    
    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }
    while((NumSpareAreaTowrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        if(NAND_PAGE_SIZE <= 512)
        {
            /* Page write Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_C;
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE0;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS); 
            }
        }
        else
        {
            /* Page write Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_A;
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE0;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
            }
        }
        /* Date write */
        size = NAND_SPARE_AREA_SIZE +  (NAND_SPARE_AREA_SIZE * numsparesreawritten);
        /* Write the data */ 
        for(; index < size; index++)
        {
            *(__IO uint8_t *)(Bank_NAND_Addr | DATA_AREA) = pBuffer[index];
        }

        *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE_TRUE1;

        /* Check status for successful operation */
        status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

        if(status == NAND_READY)
        {
            numsparesreawritten++;

            NumSpareAreaTowrite--;

            /* Calculate Next page Address */
            addressstatus = FEMC_Nand_AddressIncrement(&Address);
        }       
    }

    return (status | addressstatus);
}

/**
*\*\name    FEMC_NAND_WriteSpareArea_HalfWord.
*\*\fun     Write Spare area(s) to NAND memory (16-bits addressing).
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer containing data to be written 
*\*\param   Address: First page address
*\*\param   NumSpareAreaTowrite: Number of Spare Area to write
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\        And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address
**/
uint32_t FEMC_NAND_WriteSpareArea_HalfWord(uint32_t Bank_NAND_Addr, uint16_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite)
{
    uint32_t index = 0x00, numsparesreawritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;
    
    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }
    while((NumSpareAreaTowrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        if(NAND_PAGE_SIZE <= 512)
        {
            /* Page write Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_C;
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE0;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS); 
            }
        }
        else
        {
            /* Page write Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_A;
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE0;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
            }
        }
        /* Date write */
        size = NAND_SPARE_AREA_SIZE +  (NAND_SPARE_AREA_SIZE * numsparesreawritten);

        /* Write the data */ 
        for(; index < size/2; index++)
        {
            *(__IO uint16_t *)(Bank_NAND_Addr | DATA_AREA) = pBuffer[index];
        }

        *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_WRITE_TRUE1;

        /* Check status for successful operation */
        status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

        if(status == NAND_READY)
        {
            numsparesreawritten++;

            NumSpareAreaTowrite--;

            /* Calculate Next page Address */
            addressstatus = FEMC_Nand_AddressIncrement(&Address);
        }       
    }

    return (status | addressstatus);
}

/**
*\*\name    FEMC_NAND_ReadSpareArea_Byte.
*\*\fun     Read Spare area(s) from NAND memory (8-bits addressing).
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer containing data to be written 
*\*\param   Address: First page address
*\*\param   NumSpareAreaTowrite: Number of Spare Area to write
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\        And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address
**/
uint32_t FEMC_NAND_ReadSpareArea_Byte(uint32_t Bank_NAND_Addr, uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead)
{
    uint32_t numsparearearead = 0x00, index = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;
    
    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }

    while((NumSpareAreaToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
    {
        if(NAND_PAGE_SIZE <= 512)
        {
            /* Page read Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_C;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS); 
            }
        }
        else
        {
            /* Page read Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_A;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
            }
        }

        *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA)  = NAND_CMD_AREA_TRUE1;
        /* Data Read */
        size = NAND_SPARE_AREA_SIZE +  (NAND_SPARE_AREA_SIZE * numsparearearead);
//        pBuffer[index] = *(__IO uint8_t *)(Bank_NAND_Addr | DATA_AREA);
//        pBuffer[index] = *(__IO uint8_t *)(Bank_NAND_Addr | DATA_AREA);
        /* Get Data into Buffer */
        for ( ;index < size; index++)
        {
            pBuffer[index] = *(__IO uint8_t *)(Bank_NAND_Addr | DATA_AREA);
        }

        numsparearearead++;

        NumSpareAreaToRead--;

        /* Calculate page address */
        addressstatus = FEMC_Nand_AddressIncrement(&Address);
    }

    status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

    return (status | addressstatus);
}

/**
*\*\name    FEMC_NAND_ReadSpareArea_HalfWord.
*\*\fun     Read Spare area(s) from NAND memory (16-bits addressing).
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   pBuffer: pointer on the Buffer containing data to be written 
*\*\param   Address: First page address
*\*\param   NumSpareAreaTowrite: Number of Spare Area to write
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\        And the new status of the increment address operation. It can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address
**/
uint32_t FEMC_NAND_ReadSpareArea_HalfWord(uint32_t Bank_NAND_Addr, uint16_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead)
{
    uint32_t numsparearearead = 0x00, index = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;
    
    if(ROW_ADDRESS >= NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)
    {
        addressstatus = NAND_INVALID_ADDRESS;
    }

    while((NumSpareAreaToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
    {
        if(NAND_PAGE_SIZE <= 512)
        {
            /* Page write Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_C;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = 0x00; 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS); 
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS); 
            }
        }
        else
        {
            /* Page read Spare area command and address */
            *(__IO uint8_t *)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_AREA_A;
            
            if(NAND_BLOCK_SIZE * Address.Block <= 65535)
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
            }
            else
            {
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_1ST_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = COLUMN_2ND_CYCLE(COLUMN_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
                *(__IO uint8_t *)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
            }
        }

        /* Data Read */
        size = NAND_SPARE_AREA_SIZE +  (NAND_SPARE_AREA_SIZE * numsparearearead);

        /* Get Data into Buffer */
        for ( ;index < size/2; index++)
        {
            pBuffer[index] = *(__IO uint16_t *)(Bank_NAND_Addr | DATA_AREA);
        }

        numsparearearead++;

        NumSpareAreaToRead--;

        /* Calculate page address */
        addressstatus = FEMC_Nand_AddressIncrement(&Address);
    }

    status = FEMC_Nand_GetStatus(Bank_NAND_Addr);

    return (status | addressstatus);
}

/**
*\*\name    FEMC_Nand_Erase_Block.
*\*\fun     This routine erase complete block from NAND FLASH.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\param   Address: Any address into block to be erased.
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
**/
uint32_t FEMC_Nand_Erase_Block(uint32_t Bank_NAND_Addr, NAND_ADDRESS Address)
{
    *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_ERASE0;

    *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
    *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
    *(__IO uint8_t*)(Bank_NAND_Addr | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);

    *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_ERASE1;
    
    return (FEMC_Nand_GetStatus(Bank_NAND_Addr));
}

/**
*\*\name    FEMC_Nand_Reset.
*\*\fun     This routine reset the NAND FLASH.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\return  NAND_READY
**/
uint32_t FEMC_Nand_Reset(uint32_t Bank_NAND_Addr)
{
    *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_RESET;

    return (NAND_READY);
}

/**
*\*\name    FEMC_Nand_GetStatus.
*\*\fun     Get the NAND operation status.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_TIMEOUT_ERROR: when the previous operation generate a Timeout error
*\*\            - NAND_READY: when memory is ready for the next operation
**/
uint32_t FEMC_Nand_GetStatus(uint32_t Bank_NAND_Addr)
{
    uint32_t timeout = 0x1000000, status = NAND_READY;

    status = FEMC_Nand_ReadStatus(Bank_NAND_Addr);

    /* Wait for a NAND operation to complete or a TIMEOUT to occur */
    while ((status != NAND_READY) && (timeout != 0x00))
    {
        status = FEMC_Nand_ReadStatus(Bank_NAND_Addr);
        timeout--;
    }

    if (timeout == 0x00)
    {
        status = NAND_TIMEOUT_ERROR;
    }

    /* Return the operation status */
    return (status);
}

/**
*\*\name    FEMC_Nand_ReadStatus.
*\*\fun     Reads the NAND memory status using the Read status command.
*\*\param   Bank_NAND_Addr: BANK2_NAND_ADDR or BANK3_NAND_ADDR
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_BUSY: when memory is busy
*\*\            - NAND_READY: when memory is ready for the next operation
*\*\            - NAND_ERROR: when the previous operation gererates error
**/
uint32_t FEMC_Nand_ReadStatus(uint32_t Bank_NAND_Addr)
{
    uint32_t data = 0x00, status = NAND_BUSY;

    /* Read status operation ------------------------------------ */
    *(__IO uint8_t*)(Bank_NAND_Addr | CMD_AREA) = NAND_CMD_STATUS;
    data = *(__IO uint8_t*)(Bank_NAND_Addr);

    if ((data & NAND_ERROR) == NAND_ERROR)
    {
        status = NAND_ERROR;
    }
    else if ((data & NAND_READY) == NAND_READY)
    {
        status = NAND_READY;
    }
    else
    {
        status = NAND_BUSY;
    }

    return (status);
}

/**
*\*\name    FEMC_Nand_AddressIncrement.
*\*\fun     Increment the NAND memory address.
*\*\param   Address: address to be incremented..
*\*\return  New status of the NAND operation. This parameter can be:
*\*\            - NAND_VALID_ADDRESS: When the new address is valid address
*\*\            - NAND_INVALID_ADDRESS: When the new address is invalid address
**/
uint32_t FEMC_Nand_AddressIncrement(NAND_ADDRESS* Address)
{
    uint32_t status = NAND_VALID_ADDRESS;

    Address->Page++;

    if (Address->Page == NAND_BLOCK_SIZE)
    {
        Address->Page = 0;
        Address->Block++;

        if (Address->Block == NAND_ZONE_SIZE)
        {
            Address->Block = 0;
            Address->Zone++;

            if (Address->Zone == NAND_MAX_ZONE)
            {
                status = NAND_INVALID_ADDRESS;
            }
        }
    }

    return (status);
}
