#ifndef __BSP_CONFIG_H
#define __BSP_CONFIG_H

#include "main.h"
#include "log.h"
#include "n32h47x_48x_exti.h"
#include "systick.h"

void bsp_init(void);

void bsp_usbhs_config(void);
void usbhs_vbus_set_state(uint8_t state);
          

void app_usb_init(void);
void gpio_gtim1_dma_config(void);

#endif /* end of __BSP_CONFIG_H */
