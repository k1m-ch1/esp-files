#include "env.h"
#include <ESP8266WiFi.h>

#define HOST "192.168.1.110"
#define PORT 8080

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
    WiFiClient client;
    if (client.connect(HOST, PORT)){
      Serial.println("Conntected to server");
      client.printf("Hello from %s\n", WiFi.localIP().toString().c_str());
      client.stop();
    }
    ESP.deepSleep(10e6);
  }
}
