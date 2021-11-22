#include "FastLED.h"

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define NUM_LEDS      3
#define LED_TYPE   WS2812B
#define COLOR_ORDER   GRB
#define DATA_PIN        7
#define VOLTS          5
#define MAX_MA       500
uint8_t maxBrightness = 255;
uint8_t minBrightness = 50;
CRGB leds[NUM_LEDS];

DEFINE_GRADIENT_PALETTE

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
  FastLED.setBrightness(minBrightness);
  FastLED.clear();
  fill_solid(leds, NUM_LEDS, CRGB::Goldenrod);
  FastLED[0].showLeds(minBrightness);
}

void loop() {
  flickerLEDs();
}

void flickerLEDs() {
  for (int i=minBrightness; i<=maxBrightness; i++) {
    FastLED[0].showLeds(i);
    delay(1);
  }
  for (int i=maxBrightness; i>=minBrightness; i--) {
    FastLED[0].showLeds(i);
    delay(5);
  }
}