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

void app_main(void)
{
    printf("app_main run\n");
    d_timer_init();

    init_spiffs();
    //d_spiffs_test();
    //d_spiffs_deinit();

    d_nvs_init();
    //d_nvs_save_wifi_info();
    //d_nvs_read_wifi_info();

    ds_gpio_init();
    ds_touch_gpio_init();
    ds_screen_gpio_init();
    while (1)
    {
        printf("app run \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        // 喂狗
        esp_task_wdt_reset(); // Comment this line to trigger a TWDT timeout
    }
    esp_task_wdt_delete(NULL);
}
