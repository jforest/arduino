// Morse code - Receiver
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C

const int dot = 4;
const int dash = 3;
const int enter = 2;
const int led = 13;
const int unitDelay = 250;
int dotState = 0;
int dashState = 0;
int enterState = 0;

SSD1306AsciiAvrI2c oled;

void setup() {
  pinMode(dot, INPUT);
  pinMode(dash, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);
  oled.setScrollMode(SCROLL_MODE_AUTO);
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Enter Morse code!");
}

void loop() {
  static String code = "";
  readButtons();
  if (enterState == HIGH) {
    MorseDecode(code);
    code = "";
  }
  if (dotState == HIGH) {
    code += '.';
    pushButtons(code);
    flashLED(led, unitDelay);
  } else if (dashState == HIGH) {
    code += '-';
    pushButtons(code);
    flashLED(led, unitDelay*2);
  }
}

void flashLED(int ledPin, int flashDelay) {
    digitalWrite(ledPin, HIGH);
    delay(flashDelay*2);
    digitalWrite(ledPin, LOW);
}

bool MorseDecode(String testCode) {
  static String morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
                           "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                           ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
                           "0"};
  bool matched = false;
  for (int i = 0; i <= 26; i++) {
    delay(unitDelay/15);
    if (morse[i] == testCode) {
      pushButtons(String(char('A' + i)));
      matched = true;
      break;
    } else if (morse[i] == "0") {
      morseError("No matching code!");
      break;
    }
  }
  return matched;
}

void pushButtons(String message) {
  // Output the main push buttons text, with additional message line
  oled.setCursor(0, 2);
  oled.clearToEOL();
  oled.print(message);
}

void morseError(String message) {
  oled.setCursor(0, 4);
  oled.clearToEOL();
  oled.print(message);
}

void readButtons() {
  dotState = digitalRead(dot);
  dashState = digitalRead(dash);
  enterState = digitalRead(enter);
}
