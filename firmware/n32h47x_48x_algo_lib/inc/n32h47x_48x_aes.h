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
*\*\file n32h47x_48x_aes.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32H47X_AES_H__
#define __N32H47X_AES_H__

#include <stdint.h>

#define AES_ECB (0x11111111)
#define AES_CBC (0x22222222)
#define AES_CTR (0x33333333)

#define AES_ENC  (0x44444444)
#define AES_DEC  (0x55555555)

enum
{
	AES_Crypto_OK = 0x0,   //AES opreation success
	AES_Init_OK = 0x0,   //AES Init opreation success
	AES_Crypto_ModeError = 0x5a5a5a5a,	 //Working mode error(Neither ECB nor CBC nor CTR)
	AES_Crypto_EnOrDeError,    //En&De error(Neither encryption nor decryption)
	AES_Crypto_ParaNull,    // the part of input(output/iv) Null    
	AES_Crypto_LengthError,     // if Working mode is ECB or CBC,the length of input message must be 4 times and cannot be zero;
	                            //if Working mode is CTR,the length of input message cannot be zero; othets: return AES_Crypto_LengthError

	AES_Crypto_KeyLengthError, //the keyWordLen must be 4 or 6 or 8; othets:return AES_Crypto_KeyLengthError
  AES_Crypto_UnInitError, //AES uninitialized
};

typedef struct
{
	uint32_t *in;		// the part of input to be encrypted or decrypted
	uint32_t *iv;		// the part of initial vector
	uint32_t *out;		// the part of out
	uint32_t *key;		// the part of key
	uint32_t keyWordLen;   // the length(by word) of key
	uint32_t inWordLen;	// the length(by word) of plaintext or cipher
	uint32_t En_De;	// 0x44444444- encrypt, 0x55555555 - decrypt
	uint32_t Mode;  // 0x11111111 - ECB, 0x22222222 - CBC, 0x33333333 - CTR
}AES_PARM;

 /**
 * @brief AES_Init
 * @return AES_Init_OK, AES Init success; othets: AES Init fail
 * @note    
 */

uint32_t  AES_Init(AES_PARM *parm);

/**
 * @brief AES crypto
 * @param[in] parm pointer to AES context and the detail please refer to struct AES_PARM in AES.h
 * @return AES_Crypto_OK, AES crypto success; othets: AES crypto fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2.Input and output can be the same buffer
 *        3. IV can be NULL when ECB mode
 *        4. If Working mode is ECB or CBC,the length of input message must be 4 times and cannot be zero;
 *	         if Working mode is CTR,the length of input message cannot be zero;
 *        5. If the input is in byte, make sure align by word.
 */
uint32_t AES_Crypto(AES_PARM *parm);

/**
 * @brief AES close
 * @return none
 * @note if you want to close AES algorithm, this function can be recalled.
 */
void AES_Close(void);

/**
 * @brief Get AES lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get AES lib information
 */
void AES_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);




#endif


