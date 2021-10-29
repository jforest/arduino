#include <FastLED.h>

#define NUM_LEDS 288
#define DATA_PIN 2
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define BRIGHTNESS 60
#define VOLTS 5
#define MAX_AMPS 500 // mA
#define BATCH_SIZE 16

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<NUM_LEDS; i+=BATCH_SIZE) {
    pulseLeds(BATCH_SIZE, i);
  }
}

void pulseLeds(int batchSize, int startingLED) {
  // Pulse LEDs from startingLED to startingLED+batchSize
  for (int i=startingLED; i<(startingLED + batchSize); i++) {
    leds[i] = CRGB::OrangeRed;
    FastLED.show();
  }
  for (int i=startingLED; i<(startingLED + batchSize); i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}
