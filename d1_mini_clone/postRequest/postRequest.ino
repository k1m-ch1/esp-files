#include "env.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define URL "http://192.168.1.110:8080"

bool gotIP = false;

void handleEvent(WiFiEvent_t event){
  if (event == WIFI_EVENT_STAMODE_GOT_IP){
    Serial.printf("[WiFi] got ip: %s\n", WiFi.localIP().toString().c_str());
    gotIP = true;
  }
  else if(event == WIFI_EVENT_STAMODE_DISCONNECTED){
    Serial.println("[WiFi] disconnected");
    gotIP = false;
  }
}

void setup(){
  Serial.begin(115200);
  WiFi.onEvent(handleEvent);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop(){
  if (gotIP == true){
    HTTPClient http;
    WiFiClient client;
    if(http.begin(client, URL)){
      http.addHeader("Content-Type", "application/json");
      int temperature = 36;
      int humidity = 50;
      String httpRequestData = String("{\"key\": \"") + KEY +
        String("\",\"temperature\":") + String(temperature) +
        String(",\"humidity\":") + String(humidity) +
        String("}");
      if(http.POST(httpRequestData) > 0){
        String data = http.getString();
        Serial.println(data);
      }
    }
    client.stop();
    ESP.deepSleep(10e6);
  }
}
