RTC_DATA_ATTR int bootCount = 0;

void setup(){
  // run every second 
  Serial.begin(115200);
  esp_sleep_enable_timer_wakeup(1*1000000);
  bootCount++;
  Serial.print("I'm awake! Boot Count: ");
  Serial.println(bootCount);
  Serial.println("I'm sleeping now...");
  Serial.flush();
  esp_deep_sleep_start();
}

void loop(){
}
