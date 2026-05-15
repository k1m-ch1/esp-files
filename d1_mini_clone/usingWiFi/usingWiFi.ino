#include "env.h"
#include <ESP8266WiFi.h>

void handleEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);

  switch(event) { 
    case WIFI_EVENT_STAMODE_CONNECTED:
      Serial.printf("[WiFi] %d, Connected\n", event);
      break;

    case WIFI_EVENT_STAMODE_DISCONNECTED:
      Serial.println("[WiFi] disconnected");
      break;

    case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
      Serial.printf("[WiFi] %d, AuthMode Change\n", event);
      break;

    case WIFI_EVENT_STAMODE_GOT_IP:
      Serial.printf("[WiFi] %d, Got IP\n", event);
      break;

    case WIFI_EVENT_STAMODE_DHCP_TIMEOUT:
      Serial.printf("[WiFi] %d, DHCP Timeout\n", event);
      break;

    case WIFI_EVENT_SOFTAPMODE_STACONNECTED:
      Serial.printf("[AP] %d, Client Connected\n", event);
      break;

    case WIFI_EVENT_SOFTAPMODE_STADISCONNECTED:
      Serial.printf("[AP] %d, Client Disconnected\n", event);
      break;

    case WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED:
      //      Serial.printf("[AP] %d, Probe Request Recieved\n", event);
      break;
  }
}

void setup(){
  Serial.begin(115200);
  WiFi.onEvent(handleEvent);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop(){
  Serial.println(WiFi.localIP().toString());
  delay(1000);
}
