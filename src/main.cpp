#include <TFT_eSPI.h>
#include <Arduino.h>
#include "image_arrays.h"
#include "pins.h"

#define MOISTURE_PIN 1
#define DRY_ENTER 2000 // become DRY when reading > this
#define DRY_EXIT 1900  // stop being DRY when reading < this
#define WET_ENTER 1000 // become WET when reading < this
#define WET_EXIT 1100  // stop being WET when reading > this

enum State
{
  DRY = 0,
  HAPPY = 1,
  WET = 2,
  TOUCHED = 3
};

TFT_eSPI tft = TFT_eSPI();

int moistureState = HAPPY;
int previousAnimation = -1;
int activeAnimation;

const int frameDurations[] = {5000, 1000, 0};

int currentFrameCounter = 0;
uint32_t frameStartedAt = 0;

void drawScaledImage(int destX, int destY, int destWidth, int destHeight,
                     int srcWidth, int srcHeight, const uint16_t *imageData)
{
  uint16_t *scaledBuffer = (uint16_t *)malloc(destWidth * destHeight * sizeof(uint16_t));

  for (int y = 0; y < destHeight; y++)
  {
    for (int x = 0; x < destWidth; x++)
    {
      int srcX = (x * srcWidth) / destWidth;
      int srcY = (y * srcHeight) / destHeight;
      uint16_t color = imageData[srcY * srcWidth + srcX];
      scaledBuffer[y * destWidth + x] = color;
    }
  }

  tft.pushImage(destX, destY, destWidth, destHeight, scaledBuffer);
  free(scaledBuffer);
}

void drawFrame(int state, int counter)
{
  if (state == DRY)
  {
    if (counter == 0)
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_dry_frame1);
    else if (counter == 1)
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_dry_frame2);
    else
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_dry_frame3);
  }
  else if (state == WET)
  {
    if (counter == 0)
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_wet_frame1);
    else if (counter == 1)
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_wet_frame2);
    else
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_wet_frame3);
    /*} else if (state == TOUCHED) {
      if (counter == 0) drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_love_frame1);
      else if (counter == 1) drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_love_frame2);
      else drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_love_frame3);*/
  }
  else
  {
    if (counter == 0)
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_happy_frame1);
    else if (counter == 1)
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_happy_frame2);
    else
      drawScaledImage(0, 0, 240, 280, 96, 96, epd_bitmap_happy_frame3);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  tft.init();
  tft.setSwapBytes(true);
  tft.invertDisplay(true);
  tft.fillScreen(TFT_BLACK);
  pinMode(MOISTURE_PIN, INPUT);
}

void loop()
{
  static uint32_t lastSensorRead = -2000;
  int rawValue; 
  if (millis() - lastSensorRead >= 2000)
  {
    rawValue = analogRead(MOISTURE_PIN);
    Serial.println(rawValue);
    lastSensorRead = millis();

    if (moistureState == DRY)
    {
      if (rawValue < DRY_EXIT)
        moistureState = HAPPY;
    }
    else if (moistureState == WET)
    {
      if (rawValue > WET_EXIT)
        moistureState = HAPPY;
    }
    else
    {
      if (rawValue > DRY_ENTER)
        moistureState = DRY;
      else if (rawValue < WET_ENTER)
        moistureState = WET;
    } // if TOUCHED {activeAnimation = hearts}
  }

  if (activeAnimation != TOUCHED)
  {
    activeAnimation = moistureState;
  }

  if (activeAnimation != previousAnimation)
  {
    currentFrameCounter = 0;
    drawFrame(activeAnimation, currentFrameCounter);
    frameStartedAt = millis();
    previousAnimation = activeAnimation;
  }
  else if (currentFrameCounter < 2)
  {
    if (millis() - frameStartedAt >= frameDurations[currentFrameCounter])
    {
      currentFrameCounter++;
      drawFrame(activeAnimation, currentFrameCounter);
      frameStartedAt = millis();
    }
  } /*else if (activeAnimation == TOUCHED && millis() - frameStartedAt >= 1200){
        activeAnimation = moistureState;
      }*/
}
