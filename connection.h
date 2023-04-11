

#ifndef _CONNECTION_H_
#define _CONNECTION_H_
#include <cJSON.h>
#include "arduino.h"
// #include <Arduino_JSON.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "esp_log.h"

#include "store.h"
#include "actuators.h"

#define CONNECTION_TAG "CONNECTION"


/**
 * @brief wifi Task Priority
 * 
 */
#define WIFI_TASK_PRIORITY 1

/**
 * @brief wifi Task stack size
 * 
 */
#define WIFI_TASK_STACK_SIZE 4096

/**
 * @brief wifi Task Handler
 * 
 */
extern TaskHandle_t task_wifi_handle;

void connectToWiFi(void* parameter);
void start_wifi_task();


/**
 * @brief MQTT Task Priority
 * 
 */
#define MQTT_TASK_PRIORITY 1

/**
 * @brief MQTT Task stack size
 * 
 */
#define MQTT_TASK_STACK_SIZE 4096

/**
 * @brief MQTT Task Handler
 * 
 */
extern TaskHandle_t task_mqtt_handle;

void callback(char* topic, byte* payload, unsigned int length);

void connectToMQTT(void* parameter);
void start_mqtt_task();

#endif
