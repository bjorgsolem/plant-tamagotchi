#include <Adafruit_NeoPixel.h>

#define LED_PIN   38
#define NUM_LEDS  1

Adafruit_NeoPixel led(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");
  led.begin();
  led.setBrightness(50);
  Serial.println("NeoPixel initialized");
}

void loop() {
  Serial.println("Red");
  led.setPixelColor(0, led.Color(255, 0, 0));
  led.show();
  delay(1000);

  Serial.println("Green");
  led.setPixelColor(0, led.Color(0, 255, 0));
  led.show();
  delay(1000);

  Serial.println("Blue");
  led.setPixelColor(0, led.Color(0, 0, 255));
  led.show();
  delay(1000);

  Serial.println("Pink");
  led.setPixelColor(0, led.Color(255, 105, 180));
  led.show();
  delay(1000);
}