
#include <Servo.h>

#define INPUT_PIN A0
#define SERVO_PIN 9
#define DELAY_TIME 60

Servo servo;


void setup(){
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(115200);
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(1000);
}

void loop(){
  int servoOnPeriod = map(analogRead(INPUT_PIN), 0, 1020, 1000, 2000);
  // clamp it
  if (servoOnPeriod > 2000){
    servoOnPeriod = 2000;
  }
  if (servoOnPeriod < 1000){
    servoOnPeriod = 1000;
  }
  Serial.println(servoOnPeriod);
  servo.writeMicroseconds(servoOnPeriod);
  delay(DELAY_TIME);
}
