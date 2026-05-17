
// this is the Data Direction Register for our pin
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PB1
// LED_PIN is defined with respect to the port (for pin 9, it's PORT B, PB1)

/*
|cycles|delay|
|---|---|
|0|0.0|
|1|62.5|
|2|125.0|
|3|187.5|
|4|250.0|
|5|312.5|
|6|375.0|
|7|437.5|
|8|500.0|
|9|562.5|
|10|625.0|
|11|687.5|
|12|750.0|
|13|812.5|
|14|875.0|
|15|937.5|
|16|1000.0|
|17|1062.5|
|18|1125.0|
|19|1187.5|
*/

/*
 * 0 means: $400 \pm 150 ns$ HIGH, $850 \pm 150 ns$ LOW
 * 1 means: $800 \pm 150 ns$ HIGH, $450 \pm 150 ns$ LOW
 * Reset: over $50 000 ns$ of LOW
*/

void sendBit0(){
  LED_PORT |= 1 << LED_PIN;
  // 400 ns
  // switching it back to LOW takes at least 2 cycles, so we'll wait for 4 cycles
  asm volatile ("nop");
  LED_PORT &= ~(1 << LED_PIN);
  // now wait for 850 ns might need to delay this even less... let's see
  asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
}

void sendBit1(){
  LED_PORT |= 1 << LED_PIN;
  // wait for 800 ns
  asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
  LED_PORT &= ~(1 << LED_PIN);
  asm volatile ("nop\nnop\nnop\nnop\nnop");
}

void sendBit(bool bit){
  if (bit){
    sendBit1();
  }
  else{
    sendBit0();
  }
}

void sendResetCode(){
  LED_DDR &= ~(1 << LED_PIN);
  // this is already at least 2 cycles, so already 125ns has passed
}

void setup(){
  // equivalent to pinMode
  LED_DDR |= 1 << LED_PIN;
  // send a reset signal, which is at least 50 microseconds
  sendResetCode();
}

void loop(){
  noInterrupts();
  sendBit0();
  //sendBit1();
  /*
  byte greenByte = 0x00;
  byte redByte = 0x00;
  byte blueByte = 0x00;
  // send it GRB
  for (int i = 7; i >= 0; i--){
    // we send it MSB
    sendBit((greenByte >> i) & 0b1);
  }

  for (int i = 7; i >= 0; i--){
    // we send it MSB
    sendBit((redByte >> i) & 0b1);
  }

  for (int i = 7; i >= 0; i--){
    // we send it MSB
    sendBit((blueByte >> i) & 0b1);
  }
  sendResetCode();
  */
  interrupts();
  delay(500);
}
