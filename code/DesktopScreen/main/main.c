#include "main.h"

static void sleep_mode_init(void);
static void background_task(void *arg);

void app_main(void)
{
    //系统数据初始化
    ds_system_data_init();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    //http请求初始化
    ds_http_request_init();
    ds_http_server_init();
    //ap&sta模式初始化
    ds_wifi_ap_sta_init();   

    // //屏幕、TP外设初始化相关
    init_ft6336();
    init_screen_interface();
    //屏幕显示数据初始化
    ds_ui_page_manage_init();
    ds_ui_timepage_init();
    ds_ui_weather_init();
    ds_ui_wordpage_init();
    ds_ui_tomatopage_init();
    //定时器初始化
    ds_timer_init();
    //PWM蜂鸣器初始化
    ds_pwm_init();

    //默认Wifi账号密码设置
    // char *ssid="leo";
    // char *psw="123456789";
    // ds_nvs_save_wifi_info(ssid,psw);
    if(NVS_WIFI_INFO_HAS_SAVE == ds_nvs_read_wifi_info()){
        //已经存储wifi联网信息
        ds_ui_page_manage_send_action(PAGE_TYPE_MEMU);
    }else{
        //未存储wifi联网信息
        ds_ui_page_manage_send_action(PAGE_TYPE_SETTING);
    }

    //启动AP&STA模式
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    ds_wifi_send_event(AP_STA_START);
    xTaskCreate(background_task, "background_task", 4096, NULL, 10, NULL); 
    
    //进入低功耗模式
    sleep_mode_init();

    while(1)
    {
        printf("app run \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //喂狗
        esp_task_wdt_reset();  //Comment this line to trigger a TWDT timeout
    }
    esp_task_wdt_delete(NULL);
}

static void sleep_mode_init(void)
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
            printf("wait enter sleep mode run... %d\n", get_tp_wackup_timeleft());
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

static void background_task(void *arg)
{
    int apsta_close_count = 0;
    for (;;)
    {
        printf("background_task run... \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        // 首次更新
        if (has_first_time_httpdata_request() == true && get_wifi_sta_status() == WIFI_STA_MODE_CONNECT_SUCCESS)
        {
            ds_http_request_all();
            initialize_sntp();
            set_has_first_time_httpdata_request();
        }
        // 下拉请求更新
        if (has_update_httpdata_request() == true)
        {
            if (get_is_ap_sta_open())
            {
                if (get_wifi_sta_status() == WIFI_STA_MODE_CONNECT_SUCCESS)
                {
                    ds_http_request_all();
                    initialize_sntp();
                    set_update_httpdata_request(false);
                }
            }
            else
            {
                ds_wifi_send_event(AP_STA_START);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }
        // 关闭wifi AP&STA 计时
        if (get_is_ap_sta_open() == true && apsta_close_count == 0)
        {
            // 重置10min计时
            apsta_close_count = (SLEEP_TIME_RESET - 10);
        }
        if (apsta_close_count > 0)
        {
            apsta_close_count--;
            if (apsta_close_count == 0)
            {
                ds_wifi_send_event(AP_STA_STOP);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                set_update_httpdata_request(false);
            }
        }
        // 设置页面 开启AP&STA
        if (ds_ui_get_now_show_page() == PAGE_TYPE_SETTING)
        {
            if (get_is_ap_sta_open() == false)
            {
                ds_wifi_send_event(AP_STA_START);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }
    }
}
