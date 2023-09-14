#ifndef __D_SPIFFS_H
#define __D_SPIFFS_H

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_spiffs.h"

esp_err_t init_spiffs(void);
void d_spiffs_deinit(void);
void d_spiffs_test(void);

#endif
