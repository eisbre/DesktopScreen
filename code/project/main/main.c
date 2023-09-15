#include "config.h"

void app_main(void)
{
    Init();
    
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        // 喂狗
        esp_task_wdt_reset(); // Comment this line to trigger a TWDT timeout
    }
    esp_task_wdt_delete(NULL);
}
