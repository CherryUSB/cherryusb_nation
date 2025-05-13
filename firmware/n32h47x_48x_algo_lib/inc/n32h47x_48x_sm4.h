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
*\*\file n32h47x_48x_sm4.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32H47X_SM4_H__
#define __N32H47X_SM4_H__

#include <stdint.h>

#define SM4_ECB (0x11111111)
#define SM4_CBC (0x22222222)
#define SM4_ENC  (0x33333333)
#define SM4_DEC  (0x44444444)
enum{
     SM4_Crypto_OK=0, //SM4 opreation success
	   SM4_Init_OK=0, //SM4 Init opreation success
		 SM4_ADRNULL =0x27A90E35, //the address is NULL
		 SM4_ModeErr, //working mode error(Neither ECB nor CBC)
		 SM4_EnDeErr,  // En&De error(Neither encryption nor decryption)
		 SM4_LengthErr,//the word length of input error(the word length is 0 or is not as times as 4)
	   SM4_UnInitError,   //SM4 uninitialized
};

typedef struct{
	uint32_t *in;   // the first part of input to be encrypted or decrypted
	uint32_t *iv;   // the first part of initial vector
	uint32_t *out;  // the first part of out
	uint32_t *key;  // the first part of key
	uint32_t inWordLen; //the word length of input or output 
	uint32_t EnDeMode; //encrypt/decrypt
	uint32_t workingMode; //  ECB/CBC 
}SM4_PARM;

 /**
 * @brief SM4_Init
 * @return SM4_Init_OK, SM4 Init success; othets: SM4 Init fail
 * @note    
 */
uint32_t SM4_Init(SM4_PARM *parm);
/**
 * @brief SM4 crypto
 * @param[in] parm pointer to SM4 context and the detail please refer to struct SM4_PARM in SM4.h
 * @return SM4_Crypto_OK, SM4 crypto success; othets: SM4 crypto fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2.Input and output can be the same buffer
 *        3. IV can be NULL when ECB mode
 *        4. The word lengrh of message must be as times as 4.
 *        5. If the input is in byte, make sure align by word.
 */
uint32_t SM4_Crypto(SM4_PARM *parm);


/**
 * @brief Close SM4 algorithm
 * @return none
 * @note if you want to close SM4 algorithm, this function can be recalled.  
 */
void SM4_Close(void);


/**
 * @brief Get SM4 lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get SM4 lib information
 */
void SM4_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);


#endif
