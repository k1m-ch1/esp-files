#include <BluetoothSerial.h>
// note that this is ESP specific

BluetoothSerial SerialBT;
// basically, we're turning our ESP into a serial bluetooth device, similar to an HC-05 (but an HC-05 is expensive as shit)

void setup(){
  Serial.begin(9600);
  SerialBT.begin("My ESP-32 device");
}

void loop(){
  if (SerialBT.available()){
    char c = SerialBT.read();
    Serial.print(c);
  }
}
