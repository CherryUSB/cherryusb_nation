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
*\*\file n32h47x_48x_rng.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef  __N32H47X_RNG_H__
#define  __N32H47X_RNG_H__

#include <stdint.h>

enum{
	RNG_OK = 0x5a5a5a5a,
	LENError = 0x311ECF50,   //RNG generation of key length error 
    ADDRNULL = 0x7A9DB86C,   // This address is empty
	RNGATTACKED
};


//u32 RNG_init(void);
/**
 * @brief Get pseudo random number
 * @param[out] rand pointer to random number
 * @param[in] the wordlen of random number
 * @param[in] the seed, can be NULL
 * @return RNG_OK:get random number success; othets: get random number fail 
 * @note    
 */
uint32_t GetPseudoRand_U32(uint32_t *rand, uint32_t wordLen,uint32_t seed[2]);


/**
 * @brief Get true random number
 * @param[out] rand pointer to random number
 * @param[in] the wordlen of random number
 * @return RNG_OK:get random number success; othets: get random number fail 
 * @note    
 */
uint32_t GetTrueRand_U32(uint32_t *rand, uint32_t wordLen);

/**
 * @brief Get RNG lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get RSA lib information
 */
void RNG_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);

#endif


