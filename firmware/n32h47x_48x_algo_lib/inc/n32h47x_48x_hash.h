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
*\*\file n32h47x_48x_hash.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/


#ifndef __N32H47X_HASH_H__
#define __N32H47X_HASH_H__
#include <stdint.h>
#ifndef true
#define true					1
#endif // true

#ifndef false
#define false					0
#endif // false

#define  ALG_SHA1           (uint16_t)(0x0004)
#define  ALG_SHA224         (uint16_t)(0x000A)
#define  ALG_SHA256         (uint16_t)(0x000B)
#define  ALG_MD5            (u16)(0x000C)
#define  ALG_SM3	    (uint16_t)(0x0012)



enum
{
	HASH_SEQUENCE_TRUE = 0x0105A5A5,//save IV
	HASH_SEQUENCE_FALSE = 0x010A5A5A, //not save IV 
	HASH_Init_OK = 0,//hash init success
	HASH_Start_OK = 0,//hash update success
	HASH_Update_OK = 0,//hash update success
	HASH_Complete_OK = 0,//hash complete success
	HASH_Close_OK = 0,//hash close success
	HASH_ByteLenPlus_OK = 0,//byte length plus success
	HASH_PadMsg_OK = 0,//message padding success
	HASH_ProcMsgBuf_OK = 0, //message processing success
	SHA1_Hash_OK = 0,//sha1 operation success
	SM3_Hash_OK = 0,//sm3 operation success
	SHA224_Hash_OK = 0,//sha224 operation success
	SHA256_Hash_OK = 0,//sha256 operation success
	MD5_Hash_OK = 0,//MD5 operation success
	
	HASH_Init_ERROR = 0x01044400,//hash init error
	HASH_Start_ERROR, //hash start error
	HASH_Update_ERROR, //hash update error
	HASH_ByteLenPlus_ERROR,//hash byte plus error
};

typedef struct _HASH_CTX_ HASH_CTX;

typedef struct
{
	const uint16_t HashAlgID;//choice hash algorithm
	const uint32_t * const K, KLen;//K and word length of K
	const uint32_t * const IV, IVLen;//IV and word length of IV
	const uint32_t HASH_SACCR, HASH_HASHCTRL;//relate registers
	const uint32_t BlockByteLen, BlockWordLen; //byte length of block, word length of block
	const uint32_t DigestByteLen, DigestWordLen; //byte length of digest,word length of digest
	const uint32_t Cycle; //interation times
	uint32_t (* const ByteLenPlus)(uint32_t *, uint32_t); //function pointer
	uint32_t (* const PadMsg)(HASH_CTX *); //function pointer
}HASH_ALG;

typedef struct _HASH_CTX_
{
	const HASH_ALG	*hashAlg;//pointer to HASH_ALG
	uint32_t		sequence;	// TRUE if the IV should be saved
	uint32_t 	IV[16]; 
	uint32_t		msgByteLen[4];
  uint8_t		msgBuf[128+4];
  uint32_t		msgIdx;
}HASH_CTX;

extern const HASH_ALG HASH_ALG_SHA1[1];
extern const HASH_ALG HASH_ALG_SHA224[1];
extern const HASH_ALG HASH_ALG_SHA256[1];
extern const HASH_ALG HASH_ALG_MD5[1];
extern const HASH_ALG HASH_ALG_SM3[1];
extern const HASH_ALG HASH_ALG_SM3_160[1];
extern const HASH_ALG HASH_ALG_SM3_192[1];
/**
 * @brief  Hash init
 * @param[in] ctx pointer to HASH_CTX struct
 * @return HASH_Init_OK,  Hash init success; othets:  Hash init fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 */
uint32_t HASH_Init(HASH_CTX *ctx);

/**
 * @brief  Hash start
 * @param[in] ctx pointer to HASH_CTX struct
 * @return HASH_Start_OK,  Hash start success; othets:  Hash start fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 *         2.HASH_Init() should be recalled before use this function 
 */
uint32_t HASH_Start(HASH_CTX *ctx);

/**
 * @brief  Hash update
 * @param[in] ctx pointer to HASH_CTX struct
 * @param[in] in pointer to message
 * @param[out] out pointer tohash result,digest
 * @return HASH_Update_OK,  Hash update success; othets:  Hash update fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 *         2.HASH_Init() and HASH_Start() should be recalled before use this function 
 */
uint32_t HASH_Update(HASH_CTX *ctx,  uint8_t *in,  uint32_t byteLen);

/**
 * @brief  Hash complete
 * @param[in] ctx pointer to HASH_CTX struct
 * @param[out] out pointer tohash result,digest
 * @return HASH_Complete_OK,  Hash complete success; othets:  Hash complete fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 *         2.HASH_Init(), HASH_Start() and HASH_Update() should be recalled before use this function 
 */
uint32_t HASH_Complete(HASH_CTX *ctx,  uint8_t *out);

/**
 * @brief  Hash close
 * @return HASH_Close_OK, Hash close success; othets: Hash close fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t HASH_Close(void);

/**
 * @brief  SM3 Hash for 256bits digest
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SM3_Hash_OK, SM3 hash success; othets: SM3 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SM3_Hash(uint8_t *in,uint32_t byteLen, uint8_t* out);


/**
 * @brief  SHA1 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SHA1_Hash_OK, SHA1 hash success; othets: SHA1 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA1_Hash(uint8_t*in, uint32_t byteLen, uint8_t*out);

/**
 * @brief  SHA224 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SHA224_Hash_OK, SHA224 hash success; othets: SHA224 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA224_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);


/**
 * @brief  SHA256 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SHA256_Hash_OK, SHA256 hash success; othets: SHA256 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA256_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);

/**
 * @brief  MD5 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[in] out pointer tohash result,digest
 * @return MD5_Hash_OK, MD5 hash success; othets: MD5 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t MD5_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);

/**
 * @brief Get HASH lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get RSA lib information
 */
void HASH_Version(uint8_t*type, uint8_t*customer, uint8_t date[3], uint8_t *version);


#endif
