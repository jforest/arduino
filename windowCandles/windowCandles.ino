#include "FastLED.h"

#define NUM_LEDS      3
#define LED_TYPE   WS2812B
#define COLOR_ORDER   GRB
#define DATA_PIN        7
#define VOLTS          5
#define MAX_MA       500

CRGB leds[NUM_LEDS];
uint8_t hue = 41;  // light yellowish color
uint8_t saturation = 175; // just enough yellow and not white
uint8_t brightness = 255;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
  FastLED.setBrightness(brightness);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  EVERY_N_MILLISECONDS(10) {
    int randLED = random(3);
    flickerLEDs(randLED);
  }
}

void flickerLEDs(int randLED) {
  FastLED.clear();
  for (int led = 0; led <= randLED; led++) {
    leds[led] = CHSV(hue, saturation, brightness);
  }
  FastLED.show();
}