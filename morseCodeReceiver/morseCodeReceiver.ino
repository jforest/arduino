// Morse code - Receiver
#include <Servo.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C
#define ANSWER_LENGTH 4

// Delay between button pushes
const int unitDelay = 250;

// Define pins
const int receptionPin = 12;
const int ledPin = 13;
const int lockPin = 2;

// servo positions
const int lockedPos = 90;    // locked position of servo
const int unlockedPos = 180; // unlocked position of servo

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
boolean locked = true;                  // is the container locked or not
char data[ANSWER_LENGTH];               // String received via morse code
char master[ANSWER_LENGTH] = "SOS";     // String needed to unlock the container
byte dataCount = 0;                     // number of chars received so far

// Create the display object and servo object
SSD1306AsciiAvrI2c oled;
Servo lock;

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
  lock.attach(lockPin);
  lockContainer();
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
      char result = morseDecode(morse);
      if (locked) {
        addChar(result);
      } else {
        lockContainer();
        clearData();
      }
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

void unlockContainer() {
  lock.write(unlockedPos);  // tell servo to go to unlocked position
  delay(15);                // waits 15ms for the servo to reach the position
  statusMessage("Unlocked!");
  delay(unitDelay*4);
  locked = false;
}

void lockContainer() {
  lock.write(lockedPos);  // tell the servo to go to the locked position
  delay(15);              // waits 15ms for the servo to reach the position
  statusMessage("Locked!");
  delay(unitDelay*4);
  locked = true;
}

void statusMessage(String message) {
  oled.setCursor(0, 5);
  oled.clearToEOL();
  oled.print(message);
  oled.setCursor(0, 2);
  oled.clearToEOL();
}

// Store the character in the data array
void storeChar(char value) {
  data[dataCount] = value;
  oled.setCursor(dataCount*5, 2);
  oled.print(String(data[dataCount]));
  dataCount++;
  delay(unitDelay/2);
}

void clearData() {
  while (dataCount != 0) {
    data[dataCount--] = 0;
  }
  return;
}

void addChar(char result) {
  storeChar(result);
  if (dataCount == ANSWER_LENGTH - 1) {
    if (!strcmp(data, master)) {
      statusMessage("CORRECT!!!!!");
      unlockContainer();
      oled.write("Send any code to lock");
      clearData();
    } else {
      statusMessage("INCORRECT!");
      clearData();
    }
  }
}
