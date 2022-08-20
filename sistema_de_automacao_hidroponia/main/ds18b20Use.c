#include <stdio.h>
#include <inttypes.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"
#include "ds18b20.h"

void ds18b20Use(){
    ds18b20_requestTemperatures();
    float temp1 = ds18b20_getTempF((DeviceAddress *)tempSensors[0]);
    float temp2 = ds18b20_getTempF((DeviceAddress *)tempSensors[1]);
    float temp3 = ds18b20_getTempC((DeviceAddress *)tempSensors[0]);
    float temp4 = ds18b20_getTempC((DeviceAddress *)tempSensors[1]);
    printf("Temperatures: %0.1fF %0.1fF\n", temp1,temp2);
    printf("Temperatures: %0.1fC %0.1fC\n", temp3,temp4);

    float cTemp = ds18b20_get_temp();
    printf("Temperature: %0.1fC\n", cTemp);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}