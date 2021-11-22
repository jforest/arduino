#include <FastLED.h>

#define NUM_LEDS 288
#define DATA_PIN 2
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define VOLTS 5
#define MAX_AMPS 500 // mA
#define BATCH_SIZE 16
uint8_t gBrightness = 60;

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  fill_solid(leds, NUM_LEDS, CRGB::OrangeRed);
  FastLED[0].showLeds(gBrightness);
}

void loop() {
  // Cycle through the leds, dimming brightness on each one slowly in a wave
  for (int i=0; i<NUM_LEDS; i+=BATCH_SIZE) {
    for (int j=i; j<i+BATCH_SIZE; j++) {
      leds[j] = CRGB::White;
      FastLED[0].showLeds(gBrightness);
    } 
  }
}

void setLedState(int batchSize, int startingLED, bool ledState) {
  // Pulse LEDs from startingLED to startingLED+batchSize
  for (int i=startingLED; i<(startingLED + batchSize); i++) {
    if (ledState) {
      leds[i] = CRGB::OrangeRed;
    } else {
      leds[i] = CRGB::Black;
    }
  }
}
