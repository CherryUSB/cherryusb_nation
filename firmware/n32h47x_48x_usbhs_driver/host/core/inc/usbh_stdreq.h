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
*\*\file usbh_stdreq.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __USBH_STDREQ_H__
#define __USBH_STDREQ_H__

#include "usbhs_conf.h"
#include "usbhs_hcd.h"
#include "usbh_core.h"
#include "usbh_def.h"

/*Standard Feature Selector for clear feature command*/
#define FEATURE_SELECTOR_ENDPOINT         0X00
#define FEATURE_SELECTOR_DEVICE           0X01


#define INTERFACE_DESC_TYPE               0x04
#define ENDPOINT_DESC_TYPE                0x05
#define INTERFACE_DESC_SIZE               0x09


#define USBH_HID_CLASS                    0x03

extern uint8_t USBH_CfgDesc[512];

USBH_Status USBH_GetDescriptor(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t req_type,uint16_t value_idx, uint8_t* buff, uint16_t length );

USBH_Status USBH_Get_DevDesc(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t length);

USBH_Status USBH_Get_StringDesc(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t string_index, uint8_t *buff, uint16_t length);

USBH_Status USBH_SetCfg(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint16_t configuration_value);

USBH_Status USBH_Get_CfgDesc(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint16_t length);

USBH_Status USBH_SetAddress(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t DeviceAddress);

USBH_Status USBH_ClrFeature(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t ep_num, uint8_t hch_num); 

USBH_Status USBH_SetInterface(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t ep_num, uint8_t altSetting);

USBH_Status USBH_Issue_ClrFeature(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t ep_num);

USBH_DescHeader_t *USBH_GetNextDesc(uint8_t *pbuf, uint16_t *ptr);

#endif /* __USBH_STDREQ_H__ */
