#ifndef __MAIN_H
#define __MAIN_H

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

#include "ds_system_data.h"

#include "./HW/Inc/net/ds_wifi_scan.h"
#include "./HW/Inc/net/ds_http_server.h"
#include "./HW/Inc/net/ds_https_request.h"
#include "./HW/Inc/net/ds_http_request.h"
#include "./HW/Inc/net/ds_wifi_ap_sta.h"
#include "./HW/Inc/net/ds_wifi_ap.h"
#include "./HW/Inc/net/ds_wifi_sta.h"
#include "./HW/Inc/net/ds_sntp.h"

#include "./HW/Inc/screen/ds_ft6336.h"
#include "./HW/Inc/screen/ds_screen.h"

#include "./HW/Inc/driver/ds_spi.h"
#include "./HW/Inc/driver/ds_nvs.h"
#include "./HW/Inc/driver/ds_timer.h"
#include "./HW/Inc/driver/ds_spiffs.h"
#include "./HW/Inc/driver/ds_pwm.h"
#include "./HW/Inc/driver/ds_gpio.h"

#include "./HW/Inc/ui/ds_ui_timepage.h"
#include "./HW/Inc/ui/ds_ui_page_manage.h"
#include "./HW/Inc/ui/ds_ui_weatherpage.h"
#include "./HW/Inc/ui/ds_ui_wordpage.h"
#include "./HW/Inc/ui/ds_ui_tomatopage.h"

#include "./HW/Inc/draw/ds_font.h"
#include "./HW/Inc/draw/ds_paint.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif

#define BUTTON_GPIO_NUM_DEFAULT 4
#define TWDT_TIMEOUT_S 3
#define SLEEP_TIME_RESET 600

#endif
