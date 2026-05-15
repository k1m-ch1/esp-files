
#define DHT_PIN 2
#define TIMEOUT 1000
#define CUTOFF 50
//
bool readBit(uint8_t sensorPin, unsigned long* lowTimeRecord, unsigned long* highTimeRecord){
  // assume that we've already set the sensorPin as INPUT
  // parameters used to record, just for debugging's sake. Just make it NULL if no need.
  unsigned long start = micros();
  // wait for around 50ms
  while (!digitalRead(sensorPin)){
  }
  if (lowTimeRecord != NULL){
    *lowTimeRecord = micros() - start;
  }

  start = micros();
  while (digitalRead(sensorPin)){
  }
  unsigned long highTime = micros() - start;
  if (highTimeRecord != NULL){
    *highTimeRecord = highTime;
  }

  // if it remains high for less than CUTOFF, consider it as a low bit, otherwise, high bit
  return highTime > CUTOFF;
}

byte readByte(uint8_t sensorPin){
  // one byte has 8 bits
  byte result = 0;
  for(int i = 0; i < 8; i++){
    result = (result << 1) + readBit(sensorPin, NULL, NULL);
  }
  return result;
}

void setup(){
  // under
  pinMode(DHT_PIN, INPUT);
  Serial.begin(115200);
}

void loop(){
  // now try to initialize it
  unsigned long start;
  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, LOW);
  // pull it low for 18ms to initialize it
  // let go of control
  delay(18);
  pinMode(DHT_PIN, INPUT);
  start = micros();
  
  unsigned long responseTime;
  // we should now wait for around 20 to 40 microseconds until the DHT pulls it low
  while(digitalRead(DHT_PIN)){
  }
  responseTime = micros() - start;

  // now we wait for 80 microseconds low, then 80 microseconds high as the respond code
  start = micros();
  while(!digitalRead(DHT_PIN)){
  }
  unsigned long lowHalfResponse = micros() - start;

  start = micros();
  while(digitalRead(DHT_PIN)){
  }
  unsigned long highHalfResponse = micros() - start;

  // now expect 40 bits of data for DHT11
  unsigned long lowTime[40];
  unsigned long highTime[40];
  for (int i = 0; i < 40; i++){
    readBit(DHT_PIN, &lowTime[i], &highTime[i]);
  }
  //start = micros();
  // now read 40 bits
  Serial.printf("Time taken to respond: %lu\n", responseTime);
  Serial.printf("LOW half of reponse code. Time: %lu\n", lowHalfResponse);
  Serial.printf("HIGH half of response code. Time: %lu\n", highHalfResponse);
  for (int i = 0; i < 40; i++){
    Serial.printf("For bit %d, low time: %lu, high time: %lu\n", i, lowTime[i], highTime[i]);
  }
  delay(2000);
}
