#include "FastLED.h"

#define NUM_LEDS      600
#define LED_TYPE   WS2812B
#define COLOR_ORDER   GRB
#define DATA_PIN        7
#define VOLTS          5
#define MAX_MA       1500

CRGB leds[NUM_LEDS];
uint8_t hue = 41;  // light yellowish color
uint8_t saturation = 175; // just enough yellow and not white
uint8_t brightness = 255;

CRGBPalette16 brightChristmasPal = CRGBPalette16 (
  CRGB::Red,
  CRGB::Red,

  CRGB::RoyalBlue,
  CRGB::RoyalBlue,

  CRGB::Goldenrod,
  CRGB::Goldenrod,

  CRGB::Green,
  CRGB::Green,

  CRGB::Red,
  CRGB::Red,

  CRGB::RoyalBlue,
  CRGB::RoyalBlue,

  CRGB::Goldenrod,
  CRGB::Goldenrod,
  
  CRGB::Green,
  CRGB::Green
);

CRGBPalette16 hanukkahPal = CRGBPalette16 (
  CRGB::White,
  CRGB::White,

  CRGB::Blue,
  CRGB::Blue,

  CRGB::White,
  CRGB::White,

  CRGB::Blue,
  CRGB::Blue,

  CRGB::White,
  CRGB::White,

  CRGB::Blue,
  CRGB::Blue,

  CRGB::White,
  CRGB::White,

  CRGB::Blue,
  CRGB::Blue
);

CRGBPalette16 christmasPal = CRGBPalette16 (
  CRGB::Red,
  CRGB::Red,

  CRGB::Green,
  CRGB::Green,

  CRGB::Red,
  CRGB::Red,

  CRGB::Green,
  CRGB::Green,

  CRGB::Red,
  CRGB::Red,

  CRGB::Green,
  CRGB::Green,

  CRGB::Red,
  CRGB::Red,

  CRGB::Green,
  CRGB::Green
);

CRGBPalette16 thirdChristmasPal = CRGBPalette16 (
  CRGB::Red,
  CRGB::Red,

  CRGB::Blue,
  CRGB::Blue,

  CRGB::Orange,
  CRGB::Orange,

  CRGB::Green,
  CRGB::Green,

  CRGB::Yellow,
  CRGB::Yellow,

  CRGB::Red,
  CRGB::Red,

  CRGB::Blue,
  CRGB::Blue,

  CRGB::Orange,
  CRGB::Orange
);

uint8_t paletteIndex = 0;
int scheme = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
  FastLED.clear();
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
  EVERY_N_SECONDS(60) {
    scheme = random(0, 9);
    Serial.println(scheme);
  }

  runScheme(scheme);
  FastLED.show();
}

void runScheme(int scheme) {
  switch( scheme ) {
    case 0:
      randomLights(brightChristmasPal);
      break;
    case 1:
      randomLights(thirdChristmasPal);
      break;
    case 2:
      randomLights(christmasPal);
      break;
    case 3:
      runningRainbow(brightChristmasPal);
      break;
    case 4:
      runningRainbow(thirdChristmasPal);
      break;
    case 5:
      runningRainbow(christmasPal);
      break;
    case 6:
      bothSides(brightChristmasPal);
      break;
    case 7:
      bothSides(thirdChristmasPal);
      break;
    case 8:
      bothSides(christmasPal);
      break;
    default:
      randomLights(brightChristmasPal);
      break;
  }
}

void randomLights(CRGBPalette16 pal) {
    EVERY_N_MILLISECONDS(25) {
      leds[random(0, NUM_LEDS - 1)] = ColorFromPalette(pal, random8(), 255, LINEARBLEND);
    }
    fadeToBlackBy(leds, NUM_LEDS, 1);
}

void runningRainbow(CRGBPalette16 pal) {
  fill_palette(leds, NUM_LEDS, paletteIndex, 255, pal, 255, LINEARBLEND);
  EVERY_N_MILLISECONDS(25) {
    paletteIndex++;
  }
}

void bothSides(CRGBPalette16 pal) {
  uint16_t sin1 = beatsin16(2, 0, NUM_LEDS - 1, 0, 0);
  uint16_t sin2 = beatsin16(2, 0, NUM_LEDS -1, 0, 32768);
  uint8_t color1 = beatsin8(2, 0, 255, 0, 0);
  uint8_t color2 = beatsin8(2, 0, 255, 0, 64);

  leds[sin1] = ColorFromPalette(pal, color1, 255, LINEARBLEND);
  leds[sin2] = ColorFromPalette(pal, color2, 255, LINEARBLEND);
  blur1d(leds, NUM_LEDS, 64);
  fadeToBlackBy(leds, NUM_LEDS, 10);
}