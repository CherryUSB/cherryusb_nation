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
*\*\file usbfsd_mem.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "usbfsd_lib.h"
u8* EpOutDataPtrTmp;
u8* EpInDataPtrTmp;

/**
*\*\name    USB_CopyUserToPMABuf.
*\*\fun     Copy a buffer from user memory area to packet memory area (PMA)
*\*\param   pbUsrBuf pointer to user memory area.
*\*\param   wPMABufAddr address into PMA.
*\*\param   wNBytes no. of bytes to be copied.
*\*\return  none
**/
void USB_CopyUserToPMABuf(uint8_t* pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
    uint32_t n = (wNBytes + 1) >> 1; /* n = (wNBytes + 1) / 2 */
    uint32_t i, temp1, temp2;
    uint16_t* pdwVal;
    pdwVal = (uint16_t*)(wPMABufAddr * 2 + PMAAddr);
    for (i = n; i != 0; i--)
    {
        temp1 = (uint16_t)*pbUsrBuf;
        pbUsrBuf++;
        temp2     = temp1 | (uint16_t)*pbUsrBuf << 8;
        *pdwVal++ = temp2;
        pdwVal++;
        pbUsrBuf++;
        EpInDataPtrTmp = pbUsrBuf;
    }
}

/**
*\*\name    USB_CopyPMAToUserBuf.
*\*\fun     Copy a buffer from packet memory area (PMA) to user memory area
*\*\param   pbUsrBuf    pointer to user memory area.
*\*\param   wPMABufAddr address into PMA.
*\*\param   wNBytes no. of bytes to be copied.
*\*\return  none
**/
void USB_CopyPMAToUserBuf(uint8_t* pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
    uint32_t n = (wNBytes + 1) >> 1; /* /2*/
    uint32_t i;
    uint32_t* pdwVal;
    pdwVal = (uint32_t*)(wPMABufAddr * 2 + PMAAddr);
    for (i = n; i != 0; i--)
    {
        *(uint16_t*)pbUsrBuf++ = *pdwVal++;
        pbUsrBuf++;
        EpOutDataPtrTmp = pbUsrBuf;
    }
}
