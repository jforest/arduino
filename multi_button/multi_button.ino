// include the library code:
#include <LiquidCrystal.h>

// constants won't change. They're used here to set pin numbers:
const int b1 = 6;    // the first button pin
const int b2 = 5;    // the second button pin
const int b3 = 4;    // the third button pin
const int b4 = 3;    // the fourth button pin
const int b5 = 2;    // the fifth button pin

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Button states
int bs1 = 0;
int bs2 = 0;
int bs3 = 0;
int bs4 = 0;
int bs5 = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Push buttons!");
  // initialize the pushbutton pin as an input:
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
}

void loop() {
  // read the state of the pushbutton values:
  bs1 = digitalRead(b1);
  bs2 = digitalRead(b2);
  bs3 = digitalRead(b3);
  bs4 = digitalRead(b4);
  bs5 = digitalRead(b5);

  // check if the pushbuttons are pressed. If it is, the buttonState is HIGH:
  if ((bs1 && bs3) == HIGH) {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    lcd.print("1 and 3! GOOD!");
    delay(2000);
    lcd.clear();
  }
  if ((bs2 && bs4) == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("2 and 4! BAD!");
    delay(2000);
    lcd.clear();
  }
  if (bs5 == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("5 is the best!");
    delay(2000);
    lcd.clear();
  }
}
