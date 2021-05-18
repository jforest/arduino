#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C

// this constant won't change. It's the pin number of the sensor's output:
const int blue = A0;
const int green = A1;
const int red = A2;
const int yellow = A3;
const int white = A4;

SSD1306AsciiAvrI2c oled;

// wire states
int blueState = 0, greenState = 0, redState = 0, yellowState = 0, whiteState = 0;

void setup() {
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(ZevvPeep8x16);
  oled.clear();
  pinMode(blue, INPUT);
  pinMode(green, INPUT);
  pinMode(red, INPUT);
  pinMode(yellow, INPUT);
  pinMode(white, INPUT);
  touchWires("");
}

void loop() {
  readTouches();

  if (blueState == LOW) {
    touchWires("BLUE");
    delay(1000);
    touchWires("");
  }
  if (greenState == LOW) {
    touchWires("GREEN");
    delay(1000);
    touchWires("");
  }
  if (redState == LOW) {
    touchWires("RED");
    delay(1000);
    touchWires("");
  }
  if (yellowState == LOW) {
    touchWires("YELLOW");
    delay(1000);
    touchWires("");
  }
  if (whiteState == LOW) {
    touchWires("WHITE");
    delay(1000);
    touchWires("");
  }
}

void readTouches() {
  // Read the button states
  blueState = digitalRead(blue);
  greenState = digitalRead(green);
  redState = digitalRead(red);
  yellowState = digitalRead(yellow);
  whiteState = digitalRead(white);
}

void touchWires(String message) {
  // Output the main push buttons text, with additional message line
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Touch Wires!");
  oled.setCursor(0, 2);
  oled.print(message);
}
