#include <inttypes.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <hx711.h>
#include <stdio.h>
#include "ds18b20.h"
#include "driver/gpio.h"

static const char *TAG = "hx711-example";

#define TEMP_BUS 26
#define LED 2
#define HIGH 1
#define LOW 0
#define digitalWrite gpio_set_level

DeviceAddress tempSensors[2];

void getTempAddresses(DeviceAddress *tempSensorAddresses) {
	unsigned int numberFound = 0;
	reset_search();
	// search for 2 addresses on the oneWire protocol
	while (search(tempSensorAddresses[numberFound],true)) {
		numberFound++;
		if (numberFound == 2) break;
	}
	// if 2 addresses aren't found then flash the LED rapidly
	while (numberFound != 2) {
		numberFound = 1;
		digitalWrite(LED, HIGH);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		digitalWrite(LED, LOW);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		// search in the loop for the temp sensors as they may hook them up
		reset_search();
		while (search(tempSensorAddresses[numberFound],true)) {
			numberFound++;
			if (numberFound == 2) break;
		}
	}
	return;
}

void ds18b20_uso(){
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

void app_main() {
        hx711_t dev = {
        .dout = 4,
        .pd_sck = 2,
        .gain = HX711_GAIN_A_64
    };

    // initialize device
    ESP_ERROR_CHECK(hx711_init(&dev));

        gpio_reset_pin(LED);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

	ds18b20_init(TEMP_BUS);
	getTempAddresses(tempSensors);
	ds18b20_setResolution(tempSensors,2,10);

    printf("Address 0: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", tempSensors[0][0],tempSensors[0][1],tempSensors[0][2],tempSensors[0][3],tempSensors[0][4],tempSensors[0][5],tempSensors[0][6],tempSensors[0][7]);
	printf("Address 1: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", tempSensors[1][0],tempSensors[1][1],tempSensors[1][2],tempSensors[1][3],tempSensors[1][4],tempSensors[1][5],tempSensors[1][6],tempSensors[1][7]);


    // read from device
    while (1)
    {
        ds18b20_uso();
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
}
