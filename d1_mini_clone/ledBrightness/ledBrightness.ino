#define LED_PIN 2
#define DELAY_TIME 5000
#define PWM_MAX 255

void setup(){
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  int pwmSignal = (((millis() % DELAY_TIME)*PWM_MAX)/DELAY_TIME);
  analogWrite(LED_PIN, pwmSignal);
  Serial.printf("Setting LED brightness to: %d\r\n", pwmSignal);
  delay(100);
}
