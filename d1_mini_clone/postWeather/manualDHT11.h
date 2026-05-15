#ifndef MANUAL_DHT11_H
#define MANUAL_DHT11_H
#include <Arduino.h>

bool readBit(uint8_t sensorPin, unsigned long *lowTimeRecord,
             unsigned long *highTimeRecord);

byte readByte(uint8_t sensorPin);

int readHumidityAndTemperature(uint8_t sensorPin, float *humidity,
                               float *temperature);
#endif
