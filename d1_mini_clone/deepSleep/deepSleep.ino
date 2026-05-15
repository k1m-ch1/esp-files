/*
 * Wemos D1 Mini Deep Sleep Example
 * Requirements: Wire D0 to RST */

void setup() {
  Serial.begin(115200);
  Serial.println("\nI'm awake!");

  // --- Your code (sensors, WiFi) goes here ---
  
  // Sleep for 10 seconds (10 * 1,000,000 microseconds)
  Serial.println("Going to sleep for 1 seconds...");
  ESP.deepSleep(1e6); 
}

void loop() {
  // Loop is not used in deep sleep
}
