#include "env.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define URL "http://192.168.0.104:8080"

RTC_DATA_ATTR int bootCount = 0;

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void handleEvent(WiFiEvent_t event){
  Serial.printf("[WiFi-event] event: %d\r\n", event);
  if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP){
    // just going to request it once
    HTTPClient http;
    if(http.begin(URL)){
      if(http.GET() > 0){
        String data = http.getString();
        Serial.print(data);
      }
    }
    esp_deep_sleep_start();
  }
  else if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED){
    Serial.println("Disconnected!");
  }
}

void setup(){
  Serial.begin(115200);
  esp_sleep_enable_timer_wakeup(5*1000000);
  WiFi.onEvent(handleEvent);
  WiFi.begin(ssid, password);
}

void loop(){
}
