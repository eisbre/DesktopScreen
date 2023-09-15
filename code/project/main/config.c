#include "config.h"

void sleep_mode_init(void)
{
    set_tp_wackup_timeleft(SLEEP_TIME_RESET);
    while (true)
    {

        // ap&sta关闭、且当前在主页、且超过5min未触摸时才进入低功耗
        do
        {
            esp_task_wdt_reset();
            vTaskDelay(pdMS_TO_TICKS(1000));
            count_tp_wackup_timeleft();
            // printf("wait enter sleep mode run... %d\n", get_tp_wackup_timeleft());
            if (get_is_ap_sta_open() == false && ds_ui_get_now_show_page() == PAGE_TYPE_MEMU && get_tp_wackup_timeleft() == 0)
            {
                break;
            }
        } while (1);

        ds_touch_gpio_isr_remove();
        gpio_wakeup_enable(BUTTON_GPIO_NUM_DEFAULT, GPIO_INTR_LOW_LEVEL);
        /* Wake up in 60 seconds, or when button is pressed */
        esp_sleep_enable_timer_wakeup(60000000);
        esp_sleep_enable_gpio_wakeup();

        printf("Entering light sleep\n");

        /* Get timestamp before entering sleep */
        int64_t t_before_us = esp_timer_get_time();

        /* Enter sleep mode */
        esp_light_sleep_start();
        /* Execution continues here after wakeup */

        /* Get timestamp after waking up from sleep */
        int64_t t_after_us = esp_timer_get_time();
        /* Determine wake up reason */
        const char *wakeup_reason;
        uint32_t wackup_timeleft = 60;
        switch (esp_sleep_get_wakeup_cause())
        {
        case ESP_SLEEP_WAKEUP_TIMER:
            wakeup_reason = "timer";
            wackup_timeleft = 1;
            update_system_time_minute();
            break;
        case ESP_SLEEP_WAKEUP_GPIO:
            wakeup_reason = "pin";
            gpio_wakeup_disable(BUTTON_GPIO_NUM_DEFAULT);
            esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
            ds_touch_gpio_init();
            ds_touch_gpio_isr_add();
            reset_tp_action_manage();
            break;
        default:
            wakeup_reason = "other";
            gpio_wakeup_disable(BUTTON_GPIO_NUM_DEFAULT);
            esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
            ds_touch_gpio_init();
            ds_touch_gpio_isr_add();
            reset_tp_action_manage();
            break;
        }
        printf("Returned from light sleep, reason: %s, t=%lld ms, slept for %lld ms  wackup_timeleft=%d\n",
               wakeup_reason, t_after_us / 1000, (t_after_us - t_before_us) / 1000, wackup_timeleft);

        set_tp_wackup_timeleft(wackup_timeleft);
    }
}

void Init(void)
{
    ds_system_data_init();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    init_ft6336();
    init_screen_interface();

    ds_ui_timepage_init();
    ds_ui_page_manage_init();
    ds_ui_weather_init();
    ds_ui_wordpage_init();
    ds_ui_tomatopage_init();

    ds_timer_init();

    if (NVS_WIFI_INFO_HAS_SAVE == ds_nvs_read_wifi_info())
    {
        // 已经存储wifi联网信息
        ds_ui_page_manage_send_action(PAGE_TYPE_MEMU);
    }
    else
    {
        // 未存储wifi联网信息
        ds_ui_page_manage_send_action(PAGE_TYPE_SETTING);
    }

    //ds_wifi_ap_start();
    sleep_mode_init();
}