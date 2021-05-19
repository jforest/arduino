// Morse code - Receiver
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C

// Delay between button pushes
const int unitDelay = 250;

// Define pins
const int receptionPin = 12;
const int ledPin = 13;

// Initial pin states
int ledState = LOW;
int receptionState = LOW;
int lastReceptionState = LOW;

long signalLength = 0;
long pause = 0;
String morse = "";
String dash = "-";
String dot = ".";

boolean checker = false;
boolean linechecker = false;

// Create the display object
SSD1306AsciiAvrI2c oled;

void setup() {
  pinMode(receptionPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);
  oled.setScrollMode(SCROLL_MODE_AUTO);
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Receiving Morse code!");
  oled.setCursor(0, 2);
}

void loop() {
  receptionState = digitalRead(receptionPin);

  if (receptionState && lastReceptionState) {
    ++signalLength;
  } else if (!receptionState && lastReceptionState) {
    if (signalLength > 50 && signalLength < unitDelay*2) {
      morse =  morse + dot;
    } else if (signalLength > unitDelay*2) {
      morse = morse + dash;
    }
    signalLength = 0;
    digitalWrite(ledPin, LOW);
  } else if (receptionState && !lastReceptionState) {
    pause=0;
    digitalWrite(ledPin, HIGH);
    checker = true;
    linechecker = true;
  } else if (!receptionState && !lastReceptionState) {
    ++pause;
    if (( pause > 3 * unitDelay ) && (checker)) {
      oled.print(morseDecode(morse));
      checker = false;
      morse = "";
    }
    if ((pause > 15 * unitDelay) && (linechecker)) {
      oled.print(" ");
      linechecker = false;
    }
  }
  lastReceptionState=receptionState;
  delay(1);
}

char morseDecode(String testCode) {
  static String morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
                           "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                           ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
                           "!"};
  for (int i = 0; i <= 26; i++) {
    delay(unitDelay/15);
    if (morse[i] == testCode) {
      return char('A' + i);
    } else if (morse[i] == "!") {
      return ' ';
    }
  }
}
