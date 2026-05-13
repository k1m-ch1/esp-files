#include <WiFi.h>
#include "env.h"

const char* ssid = SSID;
const char* password = PASSWORD;

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
}

void loop(){

}
