#include "actuators.h"
SemaphoreHandle_t xSemaphore = NULL;
TaskHandle_t task_led_indication_handle;

void set_relay_state(int relay_pin, bool state) {
  xSemaphoreTake(xSemaphore, portMAX_DELAY); // Take the semaphore
  printf("state:%d\n",state);
  if (state) {
    digitalWrite(relay_pin, HIGH); // Turn the relay ON
  } else {
    digitalWrite(relay_pin, LOW); // Turn the relay OFF
  }
  xSemaphoreGive(xSemaphore); // Give the semaphore
}


void start_led_indication_task() {
  xTaskCreate(&led_indication_task, "led_indication_task", LED_INDICATION_TASK_STACK_SIZE, NULL, LED_INDICATION_TASK_PRIORITY, &task_led_indication_handle);
}

void led_indication_task(void *Params) {
  pinMode(HMI_INDICATION_LED, OUTPUT);
  while (1) {
    if (store_get_wifi_status() == true && store_get_mqtt_status() == true ) {
      digitalWrite(HMI_INDICATION_LED, HIGH);
    }  else {
      digitalWrite(HMI_INDICATION_LED, HIGH);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      digitalWrite(HMI_INDICATION_LED, LOW);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

