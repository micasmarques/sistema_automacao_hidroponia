#include <inttypes.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <hx711.h>
#include <stdio.h>
#include "ds18b20.h"
#include "driver/gpio.h"
#include "hx711Use.c"
#include "getTempAddresses.c"

static const char *TAG = "hx711-example";

#define TEMP_BUS 26
#define LED 2
#define HIGH 1
#define LOW 0
#define digitalWrite gpio_set_level

DeviceAddress tempSensors[2];

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
    while (1) {
        ds18b20Use();
        hx711Use();
}
