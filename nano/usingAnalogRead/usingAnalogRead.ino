#include <Servo.h>

#define INPUT_PIN A0

void setup(){
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(115200);
}

void loop(){
  Serial.println(analogRead(INPUT_PIN));
  delay(100);
}
