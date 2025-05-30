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
*\*\file n32h47x_48x_rcc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H47X_48X_RCC_H
#define __N32H47X_48X_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32h47x_48x.h"

/** RCC_Exported_Types **/

typedef struct
{
    uint32_t SysclkFreq;    /* returns SYSCLK clock frequency expressed in Hz */
    uint32_t HclkFreq;      /* returns HCLK clock frequency expressed in Hz */
    uint32_t Pclk1Freq;     /* returns PCLK1 clock frequency expressed in Hz */
    uint32_t Pclk2Freq;     /* returns PCLK2 clock frequency expressed in Hz */
    uint32_t AdcPllClkFreq; /* returns ADCPLLCLK clock frequency expressed in Hz */
    uint32_t AdcHclkFreq;   /* returns ADCHCLK clock frequency expressed in Hz */
    uint32_t ShrtpllFreq;   /* returns ADCHCLK clock frequency expressed in Hz */
} RCC_ClocksType;

typedef enum
{
    SYSCLK_SRC_HSI = 0x00,
    SYSCLK_SRC_HSE = 0x04,
    SYSCLK_SRC_PLL = 0x08
} SysclkSource;


#define VCO_MIN  300000000 //300M
#define VCO_MAX  1000000000//1000M
#define REF_MIN  1000000   //1M
#define REF_MAX  50000000  //50M
#define NR_MIN   1
#define NR_MAX   64
#define NF_MIN   2
#define NF_MAX   4095

#define RCC_HSI_ENABLE        (RCC_CTRL_HSIEN) 
#define RCC_HSECSS_ENABLE     (RCC_CTRL_HSECSSEN)
#define RCC_PLL_ENABLE        (RCC_CTRL_PLLEN)
#define RCC_SHRTPLL_ENABLE    (RCC_SHRTPLLCTRL3_SHRTPLLEN)
#define RCC_SHRTPLLMODE_PD    (RCC_SHRTPLLCTRL1_SHRTPLLMODE)
#define RCC_SHRTPLL_SATEN     (RCC_SHRTPLLCTRL1_SATEN)
#define RCC_SHRTPLL_FRACEN    (RCC_SHRTPLLCTRL1_FRACEN)
#define RCC_LSI_ENABLE        (RCC_CTRLSTS_LSIEN)
#define RCC_RTC_ENABLE        (RCC_BDCTRL_RTCEN)
#define RCC_LSECSS_ENABLE     (RCC_BDCTRL_LSECSSEN)
#define RCC_HSICSS_ENABLE     (RCC_CSSCTRL_HSICSSEN)
#define RCC_TRNG1M_ENABLE     (RCC_CFG3_TRNG1MEN)
#define RCC_BOR_ENABLE        (RCC_CFG3_BORRSTEN)



/** RCC_Exported_Constants **/

/** Register shift macro definition **/
#define  RCC_FLAG_OFFSET             (REG_BIT5_OFFSET)
#define  RCC_CTRL_HSITRIM_OFFSET     (REG_BIT20_OFFSET)
#define  RCC_APB2PRES_OFFSET         (REG_BIT3_OFFSET)

/** RCC RCC_REG_BIT_MASK **/
#define RCC_REG_BIT_MASK  ((uint32_t)0x00000000)

/** HSE_configuration **/
#define RCC_HSE_DISABLE  (RCC_REG_BIT_MASK)
#define RCC_HSE_ENABLE   (RCC_CTRL_HSEEN)
#define RCC_HSE_BYPASS   (RCC_CTRL_HSEBP)


/** Internal High Speed clock trimming **/
#define RCC_HSITRIM_MASK (~RCC_CTRL_HSITRIM)


/** PLL Mask **/
#define RCC_PLL_CFG_MASK      (~(RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES | RCC_CFG_PLLHSIPRES | RCC_CFG_PLLMULFCT)) 
#define RCC_PLL_PLLCTRL_MASK  (~(RCC_PLLCTRL_PLLINPRES | RCC_PLLCTRL_PLLOUTPRES| RCC_PLLCTRL_LPFC2| RCC_PLLCTRL_LPFR| RCC_PLLCTRL_LPFC1)) 

/** PLL_entry_clock_source **/
#define RCC_PLL_SRC_HSI      (RCC_REG_BIT_MASK)
#define RCC_PLL_SRC_HSI_DIV2 (RCC_CFG_PLLHSIPRES)
#define RCC_PLL_SRC_HSE      (RCC_CFG_PLLSRC)
#define RCC_PLL_SRC_HSE_DIV2 (RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES)

#define RCC_PLL_PRE_1  (RCC_PLLCTRL_PLLINPRES_DIV1)
#define RCC_PLL_PRE_2  (RCC_PLLCTRL_PLLINPRES_DIV2)
#define RCC_PLL_PRE_3  (RCC_PLLCTRL_PLLINPRES_DIV3)
#define RCC_PLL_PRE_4  (RCC_PLLCTRL_PLLINPRES_DIV4)

/** PLL_multiplication_factor **/
#define RCC_PLL_MUL_8   (RCC_CFG_PLLMULFCT8)
#define RCC_PLL_MUL_10  (RCC_CFG_PLLMULFCT10)
#define RCC_PLL_MUL_12  (RCC_CFG_PLLMULFCT12)
#define RCC_PLL_MUL_14  (RCC_CFG_PLLMULFCT14)
#define RCC_PLL_MUL_16  (RCC_CFG_PLLMULFCT16)
#define RCC_PLL_MUL_18  (RCC_CFG_PLLMULFCT18)
#define RCC_PLL_MUL_20  (RCC_CFG_PLLMULFCT20) 
#define RCC_PLL_MUL_22  (RCC_CFG_PLLMULFCT22) 
#define RCC_PLL_MUL_24  (RCC_CFG_PLLMULFCT24) 
#define RCC_PLL_MUL_26  (RCC_CFG_PLLMULFCT26) 
#define RCC_PLL_MUL_28  (RCC_CFG_PLLMULFCT28) 
#define RCC_PLL_MUL_30  (RCC_CFG_PLLMULFCT30) 
#define RCC_PLL_MUL_32  (RCC_CFG_PLLMULFCT32) 
#define RCC_PLL_MUL_34  (RCC_CFG_PLLMULFCT34) 
#define RCC_PLL_MUL_36  (RCC_CFG_PLLMULFCT36) 
#define RCC_PLL_MUL_38  (RCC_CFG_PLLMULFCT38) 
#define RCC_PLL_MUL_40  (RCC_CFG_PLLMULFCT40) 
#define RCC_PLL_MUL_42  (RCC_CFG_PLLMULFCT42) 
#define RCC_PLL_MUL_44  (RCC_CFG_PLLMULFCT44) 
#define RCC_PLL_MUL_46  (RCC_CFG_PLLMULFCT46) 
#define RCC_PLL_MUL_48  (RCC_CFG_PLLMULFCT48) 
#define RCC_PLL_MUL_50  (RCC_CFG_PLLMULFCT50) 
#define RCC_PLL_MUL_52  (RCC_CFG_PLLMULFCT52) 
#define RCC_PLL_MUL_54  (RCC_CFG_PLLMULFCT54) 
#define RCC_PLL_MUL_56  (RCC_CFG_PLLMULFCT56) 
#define RCC_PLL_MUL_58  (RCC_CFG_PLLMULFCT58) 
#define RCC_PLL_MUL_60  (RCC_CFG_PLLMULFCT60) 
#define RCC_PLL_MUL_62  (RCC_CFG_PLLMULFCT62) 
#define RCC_PLL_MUL_64  (RCC_CFG_PLLMULFCT64) 
#define RCC_PLL_MUL_66  (RCC_CFG_PLLMULFCT66) 
#define RCC_PLL_MUL_68  (RCC_CFG_PLLMULFCT68) 
#define RCC_PLL_MUL_70  (RCC_CFG_PLLMULFCT70) 
#define RCC_PLL_MUL_72  (RCC_CFG_PLLMULFCT72) 
#define RCC_PLL_MUL_74  (RCC_CFG_PLLMULFCT74) 
#define RCC_PLL_MUL_76  (RCC_CFG_PLLMULFCT76) 

#define RCC_PLLOUT_DIV_1  (RCC_PLLCTRL_PLLOUTPRES_DIV1)
#define RCC_PLLOUT_DIV_2  (RCC_PLLCTRL_PLLOUTPRES_DIV2)
#define RCC_PLLOUT_DIV_4  (RCC_PLLCTRL_PLLOUTPRES_DIV4)
#define RCC_PLLOUT_DIV_8  (RCC_PLLCTRL_PLLOUTPRES_DIV8)

/** SHRTPLL_multiplication_factor **/
#define RCC_SHRTPLL_CLKF_MASK        (~RCC_SHRTPLLCTRL1_CLKF) 
#define RCC_SHRTPLL_CLKR_MASK        (~RCC_SHRTPLLCTRL2_CLKR) 
#define RCC_SHRTPLL_BWTRIM_MASK      (~RCC_SHRTPLLCTRL3_BWTRIM) 
#define RCC_SHRTPLL_SRC_MASK         (~RCC_SHRTPLLCTRL3_SHRTPLLSRC) 
#define RCC_SHRTPLL_SRC_HSI          (RCC_REG_BIT_MASK) 
#define RCC_SHRTPLL_SRC_HSE          (RCC_SHRTPLLCTRL3_SHRTPLLSRC) 

/** System_clock_source **/
#define RCC_SYSCLK_SRC_CFG_MASK        (~RCC_CFG_SCLKSW)
#define RCC_SYSCLK_SRC_PLLCTRL_MASK    (~RCC_PLLCTRL_SCLKPLLSEL)
#define RCC_SYSCLK_SRC_CFG_PLLSEL      (RCC_CFG_SCLKSW_PLL)

#define RCC_SYSCLK_SRC_HSI         (0x80000000|RCC_REG_BIT_MASK)
#define RCC_SYSCLK_SRC_HSE         (0x80000000|RCC_CFG_SCLKSW_HSE)
#define RCC_SYSCLK_SRC_PLL         (RCC_PLLCTRL_SCLKPLLSEL_PLL)
#define RCC_SYSCLK_SRC_SHRTPLL     (RCC_PLLCTRL_SCLKPLLSEL_SHRTPLL)
#define RCC_SYSCLK_SRC_USBHS240M  (RCC_PLLCTRL_SCLKPLLSEL_USBHS240M)

/** System_clock_status mask **/
#define RCC_SYSCLK_STS_MASK    (RCC_CFG_SCLKSTS)

/** AHB_clock_source **/
#define RCC_SYSCLK_DIV_MASK (~RCC_CFG_AHBPRES)
#define RCC_SYSCLK_DIV1     (RCC_CFG_AHBPRES_DIV1)
#define RCC_SYSCLK_DIV2     (RCC_CFG_AHBPRES_DIV2)
#define RCC_SYSCLK_DIV4     (RCC_CFG_AHBPRES_DIV4)
#define RCC_SYSCLK_DIV8     (RCC_CFG_AHBPRES_DIV8)
#define RCC_SYSCLK_DIV16    (RCC_CFG_AHBPRES_DIV16)
#define RCC_SYSCLK_DIV64    (RCC_CFG_AHBPRES_DIV64)
#define RCC_SYSCLK_DIV128   (RCC_CFG_AHBPRES_DIV128)
#define RCC_SYSCLK_DIV256   (RCC_CFG_AHBPRES_DIV256)
#define RCC_SYSCLK_DIV512   (RCC_CFG_AHBPRES_DIV512)

/** APB1_APB2_clock_source **/
#define RCC_APB1_DIV_MASK   (~RCC_CFG_APB1PRES)
#define RCC_APB2_DIV_MASK   (~RCC_CFG_APB2PRES)
#define RCC_HCLK_DIV1       (RCC_CFG_APB1PRES_DIV1)
#define RCC_HCLK_DIV2       (RCC_CFG_APB1PRES_DIV2)
#define RCC_HCLK_DIV4       (RCC_CFG_APB1PRES_DIV4)
#define RCC_HCLK_DIV8       (RCC_CFG_APB1PRES_DIV8)
#define RCC_HCLK_DIV16      (RCC_CFG_APB1PRES_DIV16)

/** RCC_CFG2_Config **/
#define RCC_ATIM_CLKSRC_MASK      (~RCC_CFG2_ATIMCLKSEL) 
#define RCC_ATIM_CLKSRC_SYSCLK    (RCC_REG_BIT_MASK)
#define RCC_ATIM_CLKSRC_HCLK      (RCC_CFG2_ATIMCLKSEL)

#define RCC_RNGCCLK_SYSCLK_DIV_MASK   (~RCC_CFG2_RNGCPRES) 
#define RCC_RNGCCLK_SYSCLK_DIV1       (RCC_CFG2_RNGCPRES_DIV1)
#define RCC_RNGCCLK_SYSCLK_DIV2       (RCC_CFG2_RNGCPRES_DIV2)
#define RCC_RNGCCLK_SYSCLK_DIV3       (RCC_CFG2_RNGCPRES_DIV3)
#define RCC_RNGCCLK_SYSCLK_DIV4       (RCC_CFG2_RNGCPRES_DIV4)
#define RCC_RNGCCLK_SYSCLK_DIV5       (RCC_CFG2_RNGCPRES_DIV5)
#define RCC_RNGCCLK_SYSCLK_DIV6       (RCC_CFG2_RNGCPRES_DIV6)
#define RCC_RNGCCLK_SYSCLK_DIV7       (RCC_CFG2_RNGCPRES_DIV7)
#define RCC_RNGCCLK_SYSCLK_DIV8       (RCC_CFG2_RNGCPRES_DIV8)
#define RCC_RNGCCLK_SYSCLK_DIV9       (RCC_CFG2_RNGCPRES_DIV9)
#define RCC_RNGCCLK_SYSCLK_DIV10      (RCC_CFG2_RNGCPRES_DIV10)
#define RCC_RNGCCLK_SYSCLK_DIV11      (RCC_CFG2_RNGCPRES_DIV11)
#define RCC_RNGCCLK_SYSCLK_DIV12      (RCC_CFG2_RNGCPRES_DIV12)
#define RCC_RNGCCLK_SYSCLK_DIV13      (RCC_CFG2_RNGCPRES_DIV13)
#define RCC_RNGCCLK_SYSCLK_DIV14      (RCC_CFG2_RNGCPRES_DIV14)
#define RCC_RNGCCLK_SYSCLK_DIV15      (RCC_CFG2_RNGCPRES_DIV15)
#define RCC_RNGCCLK_SYSCLK_DIV16      (RCC_CFG2_RNGCPRES_DIV16)
#define RCC_RNGCCLK_SYSCLK_DIV17      (RCC_CFG2_RNGCPRES_DIV17)
#define RCC_RNGCCLK_SYSCLK_DIV18      (RCC_CFG2_RNGCPRES_DIV18)
#define RCC_RNGCCLK_SYSCLK_DIV19      (RCC_CFG2_RNGCPRES_DIV19)
#define RCC_RNGCCLK_SYSCLK_DIV20      (RCC_CFG2_RNGCPRES_DIV20)
#define RCC_RNGCCLK_SYSCLK_DIV21      (RCC_CFG2_RNGCPRES_DIV21)
#define RCC_RNGCCLK_SYSCLK_DIV22      (RCC_CFG2_RNGCPRES_DIV22)
#define RCC_RNGCCLK_SYSCLK_DIV23      (RCC_CFG2_RNGCPRES_DIV23)
#define RCC_RNGCCLK_SYSCLK_DIV24      (RCC_CFG2_RNGCPRES_DIV24)
#define RCC_RNGCCLK_SYSCLK_DIV25      (RCC_CFG2_RNGCPRES_DIV25)
#define RCC_RNGCCLK_SYSCLK_DIV26      (RCC_CFG2_RNGCPRES_DIV26)
#define RCC_RNGCCLK_SYSCLK_DIV27      (RCC_CFG2_RNGCPRES_DIV27)
#define RCC_RNGCCLK_SYSCLK_DIV28      (RCC_CFG2_RNGCPRES_DIV28)
#define RCC_RNGCCLK_SYSCLK_DIV29      (RCC_CFG2_RNGCPRES_DIV29)
#define RCC_RNGCCLK_SYSCLK_DIV30      (RCC_CFG2_RNGCPRES_DIV30)
#define RCC_RNGCCLK_SYSCLK_DIV31      (RCC_CFG2_RNGCPRES_DIV31)
#define RCC_RNGCCLK_SYSCLK_DIV32      (RCC_CFG2_RNGCPRES_DIV32)

#define RCC_GTIM_CLKSRC_MASK      (~RCC_CFG2_GTIMCLKSEL) 
#define RCC_GTIM_CLKSRC_PCLK      (RCC_REG_BIT_MASK)
#define RCC_GTIM_CLKSRC_SYSCLK    (RCC_CFG2_GTIMCLKSEL)

#define RCC_ADC1MCLK_SRC_MASK     (~RCC_CFG2_ADC1MSEL)
#define RCC_ADC1MCLK_SRC_HSI      (RCC_CFG2_ADC1MSEL_HSI)
#define RCC_ADC1MCLK_SRC_HSE      (RCC_CFG2_ADC1MSEL_HSE)

#define RCC_ADC1MCLK_DIV_MASK  (~RCC_CFG2_ADC1MPRES)
#define RCC_ADC1MCLK_DIV1      (RCC_CFG2_ADC1MPRES_DIV1)
#define RCC_ADC1MCLK_DIV2      (RCC_CFG2_ADC1MPRES_DIV2)
#define RCC_ADC1MCLK_DIV3      (RCC_CFG2_ADC1MPRES_DIV3)
#define RCC_ADC1MCLK_DIV4      (RCC_CFG2_ADC1MPRES_DIV4)
#define RCC_ADC1MCLK_DIV5      (RCC_CFG2_ADC1MPRES_DIV5)
#define RCC_ADC1MCLK_DIV6      (RCC_CFG2_ADC1MPRES_DIV6)
#define RCC_ADC1MCLK_DIV7      (RCC_CFG2_ADC1MPRES_DIV7)
#define RCC_ADC1MCLK_DIV8      (RCC_CFG2_ADC1MPRES_DIV8)
#define RCC_ADC1MCLK_DIV9      (RCC_CFG2_ADC1MPRES_DIV9)
#define RCC_ADC1MCLK_DIV10     (RCC_CFG2_ADC1MPRES_DIV10)
#define RCC_ADC1MCLK_DIV11     (RCC_CFG2_ADC1MPRES_DIV11)
#define RCC_ADC1MCLK_DIV12     (RCC_CFG2_ADC1MPRES_DIV12)
#define RCC_ADC1MCLK_DIV13     (RCC_CFG2_ADC1MPRES_DIV13)
#define RCC_ADC1MCLK_DIV14     (RCC_CFG2_ADC1MPRES_DIV14)
#define RCC_ADC1MCLK_DIV15     (RCC_CFG2_ADC1MPRES_DIV15)
#define RCC_ADC1MCLK_DIV16     (RCC_CFG2_ADC1MPRES_DIV16)
#define RCC_ADC1MCLK_DIV17     (RCC_CFG2_ADC1MPRES_DIV17)
#define RCC_ADC1MCLK_DIV18     (RCC_CFG2_ADC1MPRES_DIV18)
#define RCC_ADC1MCLK_DIV19     (RCC_CFG2_ADC1MPRES_DIV19)
#define RCC_ADC1MCLK_DIV20     (RCC_CFG2_ADC1MPRES_DIV20)
#define RCC_ADC1MCLK_DIV21     (RCC_CFG2_ADC1MPRES_DIV21)
#define RCC_ADC1MCLK_DIV22     (RCC_CFG2_ADC1MPRES_DIV22)
#define RCC_ADC1MCLK_DIV23     (RCC_CFG2_ADC1MPRES_DIV23)
#define RCC_ADC1MCLK_DIV24     (RCC_CFG2_ADC1MPRES_DIV24)
#define RCC_ADC1MCLK_DIV25     (RCC_CFG2_ADC1MPRES_DIV25)
#define RCC_ADC1MCLK_DIV26     (RCC_CFG2_ADC1MPRES_DIV26)
#define RCC_ADC1MCLK_DIV27     (RCC_CFG2_ADC1MPRES_DIV27)
#define RCC_ADC1MCLK_DIV28     (RCC_CFG2_ADC1MPRES_DIV28)
#define RCC_ADC1MCLK_DIV29     (RCC_CFG2_ADC1MPRES_DIV29)
#define RCC_ADC1MCLK_DIV30     (RCC_CFG2_ADC1MPRES_DIV30)
#define RCC_ADC1MCLK_DIV31     (RCC_CFG2_ADC1MPRES_DIV31)
#define RCC_ADC1MCLK_DIV32     (RCC_CFG2_ADC1MPRES_DIV32)

#define RCC_ADCPLLCLK_MASK     (~(RCC_CFG2_ADCOTGPLLPRES | RCC_CFG2_ADCOTGPLLSEL | RCC_CFG2_ADCOTGPLLEN)) 

#define RCC_ADCPLLCLK_SRC_PLL            (RCC_REG_BIT_MASK)   
#define RCC_ADCPLLCLK_SRC_USBHS240M     (RCC_CFG2_ADCOTGPLLSEL)  

#define RCC_ADCPLLCLK_DIV1       (RCC_CFG2_ADCOTGPLLPRES_DIV1)
#define RCC_ADCPLLCLK_DIV2       (RCC_CFG2_ADCOTGPLLPRES_DIV2)
#define RCC_ADCPLLCLK_DIV3       (RCC_CFG2_ADCOTGPLLPRES_DIV3)
#define RCC_ADCPLLCLK_DIV4       (RCC_CFG2_ADCOTGPLLPRES_DIV4)
#define RCC_ADCPLLCLK_DIV6       (RCC_CFG2_ADCOTGPLLPRES_DIV6)
#define RCC_ADCPLLCLK_DIV8       (RCC_CFG2_ADCOTGPLLPRES_DIV8)
#define RCC_ADCPLLCLK_DIV10      (RCC_CFG2_ADCOTGPLLPRES_DIV10)
#define RCC_ADCPLLCLK_DIV12      (RCC_CFG2_ADCOTGPLLPRES_DIV12)

#define RCC_ADCPLLCLK_DISABLE    (RCC_REG_BIT_MASK)
#define RCC_ADCPLLCLK_ENABLE     (RCC_CFG2_ADCOTGPLLEN)

#define RCC_ADCHCLK_DIV_MASK   (~RCC_CFG2_ADCHPRES)
#define RCC_ADCHCLK_DIV1       (RCC_CFG2_ADCHPRES_DIV1)
#define RCC_ADCHCLK_DIV2       (RCC_CFG2_ADCHPRES_DIV2)
#define RCC_ADCHCLK_DIV3       (RCC_CFG2_ADCHPRES_DIV3)
#define RCC_ADCHCLK_DIV4       (RCC_CFG2_ADCHPRES_DIV4)
#define RCC_ADCHCLK_DIV6       (RCC_CFG2_ADCHPRES_DIV6)
#define RCC_ADCHCLK_DIV8       (RCC_CFG2_ADCHPRES_DIV8)
#define RCC_ADCHCLK_DIV10      (RCC_CFG2_ADCHPRES_DIV10)
#define RCC_ADCHCLK_DIV12      (RCC_CFG2_ADCHPRES_DIV12)
#define RCC_ADCHCLK_DIV16      (RCC_CFG2_ADCHPRES_DIV16)
#define RCC_ADCHCLK_DIV32      (RCC_CFG2_ADCHPRES_DIV32)

/** RCC_CFG3_Config **/

#define RCC_I2S3_CLKSRC_MASK       (~RCC_CFG3_I2S3SEL) 
#define RCC_I2S3_CLKSRC_SYSCLK     ( RCC_CFG3_I2S3SEL_SYSCLK)
#define RCC_I2S3_CLKSRC_SHRTPLL    ( RCC_CFG3_I2S3SEL_SHRTPLL)
#define RCC_I2S3_CLKSRC_CLKIN      ( RCC_CFG3_I2S3SEL_CLKIN)
#define RCC_I2S3_CLKSRC_HSI        ( RCC_CFG3_I2S3SEL_HSI)

#define RCC_I2S2_CLKSRC_MASK       (~RCC_CFG3_I2S2SEL) 
#define RCC_I2S2_CLKSRC_SYSCLK     ( RCC_CFG3_I2S2SEL_SYSCLK)
#define RCC_I2S2_CLKSRC_SHRTPLL    ( RCC_CFG3_I2S2SEL_SHRTPLL)
#define RCC_I2S2_CLKSRC_CLKIN      ( RCC_CFG3_I2S2SEL_CLKIN)
#define RCC_I2S2_CLKSRC_HSI        ( RCC_CFG3_I2S2SEL_HSI)

#define RCC_FDCAN_PLLSRC_DIV_MASK (~RCC_CFG3_FDCANPLLPRES) 
#define RCC_FDCAN_PLLSRC_DIV1     (RCC_CFG3_FDCANPLLPRES_DIV1)
#define RCC_FDCAN_PLLSRC_DIV2     (RCC_CFG3_FDCANPLLPRES_DIV2)
#define RCC_FDCAN_PLLSRC_DIV3     (RCC_CFG3_FDCANPLLPRES_DIV3)
#define RCC_FDCAN_PLLSRC_DIV4     (RCC_CFG3_FDCANPLLPRES_DIV4)
#define RCC_FDCAN_PLLSRC_DIV5     (RCC_CFG3_FDCANPLLPRES_DIV5)
#define RCC_FDCAN_PLLSRC_DIV6     (RCC_CFG3_FDCANPLLPRES_DIV6)
#define RCC_FDCAN_PLLSRC_DIV7     (RCC_CFG3_FDCANPLLPRES_DIV7)
#define RCC_FDCAN_PLLSRC_DIV8     (RCC_CFG3_FDCANPLLPRES_DIV8)
#define RCC_FDCAN_PLLSRC_DIV9     (RCC_CFG3_FDCANPLLPRES_DIV9)
#define RCC_FDCAN_PLLSRC_DIV10    (RCC_CFG3_FDCANPLLPRES_DIV10)
#define RCC_FDCAN_PLLSRC_DIV11    (RCC_CFG3_FDCANPLLPRES_DIV11)
#define RCC_FDCAN_PLLSRC_DIV12    (RCC_CFG3_FDCANPLLPRES_DIV12)
#define RCC_FDCAN_PLLSRC_DIV13    (RCC_CFG3_FDCANPLLPRES_DIV13)
#define RCC_FDCAN_PLLSRC_DIV14    (RCC_CFG3_FDCANPLLPRES_DIV14)
#define RCC_FDCAN_PLLSRC_DIV15    (RCC_CFG3_FDCANPLLPRES_DIV15)

#define RCC_FDCAN_CLKSRC_MASK     (~RCC_CFG3_FDCANSEL) 
#define RCC_FDCAN_CLKSRC_PLL      ( RCC_CFG3_FDCANSEL_PLL)
#define RCC_FDCAN_CLKSRC_SHRTPLL  ( RCC_CFG3_FDCANSEL_SHRTPLL)
#define RCC_FDCAN_CLKSRC_HSE      ( RCC_CFG3_FDCANSEL_HSE)

#define RCC_USBPLLCLK_SRC_MASK     (~RCC_CFG3_USBPLLSEL)
#define RCC_USBPLLCLK_SRC_PLL      (RCC_REG_BIT_MASK)
#define RCC_USBPLLCLK_SRC_SHRTPLL  (RCC_CFG3_USBPLLSEL)

#define RCC_USBPLLCLK_DIV_MASK  (~RCC_CFG3_USBPLLPRES)
#define RCC_USBPLLCLK_DIV1      (RCC_CFG3_USBPLLPRES_DIV1)
#define RCC_USBPLLCLK_DIV2      (RCC_CFG3_USBPLLPRES_DIV2)
#define RCC_USBPLLCLK_DIV3      (RCC_CFG3_USBPLLPRES_DIV3)
#define RCC_USBPLLCLK_DIV4      (RCC_CFG3_USBPLLPRES_DIV4)
#define RCC_USBPLLCLK_DIV5      (RCC_CFG3_USBPLLPRES_DIV5)
#define RCC_USBPLLCLK_DIV6      (RCC_CFG3_USBPLLPRES_DIV6)
#define RCC_USBPLLCLK_DIV7      (RCC_CFG3_USBPLLPRES_DIV7)
#define RCC_USBPLLCLK_DIV8      (RCC_CFG3_USBPLLPRES_DIV8)
#define RCC_USBPLLCLK_DIV9      (RCC_CFG3_USBPLLPRES_DIV9)
#define RCC_USBPLLCLK_DIV10     (RCC_CFG3_USBPLLPRES_DIV10)
#define RCC_USBPLLCLK_DIV11     (RCC_CFG3_USBPLLPRES_DIV11)
#define RCC_USBPLLCLK_DIV12     (RCC_CFG3_USBPLLPRES_DIV12)
#define RCC_USBPLLCLK_DIV13     (RCC_CFG3_USBPLLPRES_DIV13)
#define RCC_USBPLLCLK_DIV14     (RCC_CFG3_USBPLLPRES_DIV14)
#define RCC_USBPLLCLK_DIV15     (RCC_CFG3_USBPLLPRES_DIV15)

#define RCC_USBFS_CLKSRC_MASK        (~RCC_CFG3_USBFSSEL) 
#define RCC_USBFS_CLKSRC_UCDR        (RCC_CFG3_USBFSSEL_UCDR)
#define RCC_USBFS_CLKSRC_PLLPRES     (RCC_CFG3_USBFSSEL_PLL)
#define RCC_USBFS_CLKSRC_USBHS48M   (RCC_CFG3_USBFSSEL_USBHS48M)

#define RCC_USBHS_CLKSRC_MASK        (~RCC_USBHSCTRL1_USBHSSEL) 
#define RCC_USBHS_CLKSRC_HSE         (RCC_REG_BIT_MASK)
#define RCC_USBHS_CLKSRC_PLLPRES     (RCC_USBHSCTRL1_USBHSSEL) 

#define RCC_USBHS_BW_MASK        (~RCC_USBHSCTRL1_PLLBW) 
#define RCC_USBHS_BW_16M         (RCC_REG_BIT_MASK)
#define RCC_USBHS_BW_OTHER       (RCC_USBHSCTRL1_PLLBW)

#define RCC_USBHS_FREQ_MASK        (~RCC_USBHSCTRL1_USBHSFSEL) 
#define RCC_USBHS_FREQ_19_2M       (RCC_REG_BIT_MASK)
#define RCC_USBHS_FREQ_20M         (RCC_USBHSCTRL1_USBHSFSEL_0)
#define RCC_USBHS_FREQ_24M         (RCC_USBHSCTRL1_USBHSFSEL_1)
#define RCC_USBHS_FREQ_16_OR_32M   (RCC_USBHSCTRL1_USBHSFSEL_0|RCC_USBHSCTRL1_USBHSFSEL_1)
#define RCC_USBHS_FREQ_26M         (RCC_USBHSCTRL1_USBHSFSEL_1|RCC_USBHSCTRL1_USBHSFSEL_2)

#define RCC_TRNG1MCLK_SRC_MASK     (~RCC_CFG3_TRNG1MSEL)
#define RCC_TRNG1MCLK_SRC_HSI      (RCC_REG_BIT_MASK)
#define RCC_TRNG1MCLK_SRC_HSE      (RCC_CFG3_TRNG1MSEL)

#define RCC_TRNG1MCLK_DIV_MASK  (~RCC_CFG3_TRNG1MPRES)
#define RCC_TRNG1MCLK_DIV2      (RCC_CFG3_TRNG1MPRES_DIV2)
#define RCC_TRNG1MCLK_DIV4      (RCC_CFG3_TRNG1MPRES_DIV4)
#define RCC_TRNG1MCLK_DIV6      (RCC_CFG3_TRNG1MPRES_DIV6)
#define RCC_TRNG1MCLK_DIV8      (RCC_CFG3_TRNG1MPRES_DIV8)
#define RCC_TRNG1MCLK_DIV10     (RCC_CFG3_TRNG1MPRES_DIV10)
#define RCC_TRNG1MCLK_DIV12     (RCC_CFG3_TRNG1MPRES_DIV12)
#define RCC_TRNG1MCLK_DIV14     (RCC_CFG3_TRNG1MPRES_DIV14)
#define RCC_TRNG1MCLK_DIV16     (RCC_CFG3_TRNG1MPRES_DIV16)
#define RCC_TRNG1MCLK_DIV18     (RCC_CFG3_TRNG1MPRES_DIV18)
#define RCC_TRNG1MCLK_DIV20     (RCC_CFG3_TRNG1MPRES_DIV20)
#define RCC_TRNG1MCLK_DIV22     (RCC_CFG3_TRNG1MPRES_DIV22)
#define RCC_TRNG1MCLK_DIV24     (RCC_CFG3_TRNG1MPRES_DIV24)
#define RCC_TRNG1MCLK_DIV26     (RCC_CFG3_TRNG1MPRES_DIV26)
#define RCC_TRNG1MCLK_DIV28     (RCC_CFG3_TRNG1MPRES_DIV28)
#define RCC_TRNG1MCLK_DIV30     (RCC_CFG3_TRNG1MPRES_DIV30)
#define RCC_TRNG1MCLK_DIV32     (RCC_CFG3_TRNG1MPRES_DIV32)

#define RCC_TRACECLK_DIV_MASK  (~RCC_CFG3_TRACEPRES)
#define RCC_TRACECLK_DIV1      (RCC_CFG3_TRACEPRES_DIV1)
#define RCC_TRACECLK_DIV2      (RCC_CFG3_TRACEPRES_DIV2)
#define RCC_TRACECLK_DIV4      (RCC_CFG3_TRACEPRES_DIV4)
#define RCC_TRACECLK_DIV8      (RCC_CFG3_TRACEPRES_DIV8)
/** RCC_BDCTRL_Config **/

/** LSE_configuration **/
#define RCC_LSE_DISABLE (RCC_REG_BIT_MASK)
#define RCC_LSE_ENABLE  (RCC_BDCTRL_LSEEN)
#define RCC_LSE_BYPASS  (RCC_BDCTRL_LSEBP)

/** RTC_clock_source **/
#define RCC_RTCCLK_SRC_MASK        (~RCC_BDCTRL_RTCSEL)
#define RCC_RTCCLK_SRC_LSE         (RCC_BDCTRL_RTCSEL_LSE)
#define RCC_RTCCLK_SRC_LSI         (RCC_BDCTRL_RTCSEL_LSI)
#define RCC_RTCCLK_SRC_HSE_DIV128  (RCC_BDCTRL_RTCSEL_HSE)

#define RCC_LPTIM1CLK_SRC_MASK        (~RCC_BDCTRL_LPTIM1SEL)
#define RCC_LPTIM2CLK_SRC_MASK        (~RCC_BDCTRL_LPTIM2SEL)

#define RCC_LPTIMCLK_SRC_LSE         (RCC_BDCTRL_LPTIM1SEL_LSE)
#define RCC_LPTIMCLK_SRC_LSI         (RCC_BDCTRL_LPTIM1SEL_LSI)
#define RCC_LPTIMCLK_SRC_HSI         (RCC_BDCTRL_LPTIM1SEL_HSI)
#define RCC_LPTIMCLK_SRC_HSE         (RCC_BDCTRL_LPTIM1SEL_HSE)
#define RCC_LPTIMCLK_SRC_PCLK1       (RCC_BDCTRL_LPTIM1SEL_PCLK1)

#define RCC_LPTIM1_PERIPH_EN         (RCC_BDCTRL_LPTIM1EN)
#define RCC_LPTIM2_PERIPH_EN         (RCC_BDCTRL_LPTIM2EN)
#define RCC_LPTIM1_PERIPH_RST        (RCC_BDCTRL_LPTIM1RST)
#define RCC_LPTIM2_PERIPH_RST        (RCC_BDCTRL_LPTIM2RST)

#define RCC_BKUP_RESET           (RCC_BDCTRL_BDSFTRST)

/** RCC_CSSCTRL Config  **/
#define RCC_CSSFLAG_HSEPOF          (RCC_CSSCTRL_HSEPOF)
#define RCC_CSSFLAG_HSEFHF          (RCC_CSSCTRL_HSEFHF)
#define RCC_CSSFLAG_HSEFLF          (RCC_CSSCTRL_HSEFLF)
#define RCC_CSSEN_HSEPOEN           (RCC_CSSCTRL_HSEPOEN)
#define RCC_CSSEN_HSEFHEN           (RCC_CSSCTRL_HSEFHEN)
#define RCC_CSSEN_HSEFLEN           (RCC_CSSCTRL_HSEFLEN)
#define RCC_HSEPOTHR_MASK           (~RCC_CSSCTRL_HSEPOTHR)
#define RCC_HSEFHTHR_MASK           (~RCC_CSSCTRL_HSEFHTHR)
#define RCC_HSEFLTHR_MASK           (~RCC_CSSCTRL_HSEFLTHR)
/** AHB_peripheral **/
#define RCC_AHB_PERIPHEN_SHRTIM  (RCC_AHBPCLKEN_SHRTIMEN)
#define RCC_AHB_PERIPHEN_ATIM3   (RCC_AHBPCLKEN_ATIM3EN)
#define RCC_AHB_PERIPHEN_ATIM2   (RCC_AHBPCLKEN_ATIM2EN)
#define RCC_AHB_PERIPHEN_ATIM1   (RCC_AHBPCLKEN_ATIM1EN)
#define RCC_AHB_PERIPHEN_DVP     (RCC_AHBPCLKEN_DVPEN)
#define RCC_AHB_PERIPHEN_CORDIC  (RCC_AHBPCLKEN_CORDICEN)
#define RCC_AHB_PERIPHEN_FMAC    (RCC_AHBPCLKEN_FMACEN)
#define RCC_AHB_PERIPHEN_USBHS  (RCC_AHBPCLKEN_USBHSEN)
#define RCC_AHB_PERIPHEN_ETH     (RCC_AHBPCLKEN_ETHEN)
#define RCC_AHB_PERIPHEN_CRC     (RCC_AHBPCLKEN_CRCEN)
#define RCC_AHB_PERIPHEN_DMA2    (RCC_AHBPCLKEN_DMA2EN)
#define RCC_AHB_PERIPHEN_DMA1    (RCC_AHBPCLKEN_DMA1EN)
#define RCC_AHB_PERIPHEN_SDIO    (RCC_AHBPCLKEN_SDIOEN)
#define RCC_AHB_PERIPHEN_XSPI    (RCC_AHBPCLKEN_XSPIEN)
#define RCC_AHB_PERIPHEN_RNGC    (RCC_AHBPCLKEN_RNGCEN)
#define RCC_AHB_PERIPHEN_BKPSRAM (RCC_AHBPCLKEN_BKPSRAMEN)
#define RCC_AHB_PERIPHEN_FEMC    (RCC_AHBPCLKEN_FEMCEN)
#define RCC_AHB_PERIPHEN_FLITF   (RCC_AHBPCLKEN_FLITFEN)
#define RCC_AHB_PERIPHEN_SRAM    (RCC_AHBPCLKEN_SRAMEN)

#define RCC_AHB_PERIPHEN_SAC     (RCC_AHB1PCLKEN_SACEN )
#define RCC_AHB_PERIPHEN_DAC78    (RCC_AHB1PCLKEN_DAC78EN)
#define RCC_AHB_PERIPHEN_DAC56    (RCC_AHB1PCLKEN_DAC56EN)
#define RCC_AHB_PERIPHEN_ADC4    (RCC_AHB1PCLKEN_ADC4EN)
#define RCC_AHB_PERIPHEN_ADC3    (RCC_AHB1PCLKEN_ADC3EN)
#define RCC_AHB_PERIPHEN_ADC2    (RCC_AHB1PCLKEN_ADC2EN)
#define RCC_AHB_PERIPHEN_ADC1    (RCC_AHB1PCLKEN_ADC1EN)
#define RCC_AHB_PERIPHEN_GPIOH   (RCC_AHB1PCLKEN_IOPHEN)
#define RCC_AHB_PERIPHEN_GPIOG   (RCC_AHB1PCLKEN_IOPGEN)
#define RCC_AHB_PERIPHEN_GPIOF   (RCC_AHB1PCLKEN_IOPFEN)
#define RCC_AHB_PERIPHEN_GPIOE   (RCC_AHB1PCLKEN_IOPEEN)
#define RCC_AHB_PERIPHEN_GPIOD   (RCC_AHB1PCLKEN_IOPDEN)
#define RCC_AHB_PERIPHEN_GPIOC   (RCC_AHB1PCLKEN_IOPCEN)
#define RCC_AHB_PERIPHEN_GPIOB   (RCC_AHB1PCLKEN_IOPBEN)
#define RCC_AHB_PERIPHEN_GPIOA   (RCC_AHB1PCLKEN_IOPAEN)


#define RCC_AHB_PERIPHRST_ETH        (RCC_AHBPRST_ETHRST)
#define RCC_AHB_PERIPHRST_USBHS     (RCC_AHBPRST_USBHSRST)
#define RCC_AHB_PERIPHRST_FMAC       (RCC_AHBPRST_FMACRST)
#define RCC_AHB_PERIPHRST_CORDIC     (RCC_AHBPRST_CORDICRST)
#define RCC_AHB_PERIPHRST_ATIM3      (RCC_AHBPRST_ATIM3RST)
#define RCC_AHB_PERIPHRST_ATIM2      (RCC_AHBPRST_ATIM2RST)
#define RCC_AHB_PERIPHRST_ATIM1      (RCC_AHBPRST_ATIM1RST)
#define RCC_AHB_PERIPHRST_DVP        (RCC_AHBPRST_DVPRST)
#define RCC_AHB_PERIPHRST_DAC78      (RCC_AHBPRST_DAC78RST)
#define RCC_AHB_PERIPHRST_DAC56      (RCC_AHBPRST_DAC56RST)
#define RCC_AHB_PERIPHRST_ADC4       (RCC_AHBPRST_ADC4RST)
#define RCC_AHB_PERIPHRST_ADC3       (RCC_AHBPRST_ADC3RST)
#define RCC_AHB_PERIPHRST_ADC2       (RCC_AHBPRST_ADC2RST)
#define RCC_AHB_PERIPHRST_ADC1       (RCC_AHBPRST_ADC1RST)
#define RCC_AHB_PERIPHRST_GPIOH      (RCC_AHBPRST_IOPHRST)
#define RCC_AHB_PERIPHRST_GPIOG      (RCC_AHBPRST_IOPGRST)
#define RCC_AHB_PERIPHRST_GPIOF      (RCC_AHBPRST_IOPFRST)
#define RCC_AHB_PERIPHRST_GPIOE      (RCC_AHBPRST_IOPERST)
#define RCC_AHB_PERIPHRST_GPIOD      (RCC_AHBPRST_IOPDRST)
#define RCC_AHB_PERIPHRST_GPIOC      (RCC_AHBPRST_IOPCRST)
#define RCC_AHB_PERIPHRST_GPIOB      (RCC_AHBPRST_IOPBRST)
#define RCC_AHB_PERIPHRST_GPIOA      (RCC_AHBPRST_IOPARST)
#define RCC_AHB_PERIPHRST_FEMC       (RCC_AHBPRST_FEMCRST)
#define RCC_AHB_PERIPHRST_SDIO       (RCC_AHBPRST_SDIORST)
#define RCC_AHB_PERIPHRST_USBHSPHY  (RCC_AHBPRST_USBHSPHYRST)
#define RCC_AHB_PERIPHRST_XSPI       (RCC_AHBPRST_XSPIRST)
#define RCC_AHB_PERIPHRST_RNGC       (RCC_AHBPRST_RNGCRST)
#define RCC_AHB_PERIPHRST_SAC        (RCC_AHBPRST_SACRST)
#define RCC_AHB_PERIPHRST_SHRTPLLPHA (RCC_AHBPRST_SHRTPLLPHARST)
#define RCC_AHB_PERIPHRST_SHRTPLL    (RCC_AHBPRST_SHRTPLLRST)
#define RCC_AHB_PERIPHRST_SHRTIM     (RCC_AHBPRST_SHRTIMRST)

/** APB2_peripheral **/
#define RCC_APB2_PERIPH_USART4      (RCC_APB2PCLKEN_USART4EN) 
#define RCC_APB2_PERIPH_COMPFILT    (RCC_APB2PCLKEN_COMPFILTEN) 
#define RCC_APB2_PERIPH_PGA         (RCC_APB2PCLKEN_PGAEN) 
#define RCC_APB2_PERIPH_COMP        (RCC_APB2PCLKEN_COMPEN) 
#define RCC_APB2_PERIPH_GTIM10      (RCC_APB2PCLKEN_GTIM10EN) 
#define RCC_APB2_PERIPH_GTIM9       (RCC_APB2PCLKEN_GTIM9EN) 
#define RCC_APB2_PERIPH_GTIM8       (RCC_APB2PCLKEN_GTIM8EN) 
#define RCC_APB2_PERIPH_UART7       (RCC_APB2PCLKEN_UART7EN) 
#define RCC_APB2_PERIPH_UART6       (RCC_APB2PCLKEN_UART6EN) 
#define RCC_APB2_PERIPH_USART1      (RCC_APB2PCLKEN_USART1EN) 
#define RCC_APB2_PERIPH_SPI1        (RCC_APB2PCLKEN_SPI1EN)
#define RCC_APB2_PERIPH_SPI4        (RCC_APB2PCLKEN_SPI4EN)
#define RCC_APB2_PERIPH_SPI5        (RCC_APB2PCLKEN_SPI5EN) 
#define RCC_APB2_PERIPH_SPI6        (RCC_APB2PCLKEN_SPI6EN) 
#define RCC_APB2_PERIPH_AFIO        (RCC_APB2PCLKEN_AFIOEN) 

/** APB1_peripheral **/
#define RCC_APB1_PERIPH_DAC34   (RCC_APB1PCLKEN_DAC34EN)  
#define RCC_APB1_PERIPH_DAC12   (RCC_APB1PCLKEN_DAC12EN)  
#define RCC_APB1_PERIPH_WWDG    (RCC_APB1PCLKEN_WWDGEN)  
#define RCC_APB1_PERIPH_I2C4    (RCC_APB1PCLKEN_I2C4EN)
#define RCC_APB1_PERIPH_I2C3    (RCC_APB1PCLKEN_I2C3EN) 
#define RCC_APB1_PERIPH_BTIM2   (RCC_APB1PCLKEN_BTIM2EN)   
#define RCC_APB1_PERIPH_BTIM1   (RCC_APB1PCLKEN_BTIM1EN)  
#define RCC_APB1_PERIPH_FDCAN3  (RCC_APB1PCLKEN_FDCAN3EN)  
#define RCC_APB1_PERIPH_FDCAN2  (RCC_APB1PCLKEN_FDCAN2EN) 
#define RCC_APB1_PERIPH_FDCAN1  (RCC_APB1PCLKEN_FDCAN1EN) 
#define RCC_APB1_PERIPH_USBFS   (RCC_APB1PCLKEN_USBFSEN)
#define RCC_APB1_PERIPH_UCDR    (RCC_APB1PCLKEN_UCDREN)  
#define RCC_APB1_PERIPH_GTIM7   (RCC_APB1PCLKEN_GTIM7EN)  
#define RCC_APB1_PERIPH_GTIM6   (RCC_APB1PCLKEN_GTIM6EN)  
#define RCC_APB1_PERIPH_GTIM5   (RCC_APB1PCLKEN_GTIM5EN)
#define RCC_APB1_PERIPH_GTIM4   (RCC_APB1PCLKEN_GTIM4EN) 
#define RCC_APB1_PERIPH_GTIM3   (RCC_APB1PCLKEN_GTIM3EN) 
#define RCC_APB1_PERIPH_GTIM2   (RCC_APB1PCLKEN_GTIM2EN)   
#define RCC_APB1_PERIPH_GTIM1   (RCC_APB1PCLKEN_GTIM1EN)   
#define RCC_APB1_PERIPH_SPI3    (RCC_APB1PCLKEN_SPI3EN)   
#define RCC_APB1_PERIPH_SPI2    (RCC_APB1PCLKEN_SPI2EN)  
#define RCC_APB1_PERIPH_I2C2    (RCC_APB1PCLKEN_I2C2EN)  
#define RCC_APB1_PERIPH_I2C1    (RCC_APB1PCLKEN_I2C1EN) 
#define RCC_APB1_PERIPH_UART5   (RCC_APB1PCLKEN_UART5EN) 
#define RCC_APB1_PERIPH_UART8   (RCC_APB1PCLKEN_UART8EN)
#define RCC_APB1_PERIPH_USART3  (RCC_APB1PCLKEN_USART3EN)  
#define RCC_APB1_PERIPH_USART2  (RCC_APB1PCLKEN_USART2EN) 
#define RCC_APB1_PERIPH_BKP     (RCC_APB1PCLKEN_BKPEN) 
#define RCC_APB1_PERIPH_PWR     (RCC_APB1PCLKEN_PWREN)

#define RCC_OFFEN_FDCAN3        (RCC_APB1PCLKEN_FDCAN3OFFEN) 
#define RCC_OFFEN_FDCAN2        (RCC_APB1PCLKEN_FDCAN2OFFEN) 
#define RCC_OFFEN_FDCAN1        (RCC_APB1PCLKEN_FDCAN1OFFEN)

/** MCO_PLL_prescaler **/
#define RCC_MCO_PLLCLK_DIV_MASK  (~RCC_CFG_MCOPRES)
#define RCC_MCO_PLLCLK_DIV2      (RCC_CFG_MCOPRES_PLLDIV2)
#define RCC_MCO_PLLCLK_DIV3      (RCC_CFG_MCOPRES_PLLDIV3)
#define RCC_MCO_PLLCLK_DIV4      (RCC_CFG_MCOPRES_PLLDIV4)
#define RCC_MCO_PLLCLK_DIV5      (RCC_CFG_MCOPRES_PLLDIV5)
#define RCC_MCO_PLLCLK_DIV6      (RCC_CFG_MCOPRES_PLLDIV6)
#define RCC_MCO_PLLCLK_DIV7      (RCC_CFG_MCOPRES_PLLDIV7)
#define RCC_MCO_PLLCLK_DIV8      (RCC_CFG_MCOPRES_PLLDIV8)
#define RCC_MCO_PLLCLK_DIV9      (RCC_CFG_MCOPRES_PLLDIV9)
#define RCC_MCO_PLLCLK_DIV10     (RCC_CFG_MCOPRES_PLLDIV10)
#define RCC_MCO_PLLCLK_DIV11     (RCC_CFG_MCOPRES_PLLDIV11)
#define RCC_MCO_PLLCLK_DIV12     (RCC_CFG_MCOPRES_PLLDIV12)
#define RCC_MCO_PLLCLK_DIV13     (RCC_CFG_MCOPRES_PLLDIV13)
#define RCC_MCO_PLLCLK_DIV14     (RCC_CFG_MCOPRES_PLLDIV14)
#define RCC_MCO_PLLCLK_DIV15     (RCC_CFG_MCOPRES_PLLDIV15)

/** Clock_source_to_output_on_MCO_pin **/
#define RCC_MCO1_MCOCFG_MASK     (~RCC_MCOCFG_MCO1)
#define RCC_MCO2_MCOCFG_MASK     (~RCC_MCOCFG_MCO2)
#define RCC_MCO_CFG_MASK         (~RCC_CFG_MCOPLLSEL)
#define RCC_MCO_MCOCFG_PLL       (RCC_MCOCFG_MCO2_PLL)

#define RCC_MCO_NOCLK           (RCC_MCOCFG_MCO2_NOCLK)
#define RCC_MCO_SYSCLK          (RCC_MCOCFG_MCO2_SYSCLK)
#define RCC_MCO_HSI             (RCC_MCOCFG_MCO2_HSI)
#define RCC_MCO_HSE             (RCC_MCOCFG_MCO2_HSE)
#define RCC_MCO_PLL_PRES        (RCC_CFG_MCOPLLSEL_PLL|0x01)
#define RCC_MCO_SHRTPLL_PRES    (RCC_CFG_MCOPLLSEL_SHRTPLL|0x01)
#define RCC_MCO_USBHS240M_PRES (RCC_CFG_MCOPLLSEL_USBHS240M|0x01)
#define RCC_MCO_LSI             (RCC_MCOCFG_MCO2_LSI)
#define RCC_MCO_LSE             (RCC_MCOCFG_MCO2_LSE)

/** system remap **/
#define RCC_REMAP_MASK    (~RCC_BOOTREMAP_REMAPKEY)
#define RCC_REMAP_KEY     ((uint32_t)0x0000CC00)

#define RCC_REMAP_SEL_MASK  (~RCC_BOOTREMAP_REMAPSEL)
#define RCC_REMAP_SYS       (RCC_BOOTREMAP_REMAPSEL_SYS)
#define RCC_REMAP_BFLASH    (RCC_BOOTREMAP_REMAPSEL_BFLASH)
#define RCC_REMAP_AFLASH    (RCC_BOOTREMAP_REMAPSEL_AFLASH)
#define RCC_REMAP_SRAM      (RCC_BOOTREMAP_REMAPSEL_SRAM)
#define RCC_REMAP_FEMC      (RCC_BOOTREMAP_REMAPSEL_FEMC)
#define RCC_REMAP_XSPI      (RCC_BOOTREMAP_REMAPSEL_XSPI)

/** RCC_Flag **/
#define RCC_FLAG_MASK         ((uint8_t)0x1F)
#define RCC_FLAG_PLLRDF       ((uint8_t)0x21)
#define RCC_FLAG_HSIRDF       ((uint8_t)0x23) 
#define RCC_FLAG_HSERDF       ((uint8_t)0x25)
#define RCC_FLAG_RPINTF       ((uint8_t)0x4C)
#define RCC_FLAG_LSECSSF      ((uint8_t)0x7A)
#define RCC_FLAG_HSECSSF      ((uint8_t)0x7B)
#define RCC_FLAG_HSICSSF      ((uint8_t)0x7C)
#define RCC_FLAG_LSIRDF       ((uint8_t)0x81)
#define RCC_FLAG_BORRSTF      ((uint8_t)0x93)
#define RCC_FLAG_MAINEMCF     ((uint8_t)0x94)
#define RCC_FLAG_BKPEMCF      ((uint8_t)0x95)
#define RCC_FLAG_RAMERSTF     ((uint8_t)0x97)
#define RCC_FLAG_SMPURSTF      ((uint8_t)0x99)
#define RCC_FLAG_PINRSTF      ((uint8_t)0x9A)
#define RCC_FLAG_PORRSTF      ((uint8_t)0x9B)
#define RCC_FLAG_SFTRSTF      ((uint8_t)0x9C)
#define RCC_FLAG_IWDGRSTF     ((uint8_t)0x9D)
#define RCC_FLAG_WWDGRSTF     ((uint8_t)0x9E)
#define RCC_FLAG_LPWRRSTF     ((uint8_t)0x9F)
#define RCC_FLAG_LSERDF       ((uint8_t)0xA1)
#define RCC_FLAG_HSEFLF       ((uint8_t)0xD0)
#define RCC_FLAG_HSEFHF       ((uint8_t)0xD1)
#define RCC_FLAG_HSEPOF       ((uint8_t)0xD2)
#define RCC_FLAG_SHRTPLLRDF   ((uint8_t)0xFC)

/** RCC_Flag **/
#define RCC_REMOVE_RESET_FLAG (RCC_CTRLSTS_RMRSTF)

/** RCC_Interrupt_source **/
/** Interrupts Flag **/
#define RCC_INT_LSIRDIF    (RCC_CLKINT_LSIRDIF )
#define RCC_INT_LSERDIF    (RCC_CLKINT_LSERDIF )
#define RCC_INT_HSIRDIF    (RCC_CLKINT_HSIRDIF)
#define RCC_INT_HSERDIF    (RCC_CLKINT_HSERDIF)
#define RCC_INT_PLLRDIF    (RCC_CLKINT_PLLRDIF)
#define RCC_INT_LSECSSIF   (RCC_CLKINT_LSECSSIF)
#define RCC_INT_HSECSSIF   (RCC_CLKINT_HSECSSIF)
#define RCC_INT_HSICSSIF   (RCC_CLKINT_HSICSSIF)
#define RCC_INT_BORIF      (RCC_CLKINT_BORIF)

/** Interrupts Clear **/
#define RCC_CLR_LSIRDIF    (RCC_CLKINT_LSIRDICLR)
#define RCC_CLR_LSERDIF    (RCC_CLKINT_LSERDICLR)
#define RCC_CLR_HSIRDIF    (RCC_CLKINT_HSIRDICLR)
#define RCC_CLR_HSERDIF    (RCC_CLKINT_HSERDICLR)
#define RCC_CLR_PLLRDIF    (RCC_CLKINT_PLLRDICLR)
#define RCC_CLR_LSECSSIF   (RCC_CLKINT_LSECSSICLR)
#define RCC_CLR_HSECSSIF   (RCC_CLKINT_HSECSSICLR)
#define RCC_CLR_HSICSSIF   (RCC_CLKINT_HSICSSICLR)
#define RCC_CLR_BORIF      (RCC_CLKINT_BORICLR)
 

void RCC_DeInit(void);
void RCC_ConfigHse(uint32_t RCC_HSE);
void RCC_EnableHSEClockSecuritySystem(FunctionalState Cmd);
void RCC_EnableHSECSSChk(uint32_t Chk_type, FunctionalState Cmd);
void RCC_SetHSECSSPhaseOffsetLimit(uint8_t limit_value);
void RCC_SetHSECSSFrequencyHighLimit(uint8_t limit_value);
void RCC_SetHSECSSFrequencyLowLimit(uint8_t limit_value);
void RCC_SetHsiCalibValue(uint8_t calibration_value);
void RCC_EnableHsi(FunctionalState Cmd);
void RCC_EnableHSIClockSecuritySystem(FunctionalState Cmd);
void RCC_ConfigPll(uint32_t PLL_source, uint32_t  PLL_prescaler, uint32_t PLL_multiplication, uint32_t PLL_outdivider);
void RCC_EnablePll(FunctionalState Cmd);
ErrorStatus RCC_ConfigSHRTPll(uint32_t SHRTPLL_source, uint64_t fin, uint64_t fout, FunctionalState Cmd);
uint32_t RCC_GetSysclkSrc(void);  
void RCC_ConfigSysclk(uint32_t sysclk_source);
void RCC_ConfigHclk(uint32_t sysclk_div);
void RCC_ConfigPclk1(uint32_t hclk_div);
void RCC_ConfigPclk2(uint32_t hclk_div);
void RCC_ConfigInt(uint32_t Interrupt, FunctionalState Cmd);
void RCC_ConfigATimClk(uint32_t timer_clksrc);
void RCC_ConfigGTimClk(uint32_t timer_clksrc);
void RCC_ConfigI2S3Clk(uint32_t I2S_clksrc);
void RCC_ConfigI2S2Clk(uint32_t I2S_clksrc);
void RCC_ConfigRngcClk(uint32_t RNG_prescaler);
void RCC_ConfigTrng1mClk(uint32_t TRNG1M_clksrc, uint32_t TRNG1M_prescaler);
void RCC_EnableTrng1mClk(FunctionalState Cmd);
void RCC_EnableBORReset(FunctionalState Cmd);
void RCC_EnableSHRTPLLPHAReset(FunctionalState Cmd);
void RCC_ConfigFDCANPllClk(uint32_t FDCAN_prescaler);
void RCC_ConfigFDCANClksrc(uint32_t FDCAN_clksrc);
void RCC_ConfigTraceClk(uint32_t TRACE_prescaler);
void RCC_ConfigUSBPLLPresClk(uint32_t USBPLL_clksrc, uint32_t USBPLL_prescaler);
void RCC_ConfigUSBFSClk(uint32_t USBFS_clksrc);
void RCC_ConfigUSBHSClk(uint32_t USBHS_clksrc);
void RCC_ConfigUSBHSBandwidth(uint32_t USBHS_bw);
void RCC_ConfigUSBHSFrequency(uint32_t USBHS_freq);  
void RCC_ConfigAdc1mClk(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler);
void RCC_ConfigAdcPllClk(uint32_t ADC_PLLsource, uint32_t ADC_PLLprescaler, uint32_t ADC_PLLenable);
void RCC_ConfigAdcHclk(uint32_t ADC_hclk_prescaler);
void RCC_EnableLsi(FunctionalState Cmd);
void RCC_ConfigLse(uint32_t RCC_LSE);
void RCC_EnableLSEClockSecuritySystem(FunctionalState Cmd);
void RCC_ConfigRtcClk(uint32_t rtcclk_source);
void RCC_EnableRtcClk(FunctionalState Cmd);
void RCC_ConfigLPTIM1Clk(uint32_t clock_source);
void RCC_ConfigLPTIM2Clk(uint32_t clock_source);
void RCC_EnableLPTIMPeriphClk(uint32_t LPTIM_periph, FunctionalState Cmd);
void RCC_EnableLPTIMPeriphReset(uint32_t LPTIM_periph);
void RCC_EnableBackupReset(void);
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_clocks);
void RCC_EnableFDCANOffRequest(uint32_t FDCAN_sel, FunctionalState Cmd);
void RCC_EnableAHBPeriphClk(uint32_t AHB_periph, FunctionalState Cmd);
void RCC_EnableAHB1PeriphClk(uint32_t AHB_periph, FunctionalState Cmd);
void RCC_EnableAPB2PeriphClk(uint32_t APB2_periph, FunctionalState Cmd);
void RCC_EnableAPB1PeriphClk(uint32_t APB1_periph, FunctionalState Cmd);
void RCC_EnableAHBPeriphReset(uint32_t AHB_periph);
void RCC_EnableAPB2PeriphReset(uint32_t APB2_periph);
void RCC_EnableAPB1PeriphReset(uint32_t APB1_periph);
void RCC_ConfigMcoClkPre(uint32_t MCO_PLL_prescaler);
void RCC_ConfigMco1(uint32_t MCO_source);
void RCC_ConfigMco2(uint32_t MCO_source);
void RCC_EnableRemap(void);
void RCC_ConfigRemapMode(uint32_t Remap_mode);
void RCC_ClearResetFlag(void);
void RCC_ClrIntPendingBit(uint32_t interrupt_clear);
ErrorStatus RCC_WaitHseStable(void);
ErrorStatus RCC_WaitHsiStable(void);
ErrorStatus RCC_WaitLsiStable(void);
ErrorStatus RCC_WaitLseStable(void);
FlagStatus RCC_GetHSECSSStatus(uint32_t interrupt_flag);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_flag);
INTStatus RCC_GetIntStatus(uint32_t interrupt_flag);

#ifdef __cplusplus
}
#endif

#endif /* __N32H47X_48X_RCC_H */


