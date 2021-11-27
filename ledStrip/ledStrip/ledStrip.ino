#include "FastLED.h"

#define NUM_LEDS      600
#define LED_TYPE   WS2812B
#define COLOR_ORDER   GRB
#define DATA_PIN        7
#define VOLTS          5
#define MAX_MA       500

CRGB leds[NUM_LEDS];
uint8_t hue = 41;  // light yellowish color
uint8_t saturation = 175; // just enough yellow and not white
uint8_t brightness = 255;

// Gradient palette "temperature_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/arendal/tn/temperature.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 144 bytes of program space.

DEFINE_GRADIENT_PALETTE( temperature_gp ) {
    0,   1, 27,105,
   14,   1, 27,105,
   14,   1, 40,127,
   28,   1, 40,127,
   28,   1, 70,168,
   42,   1, 70,168,
   42,   1, 92,197,
   56,   1, 92,197,
   56,   1,119,221,
   70,   1,119,221,
   70,   3,130,151,
   84,   3,130,151,
   84,  23,156,149,
   99,  23,156,149,
   99,  67,182,112,
  113,  67,182,112,
  113, 121,201, 52,
  127, 121,201, 52,
  127, 142,203, 11,
  141, 142,203, 11,
  141, 224,223,  1,
  155, 224,223,  1,
  155, 252,187,  2,
  170, 252,187,  2,
  170, 247,147,  1,
  184, 247,147,  1,
  184, 237, 87,  1,
  198, 237, 87,  1,
  198, 229, 43,  1,
  212, 229, 43,  1,
  212, 220, 15,  1,
  226, 220, 15,  1,
  226, 171,  2,  2,
  240, 171,  2,  2,
  240,  80,  3,  3,
  255,  80,  3,  3};


DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,     0,  0,  0,   //black
128,   255,  0,  0,   //red
224,   255,255,  0,   //bright yellow
255,   255,255,255 }; //full white

CRGBPalette16 myPal = temperature_gp;

CRGBPalette16 testPal = CRGBPalette16 (
  CRGB::Black,
  CRGB::Black,

  CRGB::RoyalBlue,
  CRGB::RoyalBlue,

  CRGB::Red,
  CRGB::Red,

  CRGB::Yellow,
  CRGB::Yellow,

  CRGB::Purple,
  CRGB::Purple,

  CRGB::Green,
  CRGB::Green,

  CRGB::OrangeRed,
  CRGB::OrangeRed,

  CRGB::White,
  CRGB::White
);

uint8_t paletteIndex = 0;
int scheme = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
  FastLED.setBrightness(brightness);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  EVERY_N_SECONDS(5) {
    scheme = random(0, 2);
  }

  runScheme(scheme);

  FastLED.show();
}


void runScheme(int scheme) {
  switch( scheme ) {
    case 0:
      randomLights();
      break;
    case 1:
      runningRainbow();
      break;
    default:
      flickerLEDs(random(0, NUM_LEDS));
      break;
  }
}
void randomLights() {
    EVERY_N_MILLISECONDS(10) {
      leds[random(0, NUM_LEDS - 1)] = ColorFromPalette(testPal, random8(), 255, LINEARBLEND);
    }
    fadeToBlackBy(leds, NUM_LEDS, 1);
}

void flickerLEDs(int randLED) {
  FastLED.clear();
  for (int led = 0; led <= randLED; led++) {
    leds[led] = CHSV(hue, saturation, brightness);
  }
  FastLED.show();
}

void runningRainbow() {
  fill_palette(leds, NUM_LEDS, paletteIndex, 1, testPal, 255, LINEARBLEND);
  EVERY_N_MILLISECONDS(10) {
    paletteIndex++;
  }
}