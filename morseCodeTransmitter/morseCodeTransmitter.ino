// Morse code - Transmitter
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C

// Delay between button pushes
const int unitDelay = 250;

// Define pins
const int buttonPin = 2;
const int transmissionPin = A5;
const int ledPin = 13;
const int buzzer = 3;

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
SSD1306AsciiAvrI2c oled;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(transmissionPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
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

void displayChar(String code) { //ugly part of the code but it works fine
                                //compare morse string to known morse values and print out the letter or a number 
                                //the code is written based on the international morse code, one thing i changed is that insted of typing a special string to end the line it happens with enough delay  
  if (code == ".-")
    oled.print("A");
  else if (code == "-...")  
    oled.print("B");
  else if (code == "-.-.")  
    oled.print("C");
  else if (code == "-..")  
    oled.print("D");
  else if (code == ".")  
    oled.print("E");
  else if (code == "..-.")  
    oled.print("F");
  else if (code == "--.")  
    oled.print("G");
  else if (code == "....")  
    oled.print("H");
  else if (code == "..")  
    oled.print("I");
  else if (code == ".---")  
    oled.print("J");
  else if (code == "-.-")  
    oled.print("K");
  else if (code == ".-..")  
    oled.print("L");
  else if (code == "--")  
    oled.print("M");
  else if (code == "-.")  
    oled.print("N");
  else if (code == "---")  
    oled.print("O");
  else if (code == ".--.")  
    oled.print("P");
  else if (code == "--.-")  
    oled.print("Q");
  else if (code == ".-.")  
    oled.print("R");
  else if (code == "...")  
    oled.print("S");
  else if (code == "-")  
    oled.print("T");
  else if (code == "..-")  
    oled.print("U");
  else if (code == "...-")  
    oled.print("V");
  else if (code == ".--")  
    oled.print("W");
  else if (code == "-..-")  
    oled.print("X");
  else if (code == "-.--")  
    oled.print("Y");
  else if (code == "--..")  
    oled.print("Z");
  else if (code == ".----")  
    oled.print("1");
  else if (code == "..---")  
    oled.print("2");
  else if (code == "...--")  
    oled.print("3");
  else if (code == "....-")  
    oled.print("4");
  else if (code == ".....")  
    oled.print("5");
  else if (code == "-....")
    oled.print("6");
  else if (code == "--...")  
    oled.print("7");
  else if (code == "---..")  
    oled.print("8");
  else if (code == "----.")  
    oled.print("9");
  else if (code == "-----")  
    oled.print("0");

  oled.print(" ");
  code=""; 
}
