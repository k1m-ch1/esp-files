#include "manualDHT11.h"

#define CUTOFF 50

bool readBit(uint8_t sensorPin, unsigned long *lowTimeRecord,
             unsigned long *highTimeRecord) {
  // assume that we've already set the sensorPin as INPUT
  // parameters used to record, just for debugging's sake. Just make it NULL if
  // no need.
  unsigned long start = micros();
  // wait for around 50ms
  while (!digitalRead(sensorPin)) {
  }
  if (lowTimeRecord != NULL) {
    *lowTimeRecord = micros() - start;
  }

  start = micros();
  while (digitalRead(sensorPin)) {
  }
  unsigned long highTime = micros() - start;
  if (highTimeRecord != NULL) {
    *highTimeRecord = highTime;
  }

  // if it remains high for less than CUTOFF, consider it as a low bit,
  // otherwise, high bit
  return highTime > CUTOFF;
}

byte readByte(uint8_t sensorPin) {
  // one byte has 8 bits
  byte result = 0;
  for (int i = 0; i < 8; i++) {
    result = (result << 1) + readBit(sensorPin, NULL, NULL);
  }
  return result;
}

int readHumidityAndTemperature(uint8_t sensorPin, float *humidity,
                               float *temperature) {
  // a return of 0 means that all is ok
  // a return of 1 means that checksum failed or some other error

  unsigned long start;
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  // pull it low for 18ms to initialize it
  delay(18);
  // let go of control
  pinMode(sensorPin, INPUT);

  unsigned long responseTime;
  // we should now wait for around 20 to 40 microseconds until the DHT pulls it
  // low
  while (digitalRead(sensorPin)) {
  }

  // now we wait for 80 microseconds low, then 80 microseconds high as the
  // reponse code
  while (!digitalRead(sensorPin)) {
  }

  while (digitalRead(sensorPin)) {
  }

  // now expect 40 bits of data for DHT11
  // that's to say, we should expect 40/8 = 5 bytes
  byte data[5];
  for (int i = 0; i < 5; i++) {
    data[i] = readByte(sensorPin);
  }

  byte expectedCheckSum =
      (data[0] + data[1] + data[2] + data[3]) & (0b11111111);

  if (expectedCheckSum != data[4]) {
    return 1;
  }

  *humidity = (float)data[0] + ((float)data[1] / 10.0f);
  *temperature = (float)data[2] + ((float)data[3] / 10.0f);
  return 0;
}
