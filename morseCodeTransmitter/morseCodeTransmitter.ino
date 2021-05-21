// Morse code - Transmitter
#include "Wire.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C

// Delay between button pushes
const int unitDelay = 250;

// Define pins
const int buttonPin = 13;
const int transmissionPin = 12;
const int ledPin = 8;
const int buzzer = A0;

// Initial pin states
int ledState = LOW;
int buttonState = LOW;
int lastButtonState = LOW;

long signalLength = 0;
long pause = 0;
String morse = "";
String dash = "-";
String dot = ".";

boolean checker = false;
boolean linechecker = false;

// Create the display object
SSD1306AsciiWire oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(transmissionPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);
  oled.setScrollMode(SCROLL_MODE_AUTO);
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Enter Morse code!");
  oled.setCursor(0, 2);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(transmissionPin, buttonState); // send the button state to the radio
  
  if (buttonState && lastButtonState) {
    ++signalLength;
    if (signalLength < unitDelay*2) {
      tone(buzzer, 1500);
    } else {
      tone(buzzer, 1000);
    }
  } else if (!buttonState && lastButtonState) {
    if (signalLength > 50 && signalLength < unitDelay*2) {
      morse =  morse + dot;
    } else if (signalLength > unitDelay*2) {
      morse = morse + dash;
    }
    signalLength = 0;
    digitalWrite(ledPin, LOW);
    noTone(buzzer);
  } else if (buttonState && !lastButtonState) {
    pause=0;
    digitalWrite(ledPin, HIGH);
    checker = true;
    linechecker = true;
  } else if (!buttonState && !lastButtonState) {
    ++pause;
    if (( pause > 3 * unitDelay ) && (checker)) {
      oled.print(morse+" ");
      checker = false;
      morse = "";
    }
    if ((pause > 15 * unitDelay) && (linechecker)) {
      oled.print(" ");
      linechecker = false;
    }
  }
  lastButtonState=buttonState;
  delay(1);
}
