#define LED_PIN 2
#define DELAY_TIME 1000

void setup(){
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED is on");
  delay(DELAY_TIME);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED is off");
  delay(DELAY_TIME);
}
