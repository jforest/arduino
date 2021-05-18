/* 
 *  Button Puzzle!
 *  
 *  Jforest 05/16/2021
 *  
 *  A challenging button puzzle to unlock the box to get to the log ond swag
 */

// include the library code:
#include <Bounce2.h>
#include <Servo.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C
#define ButtonsPressed 9

// button pins
const int b1 = 2, b2 = 3, b3 = 4, b4 = 5, b5 = 6, b6 = 7, b7 = 8, b8 = 9, b9 = 10, b10 = 11;
// the lock pin
const int l1 = 13;
// base sleep time in ms
const int sleep = 1000;
// button debounce time
const int buttonSleep = 5;
// LCD pins
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
// speaker pin
const int speakerPin = A0;
// locked position of servo
const int lockedPos = 90;
// unlocked position of servo
const int unlockedPos = 180;

SSD1306AsciiAvrI2c oled;
Servo lock;
Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();
Bounce2::Button button5 = Bounce2::Button();
Bounce2::Button button6 = Bounce2::Button();
Bounce2::Button button7 = Bounce2::Button();
Bounce2::Button button8 = Bounce2::Button();
Bounce2::Button button9 = Bounce2::Button();
Bounce2::Button button10 = Bounce2::Button();

// locked or not
bool locked = true;
// array of buttons pressed
char Data[ButtonsPressed];
// button presses to unlock
char Master[ButtonsPressed] = "01181903";
// number of buttons pressed so far
byte dataCount = 0;

void setup() {
  // set up the display
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(ZevvPeep8x16);
  oled.clear();
  // initialize the pushbutton pins as an input
  button1.attach( b1, INPUT );
  button2.attach( b2, INPUT );
  button3.attach( b3, INPUT );
  button4.attach( b4, INPUT );
  button5.attach( b5, INPUT );
  button6.attach( b6, INPUT );
  button7.attach( b7, INPUT );
  button8.attach( b8, INPUT );
  button9.attach( b9, INPUT );
  button10.attach( b10, INPUT );
  // set the debounce sleep time on each button
  button1.interval(buttonSleep);
  button2.interval(buttonSleep);
  button3.interval(buttonSleep);
  button4.interval(buttonSleep);
  button5.interval(buttonSleep);
  button6.interval(buttonSleep);
  button7.interval(buttonSleep);
  button8.interval(buttonSleep);
  button9.interval(buttonSleep);
  button10.interval(buttonSleep);
  // signal is HIGH when button is pressed
  button1.setPressedState(HIGH);
  button2.setPressedState(HIGH);
  button3.setPressedState(HIGH);
  button4.setPressedState(HIGH);
  button5.setPressedState(HIGH);
  button6.setPressedState(HIGH);
  button7.setPressedState(HIGH);
  button8.setPressedState(HIGH);
  button9.setPressedState(HIGH);
  button10.setPressedState(HIGH);
  lock.attach(l1);  // attaches the servo on the l1 pin to the servo object
  lockContainer();
  pushButtons("");
}

void loop() {
  buttonPuzzle();
}

void pushButtons(String message) {
  // Output the main push buttons text, with additional message line
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Push buttons!");
  oled.setCursor(0, 2);
  oled.print(message);
}

void buttonPuzzle() {
  // In here is the actual puzzle
  // read the state of the pushbutton values
  readButtons();

  if (locked) {
    if (button1.pressed()) {
      storeButtonPress('1');
    }
    else if (button2.pressed()) {
      storeButtonPress('2');
    }
    else if (button3.pressed()) {
      storeButtonPress('3');
    }
    else if (button4.pressed()) {
      storeButtonPress('4');
    }
    else if (button5.pressed()) {
      storeButtonPress('5');
    }
    else if (button6.pressed()) {
      storeButtonPress('6');
    }
    else if (button7.pressed()) {
      storeButtonPress('7');
    }
    else if (button8.pressed()) {
      storeButtonPress('8');
    }
    else if (button9.pressed()) {
      storeButtonPress('9');
    }
    else if (button10.pressed()) {
      storeButtonPress('0');
    }

    if (dataCount == ButtonsPressed - 1) {
      if (!strcmp(Data, Master)) {
        pushButtons("CORRECT!!!!!");
        unlockContainer();
        delay(sleep*2);
        clearData();
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

    // If any of them are HIGH, lock the container
    if (button1.pressed() || button2.pressed() || button3.pressed() || button4.pressed() || button5.pressed() || button6.pressed() || button7.pressed() || button8.pressed() || button9.pressed() || button10.pressed()) {
      lockContainer();
    }
  }
}

void readButtons() {
  // Read the button states
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
  button7.update();
  button9.update();
  button9.update();
  button10.update();
}


// Store the button press in the Data array
void storeButtonPress(char button) {
  Data[dataCount] = button;
  oled.setCursor(dataCount*8, 2);
  oled.print(String(Data[dataCount]));
  dataCount++;
  delay(sleep/4);
}

// Clear the data from the data array
void clearData() {
  while (dataCount != 0) {
    Data[dataCount--] = 0;
  }
  pushButtons("");
  return;
}

void unlockContainer() {
  // unlock the container!
  lock.write(unlockedPos);  // tell servo to go to unlocked position
  delay(15);                // waits 15ms for the servo to reach the position
  pushButtons("Unlocked!");
  delay(sleep);
  locked = false;
  pushButtons("");
}

void lockContainer() {
  // lock the container!
  pushButtons("Locking now!");
  lock.write(lockedPos);  // tell the servo to go to the locked position
  delay(15);              // waits 15ms for the servo to reach the position
  pushButtons("Locked!");
  delay(sleep);
  locked = true;
  pushButtons("");
}
