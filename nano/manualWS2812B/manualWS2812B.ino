
// this is the Data Direction Register for our pin
//#define LED_DDR DDRD
//#define LED_PORT PORTD
//#define LED_PIN PD6

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PB1
#define DELAY_TIME 1000

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

void sendResetCode(){
  LED_PORT &= ~(1 << LED_PIN);
  // this is already at least 2 cycles, so already 125ns has passed
  unsigned long start = micros();
  while(micros() - start < 60){
  }
}



void send0(){
  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");
}

void send1(){
  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
}

template<bool bit>
inline void sendBit(){
  if constexpr (bit){
    LED_PORT |= (1 << LED_PIN);
    __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    LED_PORT &= ~(1 << LED_PIN);
  } else {
    LED_PORT |= (1 << LED_PIN);
    __asm__("nop\nnop\nnop\nnop\n");
    LED_PORT &= ~(1 << LED_PIN);
    __asm__("nop\nnop\nnop\nnop\nnop\n");

  }
}

void setup(){
  // equivalent to pinMode
  LED_DDR |= 1 << LED_PIN;
  // send a reset signal, which is at least 50 microseconds
  sendResetCode();
}

void loop(){
  noInterrupts();

  // sending byte 0x00000000
  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending byte 0xff000000
  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending byte 0xff000000
  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  // sending 1

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");


  sendResetCode();
  interrupts();
  delay(DELAY_TIME);

  // sending byte 0x00000000
  // sending 0

  noInterrupts();
  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending byte 0x00000000
  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending byte 0x00000000
  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  // sending 0

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  sendResetCode();
  interrupts();
  delay(DELAY_TIME);

}
