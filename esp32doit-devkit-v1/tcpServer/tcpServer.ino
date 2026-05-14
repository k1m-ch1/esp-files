#include <WiFi.h>
#include <env.h>

#define PORT 8000

char* ssid = SSID;
char* password = PASSWORD;

bool connected = false;

WiFiServer server(PORT);

void handleEvent(WiFiEvent_t event){
  Serial.printf("[WiFi-event] event: %d\r\n", event);
  if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP){
    Serial.printf("Connected! IP address: %s\r\n", WiFi.localIP().toString().c_str());
    connected = true;
    server.begin();
  }
  else if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED){
    Serial.println("Disconnected!");
    connected = false;
    server.stop();
  }
}

void setup(){
  Serial.begin(115200);
  WiFi.onEvent(handleEvent);
  WiFi.begin(ssid, password);
}

void loop(){
  if (connected){
    WiFiClient client = server.available();
    if (client){
      Serial.println("[server] Client connected!");
      client.print("[server] You're connected!\r\n");
      while (client.connected()){
        if (client.available()){
          char c = client.read();
          Serial.print(c);
        }
      }
      client.stop();
      Serial.println("[server] client disconnected");
    }
  }
}
