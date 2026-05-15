#include "manualDHT11.h"
#include "env.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define URL "http://192.168.1.145:10000"

#define DHT_PIN 2

#define WIFI_TIMEOUT_MS 10000
#define HTTP_TIMEOUT_MS 5000
#define SLEEP_DURATION 5e6

void setup(){
  Serial.begin(115200);
  pinMode(DHT_PIN, INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int wifiStart = millis();
  Serial.print("Trying to connect to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    if(millis() - wifiStart > WIFI_TIMEOUT_MS){
      Serial.printf("[WiFi] time out of %d milliseconds has reached. Forcefully going to sleep.\n", WIFI_TIMEOUT_MS);
      ESP.deepSleep(SLEEP_DURATION);
    }
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("[WiFi] got ip: %s\n", WiFi.localIP().toString().c_str());
  float temperature;
  float humidity;
  if(!readHumidityAndTemperature(DHT_PIN, &temperature, &humidity)){
    HTTPClient http;
    WiFiClient client;
    http.setTimeout(HTTP_TIMEOUT_MS);
    if(http.begin(client, URL)){
      http.addHeader("Content-Type", "application/json");
      String httpRequestData = String("{\"key\": \"") + KEY +
        String("\",\"temperature\":") + String(temperature) +
        String(",\"humidity\":") + String(humidity) +
        String("}");
      if(http.POST(httpRequestData) > 0){
        String data = http.getString();
        Serial.println(data);
      }
    }
    http.end();
    client.stop();
  }
  ESP.deepSleep(SLEEP_DURATION);
}

void loop(){
}
