/*
 *  Button Puzzle!
 *
 *  Jforest 05/16/2021
 *
 *  A challenging button puzzle to unlock the box to get to the log ond swag
 */

// include the library code:
#include <Servo.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C
#define ButtonsPressed 9
#define NumButtons 10

const int l1 = 13;           // the lock pin
const int s1 = A3;           // the sound input pin
const int sleep = 1000;      // base sleep time in ms
const int lockedPos = 90;    // locked position of servo
const int unlockedPos = 180; // unlocked position of servo
const int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // button pins


SSD1306AsciiAvrI2c oled;
Servo lock;

int buttonStates[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char buttonValues[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
bool locked = true;
char Data[ButtonsPressed]; // array of buttons pressed
char Master[ButtonsPressed] = "01181903"; // button presses to unlock
byte dataCount = 0; // number of buttons pressed so far

void setup() {
  // set up the display
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(ZevvPeep8x16);
  oled.clear();
  // initialize the pushbutton pins as an input
  for (int i = 0; i < NumButtons; i++) {
    pinMode(i, INPUT);
  }
  lock.attach(l1);  // attaches the servo on the l1 pin to the servo object
  lockContainer();
  pushButtons("");
}

void loop() {
  buttonPuzzle();
}

void unlockContainer() {
  lock.write(unlockedPos);  // tell servo to go to unlocked position
  delay(15);                // waits 15ms for the servo to reach the position
  pushButtons("Unlocked!");
  delay(sleep);
  locked = false;
  pushButtons("");
}

void lockContainer() {
  pushButtons("Locking now!");
  lock.write(lockedPos);  // tell the servo to go to the locked position
  delay(15);              // waits 15ms for the servo to reach the position
  pushButtons("Locked!");
  delay(sleep);
  locked = true;
  pushButtons("");
}

void pushButtons(String message) {
  // Output the main push buttons text, with additional message line
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Push buttons!");
  oled.setCursor(0, 2);
  oled.print(message);
}

// Store the button press in the Data array
void storeButtonPress(char button) {
  Data[dataCount] = button;
  oled.setCursor(dataCount*8, 2);
  oled.print(String(Data[dataCount]));
  dataCount++;
  delay(sleep/4);
}

void clearData() {
  while (dataCount != 0) {
    Data[dataCount--] = 0;
  }
  pushButtons("");
  return;
}

void readButtons() {
  for (int i = 0; i < NumButtons; i++) {
    buttonStates[i] = digitalRead(buttons[i]);
  }
}

void buttonPuzzle() {
  // read the state of the pushbutton values
  readButtons();

  if (locked) {
    for (int i = 0; i < NumButtons; i++) {
      if (buttonStates[i] == HIGH) {
        storeButtonPress(buttonValues[i]);
      }
    }


    if (dataCount == ButtonsPressed - 1) {
      if (!strcmp(Data, Master)) {
        pushButtons("CORRECT!!!!!");
        unlockContainer();
        delay(sleep*2);
        clearData();
        oled.clear();
      } else {
        pushButtons("INCORRECT!");
        delay(sleep*2);
        clearData();
      }
    }
  } else {
    oled.setCursor(0, 2);
    oled.write("Push any button");
    oled.setCursor(0, 4);
    oled.write("to lock the box!");

    // read the state of the pushbutton values:
    readButtons();

    for (int i = 0; i < NumButtons; i++) {
      if (buttonStates[i] == HIGH) {
        lockContainer();
      }
    }
  }
}
