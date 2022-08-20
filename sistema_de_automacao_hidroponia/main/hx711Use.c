#include <hx711.h>
#include <stdio.h>
#include <inttypes.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"


void hx711Use(){
    esp_err_t r = hx711_wait(&dev, 500);
    if (r != ESP_OK)
    {
        ESP_LOGE(TAG, "Device not found: %d (%s)\n", r, esp_err_to_name(r));
        continue;
    }

    int32_t data;
    r = hx711_read_average(&dev, 5, &data);
    if (r != ESP_OK)
    {
        ESP_LOGE(TAG, "Could not read data: %d (%s)\n", r, esp_err_to_name(r));
        continue;
    }

    ESP_LOGI(TAG, "Raw data: %" PRIi32, data);

    vTaskDelay(pdMS_TO_TICKS(500));
}