#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include "esp_event.h"

#include "driver/gpio.h"
#include "esp_sleep.h"
#include <time.h>
#include <sys/time.h>
#include "esp_timer.h"
#include "esp_task_wdt.h"

#include "./HW/Inc/timer/d_timer.h"
#include "./HW/Inc/spiffs/d_spiffs.h"
#include "./HW/Inc/nvs/d_nvs.h"
#include "./HW/Inc/d_system_data.h"
#include "./HW/Inc/gpio/d_gpio.h"
#include "./HW/Inc/i2c/d_i2c.h"
#include "./HW/Inc/screen/d_ft6336.h"
#include "./HW/Inc/spi/d_spi.h"
#include "./HW/Inc/screen/d_screen.h"
#include "./HW/Inc/ui/ds_ui_timepage.h"
#include "./HW/Inc/ui/ds_ui_page_manage.h"
#include "./HW/Inc/ui/ds_ui_weatherpage.h"
#include "./HW/Inc/ui/ds_ui_wordpage.h"
#include "./HW/Inc/ui/ds_ui_tomatopage.h"

#include "./HW/Inc/net/ds_wifi_ap.h"

#include "./HW/Inc/data/ds_data_page.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif

#define BUTTON_GPIO_NUM_DEFAULT 4
#define TWDT_TIMEOUT_S 3
#define SLEEP_TIME_RESET 600

void sleep_mode_init(void);
void Init(void);

#endif
