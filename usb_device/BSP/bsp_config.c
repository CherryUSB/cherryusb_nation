#include "bsp_config.h"

static void bsp_gpio_config(void);

void bsp_init(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  log_init();
  log_info("bsp init");

  bsp_gpio_config();
}

void bsp_gpio_config(void)
{
  GPIO_InitType GPIO_InitStructure;

  RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB, ENABLE);
  RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOE, ENABLE);
  RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
  GPIO_ConfigPinRemap(0, 0, GPIO_RMP_SWJ_SWD);

  // LED
  GPIO_InitStruct(&GPIO_InitStructure);
  GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_8;
  GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
  GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
  GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
  GPIO_InitStructure.GPIO_Current = GPIO_DS_8mA;
  GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.Pin = GPIO_PIN_4;
  GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

void usbhs_vbus_set_state(uint8_t state)
{
  if(state)
	{
	  GPIO_SetBits(GPIOE,GPIO_PIN_1);  //EVB
		GPIO_SetBits(GPIOB,GPIO_PIN_3);  //STB
	}
	else
	{
	  GPIO_ResetBits(GPIOE,GPIO_PIN_1);  //EVB
		GPIO_ResetBits(GPIOB,GPIO_PIN_3);  //STB
	}
}
