#include "connection.h"

const char* ssid = "Test";
const char* password = "Test1234";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_password = "";
const char* mqtt_client_id = "iot_test";


const char* light1_topic = "bncoe123/home/light1";
const char* light2_topic = "bncoe123/home/light2";
const char* fan_topic = "bncoe123/home/fan";


WiFiClient espClient;
PubSubClient mqttClient(espClient);

QueueHandle_t streamer_queue;

TaskHandle_t task_wifi_handle;
TaskHandle_t task_mqtt_handle;

void start_wifi_task() {
  xTaskCreatePinnedToCore(&connectToWiFi, "connectToWiFi", WIFI_TASK_STACK_SIZE, NULL, WIFI_TASK_PRIORITY, &task_wifi_handle, 1);
}

void connectToWiFi(void* parameter) {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  printf("");
  printf("WiFi connected\n");
  Serial.print("IP address: \n");
  printf("%s\n", WiFi.localIP());
  // vTaskDelete(NULL);
  while (true) {
    if (WiFi.status() != WL_CONNECTED) {
      printf("wifi Not Connected\n");
      store_set_wifi_status(false);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


void start_mqtt_task() {
  xTaskCreatePinnedToCore(&connectToMQTT, "connectToMQTT", MQTT_TASK_STACK_SIZE, NULL, MQTT_TASK_PRIORITY, &task_mqtt_handle, 0);
}


void callback(char* topic, byte* payload, unsigned int length) {
  ESP_LOGI(CONNECTION_TAG,"Message Arrived on : %s.",topic);
  //   for (int i = 0; i < length; i++) {
  //   // Ignore newline characters
  //   if (payload[i] != '\n') {
  //   ESP_LOGI(CONNECTION_TAG,"%s",(char*)payload[i]);
  //     // Serial.print((char)payload[i]);
  //   }
  // }

  // Check which topic the message is for and set the appropriate relay state
  if (strcmp(topic, light1_topic) == 0) {
    bool state = (char)payload[0] == '1';
    set_relay_state(light1_relay_pin, state);
  } else if (strcmp(topic, light2_topic) == 0) {
    bool state = (char)payload[0] == '1';
    set_relay_state(light2_relay_pin, state);
  } else if (strcmp(topic, fan_topic) == 0) {
  ESP_LOGI(CONNECTION_TAG,"Message Arrived for fan 1 : %s.",topic);
    bool state = (char)payload[0] == '1';
    set_relay_state(fan_relay_pin, state);
  }
}

void connectToMQTT(void* parameter) {
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
  while (true) {
    if (WiFi.status() == WL_CONNECTED) {
      store_set_wifi_status(true);
      if (!mqttClient.connected()) {
        Serial.print("Connecting to MQTT server...\n");
        store_set_mqtt_status(false);
        if (mqttClient.connect(mqtt_client_id)) {
          printf("");
          printf("MQTT connected\n");
      mqttClient.subscribe(light1_topic);
      mqttClient.subscribe(light2_topic);
      mqttClient.subscribe(fan_topic);
          store_set_mqtt_status(true);
        } else {
          Serial.print(".");
        }
      }
      mqttClient.loop();
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
