#include "connection.h"
#include "actuators.h"


void setup() {
  // put your setup code here, to run once:
  
  printf("Setup Done"); 
  
  pinMode(light1_relay_pin, OUTPUT);
  pinMode(light2_relay_pin, OUTPUT);
  pinMode(fan_relay_pin, OUTPUT);
  xSemaphore = xSemaphoreCreateMutex();
  start_led_indication_task();
  // start_interrupt_task();
  start_wifi_task();
  start_mqtt_task();
}

void loop() {
  // put your main code here, to run repeatedly:
  // printf("Setup Done\n");
  // delay(1000);
}
