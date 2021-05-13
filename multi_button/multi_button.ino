// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

#define ButtonsPressed 9
#define NumButtons 10

// constants won't change. They're used here to set pin numbers:
const int b1 = A1;       // the first button pin
const int b2 = A2;       // the second button pin
const int b3 = A3;       // the third button pin
const int b4 = A4;       // the fourth button pin
const int b5 = A5;       // the fifth button pin
const int b6 = 6;
const int b7 = 5;
const int b8 = 4;
const int b9 = 3;
const int b10 = 2;
const int l1 = 13;      // the lock pin
const int sleep = 1000; // set the sleep ms
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
const int speakerPin = A0; // speaker output
const int lockedPos = 90; // position of the servo when locked
const int unlockedPos = 180; // position of the servo when unlocked

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo lock;  // create servo object to control a servo

// Button states
int bs1 = 0, bs2 = 0, bs3 = 0, bs4 = 0, bs5 = 0, bs6 = 0, bs7 = 0, bs8 = 0, bs9 = 0, bs10 = 0;

bool locked = true;
char Data[ButtonsPressed];
char Master[ButtonsPressed] = "1*1*1*1*";
byte dataCount = 0, masterCount = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the pushbutton pin as an input:
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

void unlockContainer() {
  lock.write(unlockedPos);  // tell servo to go to position in variable 'my_pos'
  delay(15);                // waits 15ms for the servo to reach the position
  pushButtons("Unlocked!");
  delay(sleep);
  locked = false;
}

void lockContainer() {
  pushButtons("Locking now!");
  lock.write(lockedPos);
  delay(sleep);
  pushButtons("Locked!");
  delay(sleep);
  locked = true;
  pushButtons("");
}

void pushButtons(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push buttons!");
  lcd.setCursor(0, 1);
  lcd.print(message);
}

// Store the button press in the Data array
void storeButtonPress(char button) {
  Data[dataCount] = button;
  lcd.setCursor(dataCount, 1);
  lcd.print(String(Data[dataCount]));
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

void buttonPuzzle() {
  // read the state of the pushbutton values
  readButtons();

  if (locked) {
    if (bs1 == HIGH) {
      storeButtonPress('1');
    }
    if (bs2 == HIGH) {
      storeButtonPress('2');
    }
    if (bs3 == HIGH) {
      storeButtonPress('3');
    }
    if (bs4 == HIGH) {
      storeButtonPress('4');
    }
    if (bs5 == HIGH) {
      storeButtonPress('5');
    }
    if (bs6 == HIGH) {
      storeButtonPress('6');
    }
    if (bs7 == HIGH) {
      storeButtonPress('7');
    }
    if (bs8 == HIGH) {
      storeButtonPress('8');
    }
    if (bs9 == HIGH) {
      storeButtonPress('9');
    }
    if (bs10 == HIGH) {
      storeButtonPress('*');
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

    if ((bs1 || bs2 || bs3 || bs4 || bs5 || bs6 || bs7 || bs8 || bs9 || bs10) == HIGH) {
      lockContainer();
    }
  }
}
