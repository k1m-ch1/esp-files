#include <Servo.h>

#define SERVO_PIN 9

Servo servo;

void setup(){
  Serial.begin(115200);
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  servo.write(0);
}

void loop(){
  if (Serial.available() > 0){
    int angle = Serial.parseInt();
    Serial.println(angle);
    servo.write(angle);
  }
}
