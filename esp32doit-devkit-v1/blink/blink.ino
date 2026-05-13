#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(LED_PIN);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED is on!");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED is off!");
  delay(1000);
}
