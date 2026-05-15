#include "manualDHT11.h"
#define DHT_PIN 2

void setup(){
  // under
  pinMode(DHT_PIN, INPUT);
  Serial.begin(115200);
}

void loop(){
  float humidity;
  float temperature;
  if (readHumidityAndTemperature(DHT_PIN, &humidity, &temperature) == 0){
    Serial.printf("Humidity: %f, Temperature: %f\n", humidity, temperature);
  }
  delay(2000);
}
