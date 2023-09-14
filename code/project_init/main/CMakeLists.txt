idf_component_register(
                    SRCS "main.c"
                    "HW/Src/timer/d_timer.c"
                    "HW/Src/spiffs/d_spiffs.c"
                    "HW/Src/nvs/d_nvs.c"
                    "HW/Src/d_system_data.c"
                    "HW/Src/gpio/d_gpio.c"

                    INCLUDE_DIRS "."
                    "HW/Inc/timer"
                    "HW/Inc/spiffs"
                    "HW/Inc/nvs"
                    "HW/Inc/gpio"
                    )
