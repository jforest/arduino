#include "FastLED.h"

#define NUM_LEDS      600
#define NUM_LEDS2     688
#define LED_TYPE  WS2812B
#define COLOR_ORDER   GRB
#define DATA_PIN        7
#define DATA_PIN2       6
#define VOLTS           5
#define MAX_MA       1500

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS2];
uint8_t brightness = 127;

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
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(leds2, NUM_LEDS2);
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
      leds[random(0, NUM_LEDS - 1)] = ColorFromPalette(pal, random8(), brightness, LINEARBLEND);
      leds2[random(0, NUM_LEDS2 -1)] = ColorFromPalette(pal, random8(), brightness, LINEARBLEND);
    }
    fadeToBlackBy(leds, NUM_LEDS, 1);
    fadeToBlackBy(leds2, NUM_LEDS2, 1);
}

void runningRainbow(CRGBPalette16 pal) {
  fill_palette(leds, NUM_LEDS, paletteIndex, 255, pal, brightness, LINEARBLEND);
  fill_palette(leds2, NUM_LEDS2, paletteIndex + 64, 255, pal, brightness, LINEARBLEND);
  EVERY_N_MILLISECONDS(25) {
    paletteIndex++;
  }
}

void bothSides(CRGBPalette16 pal) {
  uint16_t sin1 = beatsin16(2, 0, NUM_LEDS - 1, 0, 0);
  uint16_t sin2 = beatsin16(2, 0, NUM_LEDS - 1, 0, 32768);
  uint8_t color1 = beatsin8(2, 0, 255, 0, 0);
  uint8_t color2 = beatsin8(2, 0, 255, 0, 64);

  uint16_t sin3 = beatsin16(2, 0, NUM_LEDS2 - 1, 0, 23322);
  uint16_t sin4 = beatsin16(2, 0, NUM_LEDS2 - 1, 0, 9834);
  uint8_t color3 = beatsin8(2, 0, 255, 0, 32);
  uint8_t color4 = beatsin8(2, 0, 255, 0, 147);

  leds[sin1] = ColorFromPalette(pal, color1, brightness, LINEARBLEND);
  leds[sin2] = ColorFromPalette(pal, color2, brightness, LINEARBLEND);
  blur1d(leds, NUM_LEDS, 64);
  fadeToBlackBy(leds, NUM_LEDS, 10);

  leds2[sin3] = ColorFromPalette(pal, color3, brightness, LINEARBLEND);
  leds2[sin4] = ColorFromPalette(pal, color4, brightness, LINEARBLEND);
  blur1d(leds2, NUM_LEDS2, 64);
  fadeToBlackBy(leds2, NUM_LEDS2, 10);
}