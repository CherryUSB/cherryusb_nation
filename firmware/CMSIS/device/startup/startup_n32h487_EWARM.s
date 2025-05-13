; *********************************************************************************************************
;     Copyright (c) 2023, Nations Technologies Inc.
; 
;     All rights reserved.
;
;     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
; referred to as NATIONS). This software, and the product of NATIONS described herein 
; (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
; of the People's Republic of China and other applicable jurisdictions worldwide.
;
;     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
; intellectual property rights. Names and brands of third party may be mentioned or referred 
; thereto (if any) for identification purposes only.
;
;     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
; improvements to this software at any time without notice. Please contact NATIONS and obtain 
; the latest version of this software before placing orders.

;     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
; no responsibility for the accuracy and reliability of this software.
; 
;     It is the responsibility of the user of this software to properly design, program, and test 
; the functionality and safety of any application made of this information and any resulting product. 
; In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
; consequential damages arising in any way out of the use of this software or the Product.
;
;     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
; malfunction or failure of which may cause loss of human life, bodily injury or severe property 
; damage. Such applications are deemed, "Insecure Usage".
;
;     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
; harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
; to any customer's Insecure Usage.

;     Any express or implied warranty with regard to this software or the Product, including,but not 
; limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
; are disclaimed to the fullest extent permitted by law.

;     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
; or otherwise distribute this software for any purposes, in whole or in part.
;
;     NATIONS products and technologies shall not be used for or incorporated into any products or systems
; whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
; User shall comply with any applicable export control laws and regulations promulgated and administered by 
; the governments of any countries asserting jurisdiction over the parties or transactions.
; ************************************************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

    MODULE  ?cstartup
        
        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit        
        PUBLIC  __vector_table

        DATA
       
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler              ; Reset Handler
        DCD     NMI_Handler                ; NMI Handler
        DCD     HardFault_Handler          ; Hard Fault Handler
        DCD     MemManage_Handler          ; MPU Fault Handler
        DCD     BusFault_Handler           ; Bus Fault Handler
        DCD     UsageFault_Handler         ; Usage Fault Handler
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     SVC_Handler                ; SVCall Handler
        DCD     DebugMon_Handler           ; Debug Monitor Handler
        DCD     0                          ; Reserved
        DCD     PendSV_Handler             ; PendSV Handler
        DCD     SysTick_Handler            ; SysTick Handler



        ; External Interrupts
        DCD  	WWDG_IRQHandler                  ;Window watchdog interrupt
        DCD  	PVD_IRQHandler                   ;PVD through EXTI Line16 detection interrupt
        DCD  	RTC_TAMPER_IRQHandler            ;RTC Tamper or LSE-CSS through EXTI Line19 interrupt
        DCD  	RTC_WKUP_IRQHandler              ;RTC Wakeup timer through EXTI line 20 interrupt
        DCD  	FLASH_IRQHandler                 ;Flash global interrupt
        DCD  	RCC_IRQHandler                   ;RCC global interrupt
        DCD  	EXTI0_IRQHandler                 ;EXTI Line0 interrupt
        DCD  	EXTI1_IRQHandler                 ;EXTI Line1 interrupt
        DCD  	EXTI2_IRQHandler                 ;EXTI Line2 interrupt
        DCD  	EXTI3_IRQHandler                 ;EXTI Line3 interrupt
        DCD  	EXTI4_IRQHandler                 ;EXTI Line4 interrupt
        DCD  	DMA1_Channel1_IRQHandler         ;DMA1 Channel1 global interrupt
        DCD  	DMA1_Channel2_IRQHandler         ;DMA1 Channel2 global interrupt
        DCD  	DMA1_Channel3_IRQHandler         ;DMA1 Channel3 global interrupt
        DCD  	DMA1_Channel4_IRQHandler         ;DMA1 Channel4 global interrupt
        DCD  	DMA1_Channel5_IRQHandler         ;DMA1 Channel5 global interrupt
        DCD  	DMA1_Channel6_IRQHandler         ;DMA1 Channel6 global interrupt
        DCD  	DMA1_Channel7_IRQHandler         ;DMA1 Channel7 global interrupt
        DCD  	ADC1_2_IRQHandler                ;ADC1 and ADC2 global interrupt
        DCD  	USB_FS_HP_IRQHandler             ;USB FS Device High Priority interrupts
        DCD  	USB_FS_LP_IRQHandler             ;USB FS Device Low Priority interrupts
        DCD  	FDCAN1_INT0_IRQHandler           ;FDCAN1 interrupt LINE 0
        DCD  	FDCAN1_INT1_IRQHandler           ;FDCAN1 interrupt LINE 1
        DCD  	EXTI9_5_IRQHandler               ;EXTI Line[9:5] interrupts
        DCD  	ATIM1_BRK_IRQHandler             ;ATIM1 Break interrupt
        DCD  	ATIM1_UP_IRQHandler              ;ATIM1 Update interrupt
        DCD  	ATIM1_TRG_COM_IRQHandler         ;ATIM1 Trigger and Commutation interrupt
        DCD  	ATIM1_CC_IRQHandler              ;ATIM1 Capture Compare interrupt
        DCD  	GTIM1_IRQHandler                 ;GTIM1 global interrupt
        DCD  	GTIM2_IRQHandler                 ;GTIM2 global interrupt
        DCD  	GTIM3_IRQHandler                 ;GTIM3 global interrupt
        DCD  	I2C1_EV_IRQHandler               ;I2C1 event interrupt
        DCD  	I2C1_ER_IRQHandler               ;I2C1 error interrupt
        DCD  	I2C2_EV_IRQHandler               ;I2C2 event interrupt
        DCD  	I2C2_ER_IRQHandler               ;I2C2 error interrupt
        DCD  	SPI1_IRQHandler                  ;SPI1 global interrupt
        DCD  	SPI2_I2S2_IRQHandler             ;SPI2/I2S2 global interrupt
        DCD  	USART1_IRQHandler                ;USART1 global interrupt
        DCD     USART2_IRQHandler                ;USART2 global interrupt
        DCD  	USART3_IRQHandler                ;USART3 global interrupt
        DCD  	EXTI15_10_IRQHandler             ;EXTI Line[15:10] interrupts
        DCD  	RTCAlarm_IRQHandler              ;RTC alarm through EXTI line17 interrupt
        DCD  	USB_FS_WKUP_IRQHandler           ;USB FS Device wakeup from suspend through EXTI line18 interrupt
        DCD  	ATIM2_BRK_IRQHandler             ;ATIM2 Break interrupt
        DCD  	ATIM2_UP_IRQHandler              ;ATIM2 Update interrupt
        DCD  	ATIM2_TRG_COM_IRQHandler         ;ATIM2 Trigger and Commutation interrupts
        DCD  	ATIM2_CC_IRQHandler              ;ATIM2 Capture Compare interrupt
        DCD  	ADC3_ADC4_IRQHandler             ;ADC3_ADC4 global interrupt
        DCD  	UCDR_IRQHandler                  ;UCDR error interrupt
        DCD  	SDIO_IRQHandler                  ;SDIO global interrupt
        DCD  	GTIM4_IRQHandler                 ;GTIM4 global interrupt
        DCD  	SPI3_I2S3_IRQHandler             ;SPI3/I2S3 global interrupt
        DCD  	USART4_IRQHandler                ;USART4 global interrupt
        DCD  	UART5_IRQHandler                 ;UART5 global interrupt
        DCD  	BTIM1_IRQHandler                 ;BTIM1 global interrupt
        DCD  	BTIM2_IRQHandler                 ;BTIM2 global interrupt
        DCD  	DMA2_Channel1_IRQHandler         ;DMA2 Channel1 global interrupt
        DCD  	DMA2_Channel2_IRQHandler         ;DMA2 Channel2 global interrupt
        DCD  	DMA2_Channel3_IRQHandler         ;DMA2 Channel3 global interrupt
        DCD  	DMA2_Channel4_IRQHandler         ;DMA2 Channel4 global interrupt
        DCD  	DMA2_Channel5_IRQHandler         ;DMA2 Channel5 global interrupt
        DCD  	SRAM_ERR_IRQHandler              ;SRAM ECC error
        DCD  	0                                ;Reserved
        DCD  	FDCAN2_INT0_IRQHandler           ;FDCAN2 interrupt 0
        DCD  	FDCAN2_INT1_IRQHandler           ;FDCAN2 interrupt 1
        DCD  	FDCAN3_INT0_IRQHandler           ;FDCAN3 interrupt 0
        DCD  	FDCAN3_INT1_IRQHandler           ;FDCAN3 interrupt 1
        DCD  	XSPI_IRQHandler                  ;XSPI global interrupt
        DCD  	DMA2_Channel6_IRQHandler         ;DMA2 Channel6 global interrupt
        DCD  	DMA2_Channel7_IRQHandler         ;DMA2 Channel7 global interrupt
        DCD  	I2C3_EV_IRQHandler               ;I2C3 event interrupt
        DCD  	I2C3_ER_IRQHandler               ;I2C3 error interrupt
        DCD  	I2C4_EV_IRQHandler               ;I2C4 event interrupt
        DCD  	I2C4_ER_IRQHandler               ;I2C4 error interrupt
        DCD  	UART6_IRQHandler                 ;UART6 global interrupt
        DCD  	UART7_IRQHandler                 ;UART7 global interrupt
        DCD  	DMA1_Channel8_IRQHandler         ;DMA1 Channel8 global interrupt
        DCD  	DMA2_Channel8_IRQHandler         ;DMA2 Channel8 global interrupt
        DCD  	DVP_IRQHandler                   ;DVP global interrupt
        DCD  	SAC_IRQHandler                   ;SAC global interrupt
        DCD  	SMPU_IRQHandler                  ;SMPU global interrupt
        DCD  	0                                ;Reserved 
        DCD  	USB_HS_EPx_OUT_IRQHandler        ;need check to user manual of exti chapter  USB HS End Point 1 Out global interrupt
        DCD  	USB_HS_EPx_IN_IRQHandler         ;need check to user manual of exti chapter  USB HS End Point 1 Inglobal interrupt
        DCD  	USB_HS_WKUP_IRQHandler           ;need check to user manual of exti chapter  USB HS wakeup from suspend through EXTI line23 interrupt
        DCD  	UART8_IRQHandler                 ;USART8 global interrupt
        DCD  	SPI4_IRQHandler                  ;SPI4 global interrupt
        DCD  	ETH_IRQHandler                   ;Ethernet global interrupt
        DCD  	ETH_WKUP_IRQHandler              ;Ethernet Wakeup through EXTI Line 27 interrupt
        DCD  	GTIM5_IRQHandler                 ;GTIM5 global interrupt
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	0                                ;Reserved
        DCD  	ATIM3_BRK_IRQHandler             ;ATIM3 Break interrupt
        DCD  	ATIM3_UP_IRQHandler              ;ATIM3 Update interrupt
        DCD  	ATIM3_TRG_COM_IRQHandler         ;ATIM3 Trigger and Commutation interrupts
        DCD  	ATIM3_CC_IRQHandler              ;ATIM3 Capture Compare interrupt
        DCD  	GTIM6_IRQHandler                 ;GTIM6 global interrupt
        DCD  	LPTIM1_WKUP_IRQHandler           ;LPTIM1 wakeup through EXTI Line 25 interrup interrupt
        DCD  	LPTIM2_WKUP_IRQHandler           ;LPTIM2 wakeup through EXTI Line 26 interrup interrupt
        DCD  	FMAC_IRQ_IRQHandler              ;FMAC global interrupt
        DCD  	Cordic_IRQ_IRQHandler            ;Cordic global interrupt
        DCD  	SPI5_IRQHandler                  ;SPI5 global interrupt
        DCD  	SPI6_IRQHandler                  ;SPI6 global interrupt
        DCD  	GTIM7_IRQHandler                 ;GTIM7 global interrupt
        DCD  	GTIM8_IRQHandler                 ;GTIM8 global interrupt
        DCD  	GTIM9_IRQHandler                 ;GTIM9 global interrupt
        DCD  	GTIM10_IRQHandler                ;GTIM10 global interrupt
        DCD  	DAC1_2_3_4_Underflow_IRQHandler  ;DAC1/2/3/4 underflow interrupt
        DCD  	DAC5_6_7_8_Underflow_IRQHandler  ;DAC5/6/7/8 underflow interrupt
        DCD  	USB_HS_IRQHandler                ;USB HS global interrupt 
        DCD  	FEMC_IRQHandler                  ;FEMC nand interrupt 
        ;need check to user manual of exti chapter 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK RTC_TAMPER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_TAMPER_IRQHandler
        B RTC_TAMPER_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel3_IRQHandler
        B DMA1_Channel3_IRQHandler

        PUBWEAK DMA1_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel4_IRQHandler
        B DMA1_Channel4_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler

        PUBWEAK ADC1_2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_2_IRQHandler
        B ADC1_2_IRQHandler

        PUBWEAK USB_FS_HP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_FS_HP_IRQHandler
        B USB_FS_HP_IRQHandler

        PUBWEAK USB_FS_LP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_FS_LP_IRQHandler
        B USB_FS_LP_IRQHandler

        PUBWEAK FDCAN1_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN1_INT0_IRQHandler
        B FDCAN1_INT0_IRQHandler

        PUBWEAK FDCAN1_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN1_INT1_IRQHandler
        B FDCAN1_INT1_IRQHandler

        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI9_5_IRQHandler
        B EXTI9_5_IRQHandler

        PUBWEAK ATIM1_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_BRK_IRQHandler
        B ATIM1_BRK_IRQHandler

        PUBWEAK ATIM1_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_UP_IRQHandler
        B ATIM1_UP_IRQHandler

        PUBWEAK ATIM1_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_TRG_COM_IRQHandler
        B ATIM1_TRG_COM_IRQHandler

        PUBWEAK ATIM1_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_CC_IRQHandler
        B ATIM1_CC_IRQHandler

        PUBWEAK GTIM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM1_IRQHandler
        B GTIM1_IRQHandler

        PUBWEAK GTIM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM2_IRQHandler
        B GTIM2_IRQHandler

        PUBWEAK GTIM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM3_IRQHandler
        B GTIM3_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler

        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_I2S2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_I2S2_IRQHandler
        B SPI2_I2S2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI15_10_IRQHandler
        B EXTI15_10_IRQHandler

        PUBWEAK RTCAlarm_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTCAlarm_IRQHandler
        B RTCAlarm_IRQHandler

        PUBWEAK USB_FS_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_FS_WKUP_IRQHandler
        B USB_FS_WKUP_IRQHandler

        PUBWEAK ATIM2_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_BRK_IRQHandler
        B ATIM2_BRK_IRQHandler

        PUBWEAK ATIM2_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_UP_IRQHandler
        B ATIM2_UP_IRQHandler

        PUBWEAK ATIM2_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_TRG_COM_IRQHandler
        B ATIM2_TRG_COM_IRQHandler

        PUBWEAK ATIM2_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_CC_IRQHandler
        B ATIM2_CC_IRQHandler

        PUBWEAK ADC3_ADC4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC3_ADC4_IRQHandler
        B ADC3_ADC4_IRQHandler

        PUBWEAK UCDR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UCDR_IRQHandler
        B UCDR_IRQHandler

        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_IRQHandler
        B SDIO_IRQHandler

        PUBWEAK GTIM4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM4_IRQHandler
        B GTIM4_IRQHandler

        PUBWEAK SPI3_I2S3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_I2S3_IRQHandler
        B SPI3_I2S3_IRQHandler

        PUBWEAK USART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART4_IRQHandler
        B USART4_IRQHandler

        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART5_IRQHandler
        B UART5_IRQHandler

        PUBWEAK BTIM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM1_IRQHandler
        B BTIM1_IRQHandler

        PUBWEAK BTIM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM2_IRQHandler
        B BTIM2_IRQHandler

        PUBWEAK DMA2_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel1_IRQHandler
        B DMA2_Channel1_IRQHandler

        PUBWEAK DMA2_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel2_IRQHandler
        B DMA2_Channel2_IRQHandler

        PUBWEAK DMA2_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel3_IRQHandler
        B DMA2_Channel3_IRQHandler

        PUBWEAK DMA2_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel4_IRQHandler
        B DMA2_Channel4_IRQHandler

        PUBWEAK DMA2_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel5_IRQHandler
        B DMA2_Channel5_IRQHandler

        PUBWEAK SRAM_ERR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SRAM_ERR_IRQHandler
        B SRAM_ERR_IRQHandler

        PUBWEAK FDCAN2_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN2_INT0_IRQHandler
        B FDCAN2_INT0_IRQHandler

        PUBWEAK FDCAN2_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN2_INT1_IRQHandler
        B FDCAN2_INT1_IRQHandler

        PUBWEAK FDCAN3_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN3_INT0_IRQHandler
        B FDCAN3_INT0_IRQHandler

        PUBWEAK FDCAN3_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN3_INT1_IRQHandler
        B FDCAN3_INT1_IRQHandler

        PUBWEAK XSPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
XSPI_IRQHandler
        B XSPI_IRQHandler

        PUBWEAK DMA2_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel6_IRQHandler
        B DMA2_Channel6_IRQHandler

        PUBWEAK DMA2_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel7_IRQHandler
        B DMA2_Channel7_IRQHandler

        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler

        PUBWEAK I2C4_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C4_EV_IRQHandler
        B I2C4_EV_IRQHandler

        PUBWEAK I2C4_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C4_ER_IRQHandler
        B I2C4_ER_IRQHandler

        PUBWEAK UART6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART6_IRQHandler
        B UART6_IRQHandler

        PUBWEAK UART7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART7_IRQHandler
        B UART7_IRQHandler

        PUBWEAK DMA1_Channel8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel8_IRQHandler
        B DMA1_Channel8_IRQHandler

        PUBWEAK DMA2_Channel8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel8_IRQHandler
        B DMA2_Channel8_IRQHandler

        PUBWEAK DVP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DVP_IRQHandler
        B DVP_IRQHandler

        PUBWEAK SAC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SAC_IRQHandler
        B SAC_IRQHandler

        PUBWEAK SMPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SMPU_IRQHandler
        B SMPU_IRQHandler

        PUBWEAK USB_HS_EPx_OUT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_HS_EPx_OUT_IRQHandler
        B USB_HS_EPx_OUT_IRQHandler

        PUBWEAK USB_HS_EPx_IN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_HS_EPx_IN_IRQHandler
        B USB_HS_EPx_IN_IRQHandler

        PUBWEAK USB_HS_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_HS_WKUP_IRQHandler
        B USB_HS_WKUP_IRQHandler

        PUBWEAK UART8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART8_IRQHandler
        B UART8_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI4_IRQHandler
        B SPI4_IRQHandler

        PUBWEAK ETH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH_IRQHandler
        B ETH_IRQHandler

        PUBWEAK ETH_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH_WKUP_IRQHandler
        B ETH_WKUP_IRQHandler

        PUBWEAK GTIM5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM5_IRQHandler
        B GTIM5_IRQHandler

        PUBWEAK ATIM3_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_BRK_IRQHandler
        B ATIM3_BRK_IRQHandler

        PUBWEAK ATIM3_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_UP_IRQHandler
        B ATIM3_UP_IRQHandler

        PUBWEAK ATIM3_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_TRG_COM_IRQHandler
        B ATIM3_TRG_COM_IRQHandler

        PUBWEAK ATIM3_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_CC_IRQHandler
        B ATIM3_CC_IRQHandler

        PUBWEAK GTIM6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM6_IRQHandler
        B GTIM6_IRQHandler

        PUBWEAK LPTIM1_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPTIM1_WKUP_IRQHandler
        B LPTIM1_WKUP_IRQHandler

        PUBWEAK LPTIM2_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPTIM2_WKUP_IRQHandler
        B LPTIM2_WKUP_IRQHandler

        PUBWEAK FMAC_IRQ_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FMAC_IRQ_IRQHandler
        B FMAC_IRQ_IRQHandler

        PUBWEAK Cordic_IRQ_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
Cordic_IRQ_IRQHandler
        B Cordic_IRQ_IRQHandler

        PUBWEAK SPI5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI5_IRQHandler
        B SPI5_IRQHandler

        PUBWEAK SPI6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI6_IRQHandler
        B SPI6_IRQHandler

        PUBWEAK GTIM7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM7_IRQHandler
        B GTIM7_IRQHandler

        PUBWEAK GTIM8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM8_IRQHandler
        B GTIM8_IRQHandler

        PUBWEAK GTIM9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM9_IRQHandler
        B GTIM9_IRQHandler

        PUBWEAK GTIM10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM10_IRQHandler
        B GTIM10_IRQHandler

        PUBWEAK DAC1_2_3_4_Underflow_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC1_2_3_4_Underflow_IRQHandler
        B DAC1_2_3_4_Underflow_IRQHandler

        PUBWEAK DAC5_6_7_8_Underflow_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC5_6_7_8_Underflow_IRQHandler
        B DAC5_6_7_8_Underflow_IRQHandler

        PUBWEAK USB_HS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_HS_IRQHandler
        B USB_HS_IRQHandler

        PUBWEAK FEMC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FEMC_IRQHandler
        B FEMC_IRQHandler

        END

