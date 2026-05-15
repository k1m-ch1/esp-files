#include "manualDHT11.h"
#include "env.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Ticker.h>

#define URL "http://192.168.1.145:10000"

#define DHT_PIN 2

#define TIMEOUT 10
#define SLEEP_DURATION 5e6

Ticker timeOutSleepTimer;

void timeOutSleep(){
  ESP.deepSleep(SLEEP_DURATION);
}

void setup(){
  Serial.begin(115200);
  pinMode(DHT_PIN, INPUT);
  timeOutSleepTimer.attach(TIMEOUT, timeOutSleep);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Trying to connect to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("[WiFi] got ip: %s\n", WiFi.localIP().toString().c_str());
  HTTPClient http;
  WiFiClient client;
  if(http.begin(client, URL)){
    http.addHeader("Content-Type", "application/json");
    float temperature;
    float humidity;
    readHumidityAndTemperature(DHT_PIN, &temperature, &humidity);
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
  ESP.deepSleep(SLEEP_DURATION);
}

void loop(){
}
