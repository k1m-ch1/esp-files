
#define LED_PIN LED_BUILTIN
volatile uint8_t ledState = LOW;

ISR(TIMER1_COMPA_vect){
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup(){
  pinMode(LED_PIN, OUTPUT);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  // clear all settings
  TCNT1 = 0;
  OCR1A = 15624;

  // resetting the counter after interrupt
  TCCR1B |= (1 << WGM12);
  // setting prescalar to 256
  TCCR1B |= (1 << CS12);
  
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop(){

}
