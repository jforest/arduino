// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

// constants won't change. They're used here to set pin numbers:
const int b1 = 6;    // the first button pin
const int b2 = 5;    // the second button pin
const int b3 = 4;    // the third button pin
const int b4 = 3;    // the fourth button pin
const int b5 = 2;    // the fifth button pin
const int l1 = 13;   // the lock pin
const int sleep = 1000; // set the sleep ms

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo lock;  // create servo object to control a servo

// Button states
int bs1 = 0;
int bs2 = 0;
int bs3 = 0;
int bs4 = 0;
int bs5 = 0;

int pos = 0;    // variable to store the servo position

void unlock() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    lock.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void push_buttons(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push buttons!");
  lcd.setCursor(0, 1);
  lcd.print(message);
}

void button_puzzle() {
  // read the state of the pushbutton values:
  bs1 = digitalRead(b1);
  bs2 = digitalRead(b2);
  bs3 = digitalRead(b3);
  bs4 = digitalRead(b4);
  bs5 = digitalRead(b5);

  // check if the pushbuttons are pressed. If it is, the buttonState is HIGH:
  if ((bs1 && bs3) == HIGH) {
    push_buttons("1 and 3! GOOD!");
    delay(sleep);
    push_buttons("BUT, wrong.");
  }
  if ((bs2 && bs4) == HIGH) {
    push_buttons("2 and 4! BAD!");
    delay(sleep);
    push_buttons("WRONGGGGGG!");
  }
  if (bs5 == HIGH) {
    push_buttons("5 is the best!");
    delay(sleep);
    push_buttons("YOU WIN!");
    unlock();
    push_buttons("Unlocked!");
  }
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  push_buttons("");
  // initialize the pushbutton pin as an input:
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  lock.attach(l1);  // attaches the servo on the l1 pin to the servo object
}

void loop() {
  button_puzzle();
}
