/* 
 *  Button Puzzle!
 *  
 *  Jforest 05/16/2021
 *  
 *  A challenging button puzzle to unlock the box to get to the log ond swag
 */

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

#define ButtonsPressed 8

// button pins
const int b1 = A1, b2 = A2, b3 = A3, b4 = A4, b5 = A5, b6 = 6, b7 = 5, b8 = 4, b9 = 3, b10 = 2;
// the lock pin
const int l1 = 13;
// base sleep time in ms
const int sleep = 1000;
// LCD pins
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
// speaker pin
const int speakerPin = A0;
// locked position of servo
const int lockedPos = 90;
// unlocked position of servo
const int unlockedPos = 180;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo lock;

// Button states
int bs1 = 0, bs2 = 0, bs3 = 0, bs4 = 0, bs5 = 0, bs6 = 0, bs7 = 0, bs8 = 0, bs9 = 0, bs10 = 0;
// locked or not
bool locked = true;
// array of buttons pressed
char Data[ButtonsPressed];
// button presses to unlock
char Master[ButtonsPressed] = "MARCONI";
// number of buttons pressed so far
byte dataCount = 0;

void setup() {
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // initialize the pushbutton pins as an input
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);
  pinMode(b8, INPUT);
  pinMode(b9, INPUT);
  pinMode(b10, INPUT);
  lock.attach(l1);  // attaches the servo on the l1 pin to the servo object
  lockContainer();
  pushButtons("");
}

void loop() {
  buttonPuzzle();
}

void pushButtons(String message) {
  // Output the main push buttons text, with additional message line
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push buttons!");
  lcd.setCursor(0, 1);
  lcd.print(message);
}

void buttonPuzzle() {
  // In here is the actual puzzle
    // read the state of the pushbutton values
  readButtons();

  if (locked) {
    if ((bs1 == HIGH) && (bs2 == HIGH)) {
      storeButtonPress('A');
    }
    else if ((bs2 == HIGH) && (bs3 == HIGH)) {
      storeButtonPress('B');
    }
    else if ((bs3 == HIGH) && (bs4 == HIGH)) {
      storeButtonPress('C');
    }
    else if ((bs4 == HIGH) && (bs5 == HIGH)) {
      storeButtonPress('D');
    }
    else if ((bs5 == HIGH) && (bs6 == HIGH)) {
      storeButtonPress('E');
    }
    else if ((bs6 == HIGH) && (bs7 == HIGH)) {
      storeButtonPress('F');
    }
    else if ((bs7 == HIGH) && (bs8 == HIGH)) {
      storeButtonPress('G');
    }
    else if ((bs8 == HIGH) && (bs9 == HIGH)) {
      storeButtonPress('H');
    }
    else if ((bs9 == HIGH) && (bs10 == HIGH)) {
      storeButtonPress('I');
    }
    else if ((bs1 == HIGH) && (bs3 == HIGH)) {
      storeButtonPress('J');
    }
    else if ((bs2 == HIGH) && (bs4 == HIGH)) {
      storeButtonPress('K');
    }
    else if ((bs3 == HIGH) && (bs5 == HIGH)) {
      storeButtonPress('L');
    }
    else if ((bs4 == HIGH) && (bs6 == HIGH)) {
      storeButtonPress('M');
    }
    else if ((bs5 == HIGH) && (bs7 == HIGH)) {
      storeButtonPress('N');
    }
    else if ((bs6 == HIGH) && (bs8 == HIGH)) {
      storeButtonPress('O');
    }
    else if ((bs7 == HIGH) && (bs9 == HIGH)) {
      storeButtonPress('P');
    }
    else if ((bs8 == HIGH) && (bs10 == HIGH)) {
      storeButtonPress('Q');
    }
    else if ((bs1 == HIGH) && (bs4 == HIGH)) {
      storeButtonPress('R');
    }
    else if ((bs2 == HIGH) && (bs5 == HIGH)) {
      storeButtonPress('S');
    }
    else if ((bs3 == HIGH) && (bs6 == HIGH)) {
      storeButtonPress('T');
    }
    else if ((bs4 == HIGH) && (bs7 == HIGH)) {
      storeButtonPress('U');
    }
    else if ((bs5 == HIGH) && (bs8 == HIGH)) {
      storeButtonPress('V');
    }
    else if ((bs6 == HIGH) && (bs9 == HIGH)) {
      storeButtonPress('W');
    }
    else if ((bs7 == HIGH) && (bs10 == HIGH)) {
      storeButtonPress('X');
    }
    else if ((bs1 == HIGH) && (bs5 == HIGH)) {
      storeButtonPress('Y');
    }
    else if ((bs2 == HIGH) && (bs6 == HIGH)) {
      storeButtonPress('Z');
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
    lcd.setCursor(0, 0);
    lcd.write("Push any button");
    lcd.setCursor(0, 1);
    lcd.write("to lock the box!");

    // read the state of the pushbutton values:
    readButtons();

    // If any of them are HIGH, lock the container
    if ((bs1 || bs2 || bs3 || bs4 || bs5 || bs6 || bs7 || bs8 || bs9 || bs10) == HIGH) {
      lockContainer();
    }
  }
}

void readButtons() {
  // Read the button states
  bs1 = digitalRead(b1);
  bs2 = digitalRead(b2);
  bs3 = digitalRead(b3);
  bs4 = digitalRead(b4);
  bs5 = digitalRead(b5);
  bs6 = digitalRead(b6);
  bs7 = digitalRead(b7);
  bs8 = digitalRead(b8);
  bs9 = digitalRead(b9);
  bs10 = digitalRead(b10);
}


// Store the button press in the Data array
void storeButtonPress(char button) {
  Data[dataCount] = button;
  lcd.setCursor(dataCount, 1);
  lcd.print(String(Data[dataCount]));
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
