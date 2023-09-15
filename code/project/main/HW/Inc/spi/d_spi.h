#ifndef __D_SPI_H_
#define __D_SPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"

void spi_send_data(const uint8_t data);
void spi_send_cmd(const uint8_t cmd);
void screen_spi_init(void);
void screen_spi_test(void);

#endif