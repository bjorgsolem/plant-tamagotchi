#include <Arduino.h>
#include <LovyanGFX.hpp>

void setup() {
 Serial.begin(115200);
  delay(1000);
}

void loop() {
 int rawValue = analogRead(1);  
  Serial.println(rawValue);
  delay(500);
}



//thresholds:
/*
Dry soil: reading > 1800
Moist soil: 1000 - 1800
Wet soil: < 1000

*/