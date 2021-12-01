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

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,     0,  0,  0,   //black
128,   255,  0,  0,   //red
224,   255,255,  0,   //bright yellow
255,   255,255,255 }; //full white

CRGBPalette16 heatPal = heatmap_gp;


CRGBPalette16 brightChristmasPal = CRGBPalette16 (
  CRGB::Black,
  CRGB::Black,

  CRGB::Blue,
  CRGB::Blue,

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
    scheme = random(0, 6);
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
      runningRainbow(hanukkahPal);
      break;
    case 2:
      runningRainbow(brightChristmasPal);
      break;
    case 3:
      randomLights(hanukkahPal);
      break;
    case 4:
      runningRainbow(christmasPal);
      break;
    case 5:
      randomLights(christmasPal);
      break;
    default:
      runningRainbow(christmasPal);
      break;
  }
}

void randomLights(CRGBPalette16 pal) {
    EVERY_N_MILLISECONDS(25) {
      leds[random(0, NUM_LEDS - 1)] = ColorFromPalette(pal, random8(), 255, LINEARBLEND);
    }
    fadeToBlackBy(leds, NUM_LEDS, 1);
    FastLED.show();
}

void runningRainbow(CRGBPalette16 pal) {
  fill_palette(leds, NUM_LEDS, paletteIndex, 255, pal, 255, LINEARBLEND);
  EVERY_N_MILLISECONDS(25) {
    paletteIndex++;
  }
  FastLED.show();
}