#include <TFT_eSPI.h>
#include <Arduino.h>
#include "image_arrays.h"
#include "pins.h"


#define MOISTURE_PIN 1
#define DRY_THRESHOLD 2000
#define WET_THRESHOLD 1000
enum State { DRY = 0, MOIST = 1, WET = 2 };

TFT_eSPI tft = TFT_eSPI();

int previousState = -1;

//Function used to scale image -> takes up less flash?
void drawScaledImage(int destX, int destY, int destWidth, int destHeight,
                      int srcWidth, int srcHeight, const uint16_t* imageData) {
  uint16_t* scaledBuffer = (uint16_t*)malloc(destWidth * destHeight * sizeof(uint16_t));

  for (int y = 0; y < destHeight; y++) {
    for (int x = 0; x < destWidth; x++) {
      int srcX = (x * srcWidth) / destWidth;
      int srcY = (y * srcHeight) / destHeight;
      uint16_t color = imageData[srcY * srcWidth + srcX];
      scaledBuffer[y * destWidth + x] = color;
    }
  }

  tft.pushImage(destX, destY, destWidth, destHeight, scaledBuffer);
  free(scaledBuffer);
}


void setup() {
  Serial.begin(115200);
  delay(1000);
  tft.init();
  tft.setSwapBytes(true);
  tft.invertDisplay(true);
  tft.fillScreen(TFT_BLACK);
  pinMode(MOISTURE_PIN, INPUT);
}

void loop() {
  int rawValue = analogRead(MOISTURE_PIN);  
  Serial.println(rawValue);
  int currentState;

  if (rawValue > DRY_THRESHOLD){
	currentState = DRY; 
  } else if (rawValue <  WET_THRESHOLD){
	currentState = WET;
  } else {
	currentState = MOIST; 
  }

    if (currentState != previousState) {
		if (currentState == DRY) {
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_dry_frame1);
			delay(5000);
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_dry_frame2);
			delay(1000);
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_dry_frame3);
		} else if (currentState == WET) {
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_wet_frame1);
			delay(5000);
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_wet_frame2);
			delay(1000);
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_wet_frame3);
		} else {
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_happy_frame1);
			delay(5000);
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_happy_frame2);
			delay(1000);
			drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_happy_frame3);
		}
		previousState = currentState; 
  }
  
  delay(500);
}


