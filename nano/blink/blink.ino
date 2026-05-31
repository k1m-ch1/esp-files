
#define DELAY_TIME 1000
#define LED_PIN LED_BUILTIN

void setup(){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED is high!");
  delay(DELAY_TIME);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED is low!"); }
  delay(DELAY_TIME);
