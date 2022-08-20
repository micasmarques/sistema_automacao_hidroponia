#include <stdio.h>
#include <inttypes.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"

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