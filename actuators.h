#ifndef _ACTUATORS_H_
#define _ACTUATORS_H_
#include "arduino.h"
#include "store.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"
#include "esp_log.h"

#define HMI_INDICATION_LED 25


const int light1_relay_pin = 26;
const int light2_relay_pin = 14;
const int fan_relay_pin =  13;

extern SemaphoreHandle_t xSemaphore;

void set_relay_state(int relay_pin, bool state) ;


/**
 * @brief LED INDICATION Task Priority
 * 
 */
#define LED_INDICATION_TASK_PRIORITY 7

/**
 * @brief LED INDICATION Task stack size
 * 
 */
#define LED_INDICATION_TASK_STACK_SIZE 2048

/**
 * @brief LED INDICATION Task Handler
 * 
 */
extern TaskHandle_t task_led_indication_handle;

void start_led_indication_task();

void led_indication_task(void*Params);

#endif