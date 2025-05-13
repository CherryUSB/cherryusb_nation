/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h47x_48x.h"
#include "misc.h"
#include "n32h47x_48x_gpio.h"
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_usart.h"
#include "n32h47x_48x_dma.h"
#include "n32h47x_48x_tim.h"

#include "bsp_config.h"

#define ARRAY_SIZE(array) \
    ((int)((sizeof(array) / sizeof((array)[0]))))

#define USB1  0
#define OTG_HS_ADDR 0x40040000


/** λ������ **/
/** ��λ����ַ+λ���ת���ɱ�����ַ */
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))

/** ��һ����ַת��Ϊһ��ָ�� */
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))

/** ��λ����������ַת����ָ�� */
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

/** IO�ڵ�ַӳ�� */
#define GPIOx_POD_Offset (0x30)
#define GPIOA_POD_Addr (GPIOA_BASE + GPIOx_POD_Offset)
#define GPIOB_POD_Addr (GPIOB_BASE + GPIOx_POD_Offset)
#define GPIOC_POD_Addr (GPIOC_BASE + GPIOx_POD_Offset)
#define GPIOD_POD_Addr (GPIOD_BASE + GPIOx_POD_Offset)

#define GPIOx_PID_Offset (0x2C)
#define GPIOA_PID_Addr (GPIOA_BASE + GPIOx_PID_Offset)
#define GPIOB_PID_Addr (GPIOB_BASE + GPIOx_PID_Offset)
#define GPIOC_PID_Addr (GPIOC_BASE + GPIOx_PID_Offset)
#define GPIOD_PID_Addr (GPIOD_BASE + GPIOx_PID_Offset)

    // IO�ڲ�����ֻ�Ե�һ��IO��
    // ȷ��n��ֵС��16
#define PAout(n) BIT_ADDR(GPIOA_POD_Addr, n) // ���
#define PBout(n) BIT_ADDR(GPIOB_POD_Addr, n) // ���
#define PCout(n) BIT_ADDR(GPIOC_POD_Addr, n) // ���
#define PDout(n) BIT_ADDR(GPIOD_POD_Addr, n) // ���

#define PAin(n) BIT_ADDR(GPIOA_PID_Addr, n) // ����
#define PBin(n) BIT_ADDR(GPIOB_PID_Addr, n) // ����
#define PCin(n) BIT_ADDR(GPIOC_PID_Addr, n) // ����
#define PDin(n) BIT_ADDR(GPIOD_PID_Addr, n) // ����

#define Px_OUT(GPIOx, n) BIT_ADDR((uint32_t)(&GPIOx->POD), n) // ���
#define Px_IN(GPIOx, n) BIT_ADDR((uint32_t)(&GPIOx->PID), n)  // ����

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
