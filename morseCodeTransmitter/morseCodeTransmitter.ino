// Morse code - Transmitter
#include "RF24.h"
#include <nRF24L01.h>
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C
#define SCREEN_CHARS_WIDE 16

// Delay between button pushes
const int unitDelay = 250;

// Define pins
const int buttonPin = 9;
const int ledPin = 10;
const int buzzer = A0;
const int cePin = 7;
const int csnPin = 8;

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

const byte rxAddress[5] = {'R','N','o','d','e'};

// Create the display object
SSD1306AsciiWire oled;

// instantiate an object for the nRF24L01 transceiver
RF24 radio(cePin, csnPin);

void setup() {
  Wire.begin();
  Wire.setClock(400000L);

  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(ZevvPeep8x16);
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Enter Morse code");
  oled.setCursor(0, 2);

  if (!radio.begin()) {
    oled.print("Tx not working");
    for ( int i = 0; i< 10; i++) {
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      delay(1000);
    }
  }
  radio.setPALevel(RF24_PA_MIN);
  radio.setRetries(3,5); // delay, count
  radio.openWritingPipe(rxAddress);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  static String screenOutput = "";
  buttonState = digitalRead(buttonPin);

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
      screenOutput = morseOutput(morse, screenOutput);
      transmit(morse);
      checker = false;
      morse = "";
    }
    if ((pause > 15 * unitDelay) && (linechecker)) {
      linechecker = false;
    }
  }
  lastButtonState=buttonState;
  delay(1);
}

String morseOutput(String code, String screen) {
  if (screen.length() == 0) {
    screen = code;
  } else {
    screen += " " + code;
  }
  if (screen.length() >= SCREEN_CHARS_WIDE) {
    screen.remove(0, (screen.length() - SCREEN_CHARS_WIDE));
  }
  oled.setCursor(0,2);
  oled.clearToEOL();
  oled.print(screen);

  return screen;
}

void transmit(String payload) {
  char payloadInChars[32];
  payload.toCharArray(payloadInChars, 32); // we expect a 32 char array on the other side too
  if (!radio.write(&payloadInChars, sizeof(payloadInChars))) {
    oled.setCursor(0,5);
    oled.clearToEOL();
    oled.print("Failed to send");
  }
}
