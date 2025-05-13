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

Stack_Size      EQU     0x0001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp
                                                  
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size




__Vectors       DCD     __initial_sp               ; Top of Stack
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
                DCD  	0                                ; Reserved
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
                DCD  	COMP4_5_6_IRQHandler             ;COMP4&COMP5&COMP6 through EXTI Line22/30/31 interrupt
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
                DCD  	0                                ; Reserved
                DCD  	SAC_IRQHandler                   ;SAC global interrupt
                DCD  	SMPU_IRQHandler                  ;SMPU global interrupt
                DCD  	COMP1_2_3_IRQHandler             ;COMP1 & COMP2 & COMP3 through EXTI Line21/28/29 interrupt  
                DCD  	0                                ; Reserved
                DCD  	0                                ; Reserved
                DCD  	0                                ; Reserved
                DCD  	UART8_IRQHandler                 ;USART8 global interrupt
                DCD  	SPI4_IRQHandler                  ;SPI4 global interrupt
                DCD  	0                                ; Reserved
                DCD  	0                                ; Reserved
                DCD  	GTIM5_IRQHandler                 ;GTIM5 global interrupt
                DCD  	COMP7_IRQHandler                 ;COMP7 through EXTI Line24 interrupt
                DCD  	SHRT1_MST_IRQHandler             ;SHRTIM1 master interrupt
                DCD  	SHRT1_TIMA_IRQHandler            ;SHRTIM1 timer A interrupt
                DCD  	SHRT1_TIMB_IRQHandler            ;SHRTIM1 Timer B interrupt
                DCD  	SHRT1_TIMC_IRQHandler            ;SHRTIM1 timer C interrupt
                DCD  	SHRT1_TIMD_IRQHandler            ;SHRTIM1 timer D interrupt
                DCD  	SHRT1_TIME_IRQHandler            ;SHRTIM1 Timer E interrupt
                DCD  	SHRT1_TIMF_IRQHandler            ;SHRTIM1 timer F interrupt
                DCD  	SHRT1_FLT_IRQHandler             ;SHRTIM1 fault  interrupt
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
                DCD  	0                                ; Reserved
                DCD  	FEMC_IRQHandler                  ;FEMC nand interrupt 
                ;need check to user manual of exti chapter 


__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY
                
; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0               
                LDR     R0, =__main
                BX      R0
                ENDP
                
; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  	WWDG_IRQHandler                  [WEAK]
                EXPORT  	PVD_IRQHandler                   [WEAK]
                EXPORT  	RTC_TAMPER_IRQHandler            [WEAK]
                EXPORT  	RTC_WKUP_IRQHandler              [WEAK]
                EXPORT  	FLASH_IRQHandler                 [WEAK]
                EXPORT  	RCC_IRQHandler                   [WEAK]
                EXPORT  	EXTI0_IRQHandler                 [WEAK]
                EXPORT  	EXTI1_IRQHandler                 [WEAK]
                EXPORT  	EXTI2_IRQHandler                 [WEAK]
                EXPORT  	EXTI3_IRQHandler                 [WEAK]
                EXPORT  	EXTI4_IRQHandler                 [WEAK]
                EXPORT  	DMA1_Channel1_IRQHandler         [WEAK]
                EXPORT  	DMA1_Channel2_IRQHandler         [WEAK]
                EXPORT  	DMA1_Channel3_IRQHandler         [WEAK]
                EXPORT  	DMA1_Channel4_IRQHandler         [WEAK]
                EXPORT  	DMA1_Channel5_IRQHandler         [WEAK]
                EXPORT  	DMA1_Channel6_IRQHandler         [WEAK]
                EXPORT  	DMA1_Channel7_IRQHandler         [WEAK]
                EXPORT  	ADC1_2_IRQHandler                [WEAK]
                EXPORT  	USB_FS_HP_IRQHandler             [WEAK]
                EXPORT  	USB_FS_LP_IRQHandler             [WEAK]
                EXPORT  	FDCAN1_INT0_IRQHandler           [WEAK]
                EXPORT  	FDCAN1_INT1_IRQHandler           [WEAK]
                EXPORT  	EXTI9_5_IRQHandler               [WEAK]
                EXPORT  	ATIM1_BRK_IRQHandler             [WEAK]
                EXPORT  	ATIM1_UP_IRQHandler              [WEAK]
                EXPORT  	ATIM1_TRG_COM_IRQHandler         [WEAK]
                EXPORT  	ATIM1_CC_IRQHandler              [WEAK]
                EXPORT  	GTIM1_IRQHandler                 [WEAK]
                EXPORT  	GTIM2_IRQHandler                 [WEAK]
                EXPORT  	GTIM3_IRQHandler                 [WEAK]
                EXPORT  	I2C1_EV_IRQHandler               [WEAK]
                EXPORT  	I2C1_ER_IRQHandler               [WEAK]
                EXPORT  	I2C2_EV_IRQHandler               [WEAK]
                EXPORT  	I2C2_ER_IRQHandler               [WEAK]
                EXPORT  	SPI1_IRQHandler                  [WEAK]
                EXPORT  	SPI2_I2S2_IRQHandler             [WEAK]
                EXPORT  	USART1_IRQHandler                [WEAK]
                EXPORT      USART2_IRQHandler                [WEAK]
                EXPORT  	USART3_IRQHandler                [WEAK]
                EXPORT  	EXTI15_10_IRQHandler             [WEAK]
                EXPORT  	RTCAlarm_IRQHandler              [WEAK]
                EXPORT  	USB_FS_WKUP_IRQHandler           [WEAK]
                EXPORT  	ATIM2_BRK_IRQHandler             [WEAK]
                EXPORT  	ATIM2_UP_IRQHandler              [WEAK]
                EXPORT  	ATIM2_TRG_COM_IRQHandler         [WEAK]
                EXPORT  	ATIM2_CC_IRQHandler              [WEAK]
                EXPORT  	ADC3_ADC4_IRQHandler             [WEAK]
                EXPORT  	UCDR_IRQHandler                  [WEAK]
                EXPORT  	GTIM4_IRQHandler                 [WEAK]
                EXPORT  	SPI3_I2S3_IRQHandler             [WEAK]
                EXPORT  	USART4_IRQHandler                [WEAK]
                EXPORT  	UART5_IRQHandler                 [WEAK]
                EXPORT  	BTIM1_IRQHandler                 [WEAK]
                EXPORT  	BTIM2_IRQHandler                 [WEAK]
                EXPORT  	DMA2_Channel1_IRQHandler         [WEAK]
                EXPORT  	DMA2_Channel2_IRQHandler         [WEAK]
                EXPORT  	DMA2_Channel3_IRQHandler         [WEAK]
                EXPORT  	DMA2_Channel4_IRQHandler         [WEAK]
                EXPORT  	DMA2_Channel5_IRQHandler         [WEAK]
                EXPORT  	SRAM_ERR_IRQHandler              [WEAK]
                EXPORT  	COMP4_5_6_IRQHandler             [WEAK]
                EXPORT  	FDCAN2_INT0_IRQHandler           [WEAK]
                EXPORT  	FDCAN2_INT1_IRQHandler           [WEAK]
                EXPORT  	FDCAN3_INT0_IRQHandler           [WEAK]
                EXPORT  	FDCAN3_INT1_IRQHandler           [WEAK]
                EXPORT  	XSPI_IRQHandler                  [WEAK]
                EXPORT  	DMA2_Channel6_IRQHandler         [WEAK]
                EXPORT  	DMA2_Channel7_IRQHandler         [WEAK]
                EXPORT  	I2C3_EV_IRQHandler               [WEAK]
                EXPORT  	I2C3_ER_IRQHandler               [WEAK]
                EXPORT  	I2C4_EV_IRQHandler               [WEAK]
                EXPORT  	I2C4_ER_IRQHandler               [WEAK]
                EXPORT  	UART6_IRQHandler                 [WEAK]
                EXPORT  	UART7_IRQHandler                 [WEAK]
                EXPORT  	DMA1_Channel8_IRQHandler         [WEAK]
                EXPORT  	DMA2_Channel8_IRQHandler         [WEAK]
                EXPORT  	SAC_IRQHandler                   [WEAK]
                EXPORT  	SMPU_IRQHandler                  [WEAK]
                EXPORT  	COMP1_2_3_IRQHandler             [WEAK]
                EXPORT  	UART8_IRQHandler                 [WEAK]
                EXPORT  	SPI4_IRQHandler                  [WEAK]
                EXPORT  	GTIM5_IRQHandler                 [WEAK]
                EXPORT  	COMP7_IRQHandler                 [WEAK]
                EXPORT  	SHRT1_MST_IRQHandler             [WEAK]
                EXPORT  	SHRT1_TIMA_IRQHandler            [WEAK]
                EXPORT  	SHRT1_TIMB_IRQHandler            [WEAK]
                EXPORT  	SHRT1_TIMC_IRQHandler            [WEAK]
                EXPORT  	SHRT1_TIMD_IRQHandler            [WEAK]
                EXPORT  	SHRT1_TIME_IRQHandler            [WEAK]
                EXPORT  	SHRT1_TIMF_IRQHandler            [WEAK]
                EXPORT  	SHRT1_FLT_IRQHandler             [WEAK]
                EXPORT  	ATIM3_BRK_IRQHandler             [WEAK]
                EXPORT  	ATIM3_UP_IRQHandler              [WEAK]
                EXPORT  	ATIM3_TRG_COM_IRQHandler         [WEAK]
                EXPORT  	ATIM3_CC_IRQHandler              [WEAK]
                EXPORT  	GTIM6_IRQHandler                 [WEAK]
                EXPORT  	LPTIM1_WKUP_IRQHandler           [WEAK]
                EXPORT  	LPTIM2_WKUP_IRQHandler           [WEAK]
                EXPORT  	FMAC_IRQ_IRQHandler              [WEAK]
                EXPORT  	Cordic_IRQ_IRQHandler            [WEAK]
                EXPORT  	SPI5_IRQHandler                  [WEAK]
                EXPORT  	SPI6_IRQHandler                  [WEAK]
                EXPORT  	GTIM7_IRQHandler                 [WEAK]
                EXPORT  	GTIM8_IRQHandler                 [WEAK]
                EXPORT  	GTIM9_IRQHandler                 [WEAK]
                EXPORT  	GTIM10_IRQHandler                [WEAK]
                EXPORT  	DAC1_2_3_4_Underflow_IRQHandler  [WEAK]
                EXPORT  	DAC5_6_7_8_Underflow_IRQHandler  [WEAK]
                EXPORT  	FEMC_IRQHandler                  [WEAK]       
WWDG_IRQHandler                  
PVD_IRQHandler                   
RTC_TAMPER_IRQHandler            
RTC_WKUP_IRQHandler              
FLASH_IRQHandler                 
RCC_IRQHandler                   
EXTI0_IRQHandler                 
EXTI1_IRQHandler                 
EXTI2_IRQHandler                 
EXTI3_IRQHandler                 
EXTI4_IRQHandler                 
DMA1_Channel1_IRQHandler         
DMA1_Channel2_IRQHandler         
DMA1_Channel3_IRQHandler         
DMA1_Channel4_IRQHandler         
DMA1_Channel5_IRQHandler         
DMA1_Channel6_IRQHandler         
DMA1_Channel7_IRQHandler         
ADC1_2_IRQHandler                
USB_FS_HP_IRQHandler             
USB_FS_LP_IRQHandler             
FDCAN1_INT0_IRQHandler             
FDCAN1_INT1_IRQHandler             
EXTI9_5_IRQHandler               
ATIM1_BRK_IRQHandler             
ATIM1_UP_IRQHandler              
ATIM1_TRG_COM_IRQHandler         
ATIM1_CC_IRQHandler              
GTIM1_IRQHandler                 
GTIM2_IRQHandler                 
GTIM3_IRQHandler                 
I2C1_EV_IRQHandler               
I2C1_ER_IRQHandler               
I2C2_EV_IRQHandler               
I2C2_ER_IRQHandler               
SPI1_IRQHandler                  
SPI2_I2S2_IRQHandler             
USART1_IRQHandler                
USART2_IRQHandler                
USART3_IRQHandler                
EXTI15_10_IRQHandler             
RTCAlarm_IRQHandler              
USB_FS_WKUP_IRQHandler           
ATIM2_BRK_IRQHandler             
ATIM2_UP_IRQHandler              
ATIM2_TRG_COM_IRQHandler         
ATIM2_CC_IRQHandler              
ADC3_ADC4_IRQHandler             
UCDR_IRQHandler                  
GTIM4_IRQHandler                 
SPI3_I2S3_IRQHandler             
USART4_IRQHandler                
UART5_IRQHandler                 
BTIM1_IRQHandler                 
BTIM2_IRQHandler                 
DMA2_Channel1_IRQHandler         
DMA2_Channel2_IRQHandler         
DMA2_Channel3_IRQHandler         
DMA2_Channel4_IRQHandler         
DMA2_Channel5_IRQHandler         
SRAM_ERR_IRQHandler              
COMP4_5_6_IRQHandler             
FDCAN2_INT0_IRQHandler             
FDCAN2_INT1_IRQHandler             
FDCAN3_INT0_IRQHandler             
FDCAN3_INT1_IRQHandler             
XSPI_IRQHandler                  
DMA2_Channel6_IRQHandler         
DMA2_Channel7_IRQHandler         
I2C3_EV_IRQHandler               
I2C3_ER_IRQHandler               
I2C4_EV_IRQHandler               
I2C4_ER_IRQHandler               
UART6_IRQHandler                 
UART7_IRQHandler                 
DMA1_Channel8_IRQHandler         
DMA2_Channel8_IRQHandler         
SAC_IRQHandler                   
SMPU_IRQHandler                  
COMP1_2_3_IRQHandler             
UART8_IRQHandler                 
SPI4_IRQHandler                  
GTIM5_IRQHandler                 
COMP7_IRQHandler                 
SHRT1_MST_IRQHandler             
SHRT1_TIMA_IRQHandler            
SHRT1_TIMB_IRQHandler            
SHRT1_TIMC_IRQHandler            
SHRT1_TIMD_IRQHandler            
SHRT1_TIME_IRQHandler            
SHRT1_TIMF_IRQHandler            
SHRT1_FLT_IRQHandler             
ATIM3_BRK_IRQHandler             
ATIM3_UP_IRQHandler              
ATIM3_TRG_COM_IRQHandler         
ATIM3_CC_IRQHandler              
GTIM6_IRQHandler                 
LPTIM1_WKUP_IRQHandler           
LPTIM2_WKUP_IRQHandler           
FMAC_IRQ_IRQHandler              
Cordic_IRQ_IRQHandler            
SPI5_IRQHandler                  
SPI6_IRQHandler                  
GTIM7_IRQHandler                 
GTIM8_IRQHandler                 
GTIM9_IRQHandler                 
GTIM10_IRQHandler                
DAC1_2_3_4_Underflow_IRQHandler  
DAC5_6_7_8_Underflow_IRQHandler  
FEMC_IRQHandler
                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

