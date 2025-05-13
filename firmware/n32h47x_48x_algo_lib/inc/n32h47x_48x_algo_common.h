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
*\*\file n32h47x_48x_algo_common.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef _N32H47X_ALGO_COMMON_H_
#define _N32H47X_ALGO_COMMON_H_

#include <stdint.h>


enum{
  Cpy_OK=0,//copy success
	SetZero_OK = 0,//set zero success
	XOR_OK = 0,   //XOR success
	Reverse_OK = 0, //Reverse success
	Cmp_EQUAL = 0, //Two big number are equal
	Cmp_UNEQUAL = 1, //Two big number are not equal

};

/**
 * @brief disturb the sequence order
 * @param[in] order pointer to the sequence to be disturbed
 * @param[in] rand pointer to random number
 * @param[in] the length of order
 * @return RandomSort_OK:  disturb order success;  Others: disturb order fail;
 * @note 
 */
uint32_t RandomSort(uint8_t *order, const  uint8_t *rand, uint32_t len);

/**
 * @brief Copy data by byte
 * @param[in]  dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  byte length 
 * @return Cpy_OK: success; others: fail.
 * @note 1. dst and  src cannot be same
 */
uint32_t Cpy_U8( uint8_t *dst,  uint8_t *src,  uint32_t byteLen);

/**
 * @brief Copy data by word
 * @param[in]  dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  word length 
 * @return Cpy_OK: success; others: fail.
 * @note 1. dst and  src must be aligned by word
 */
uint32_t Cpy_U32( uint32_t *dst, const uint32_t *src,  uint32_t wordLen);

 /**
 * @brief XOR
 * @param[in] a pointer to one data to be XORed
 * @param[in] b pointer to another data to be XORed
 * @param[in] the length of order
 * @return XOR_OK:  operation success;  Others: operation fail;
 * @note 
 */
uint32_t XOR_U8(uint8_t *a, uint8_t *b, uint8_t *c, uint32_t byteLen);

 /**
 * @brief XORed two u32 arrays
 * @param[in] a pointer to one data to be XORed
 * @param[in] b pointer to another data to be XORed
 * @param[in] the length of order
 * @return XOR_OK:  operation success;  Others: operation fail;
 * @note 
 */
uint32_t XOR_U32(uint32_t *a,uint32_t *b,uint32_t *c,uint32_t wordLen);

/**
 * @brief set zero by byte
 * @param[in] dst pointer to the address to be set zero 
 * @param[in]  byte length 
 * @return SetZero_OK: success; others: fail.
 * @note 
 */
uint32_t SetZero_U8(uint8_t *dst, uint32_t byteLen);

/**
 * @brief set zero by word
 * @param[in] dst pointer to the address to be set zero 
 * @param[in]  word length 
 * @return SetZero_OK: success; others: fail.
 * @note 
 */
uint32_t SetZero_U32(uint32_t *dst, uint32_t wordLen);

/**
 * @brief reverse byte order of every word, the words stay the same
 * @param[in]  dst pointer to the destination address
 * @param[in]  src pointer to the source address 
 * @param[in]  word length 
 * @return Reverse_OK: success; others: fail.
 * @note 1.dst and src can be same
 */
uint32_t ReverseBytesInWord_U32(uint32_t *dst, const uint32_t *src, uint32_t wordLen);

/**
 * @brief compare two big number
 * @param[in] a pointer to one big number
 * @param[in] word length of a
 * @param[in] b pointer to another big number
 * @param[in]  word length of b
 * @return Cmp_UNEQUAL:a!=b;Cmp_EQUAL: a==b.
 * 
 */
int32_t Cmp_U32(const uint32_t *a, uint32_t aWordLen, const uint32_t *b, uint32_t bWordLen);

/**
 * @brief compare two big number
 * @param[in] a pointer to one big number
 * @param[in] word length of a
 * @param[in] b pointer to another big number
 * @param[in]  word length of b
 * @return Cmp_UNEQUAL:a!=b;Cmp_EQUAL: a==b.
 * 
 */
int32_t Cmp_U8(const  uint8_t *a, uint32_t aByteLen, const uint8_t *b, uint32_t bByteLen);


#endif

