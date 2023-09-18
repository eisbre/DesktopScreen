
idf_component_register(
                        SRCS 
                        "main.c"

                        "HW/Src/ds_system_data.c"

                        "HW/Src/net/ds_wifi_scan.c"
                        "HW/Src/net/ds_wifi_ap.c"
                        "HW/Src/net/ds_https_request.c"
                        "HW/Src/net/ds_http_server.c"
                        "HW/Src/net/ds_wifi_sta.c"
                        "HW/Src/net/ds_http_request.c"
                        "HW/Src/net/ds_wifi_ap_sta.c"
                        "HW/Src/net/ds_sntp.c"

                        "HW/Src/screen/ds_ft6336.c"
                        "HW/Src/screen/ds_screen.c"

                        "HW/Src/driver/ds_timer.c"
                        "HW/Src/driver/ds_gpio.c"
                        "HW/Src/driver/ds_i2c.c"
                        "HW/Src/driver/ds_nvs.c"
                        "HW/Src/driver/ds_spi.c"
                        "HW/Src/driver/ds_pwm.c"
                        "HW/Src/driver/ds_spiffs.c"

                        "HW/Src/ui/ds_ui_timepage.c"
                        "HW/Src/ui/ds_ui_page_manage.c"
                        "HW/Src/ui/ds_ui_mainpage.c"
                        "HW/Src/ui/ds_ui_weatherpage.c"
                        "HW/Src/ui/ds_ui_wordpage.c"
                        "HW/Src/ui/ds_ui_tomatopage.c"

                        "HW/Src/data/ds_data_weather.c"
                        "HW/Src/data/ds_data_num.c"
                        "HW/Src/data/ds_data_icon.c"
                        "HW/Src/data/ds_data_page.c"

                        "HW/Src/draw/ds_font.c"
                        "HW/Src/draw/ds_paint.c"

                        INCLUDE_DIRS 
                        "."
                        "HW/Inc"
                        "HW/Inc/draw"
                        "HW/Inc/data"
                        "HW/Inc/net"
                        "HW/Inc/driver"
                        "HW/Inc/ui"
                        "HW/Inc/screen"

                        EMBED_FILES 
                        "html/favicon.ico"
                        "html/setting.html"
                        EMBED_TXTFILES
                        "cert/server_root_cert.pem"
                        "cert/server_root_cert_bilibili.pem"
                        )
