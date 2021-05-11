// include the library code:
#include <LiquidCrystal.h>

// constants won't change. They're used here to set pin numbers:
const int buttonZero = 6;    // the zeroth button pin
const int buttonOne = 5;     // the first button pin
const int buttonTwo = 4;     // the second button pin
const int buttonThree = 3;   // the third button pin
const int buttonFour = 2;    // the fourth button pin

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// variables will change:
int buttonState0 = 0;
int buttonState1 = 0;        // variable for reading the pushbutton status
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Push buttons!");
  // initialize the pushbutton pin as an input:
  pinMode(buttonZero, INPUT);
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(buttonThree, INPUT);
  pinMode(buttonFour, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState0 = digitalRead(buttonZero);
  buttonState1 = digitalRead(buttonOne);
  buttonState2 = digitalRead(buttonTwo);
  buttonState3 = digitalRead(buttonThree);
  buttonState4 = digitalRead(buttonFour);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //if ((buttonState0 || buttonState1 || buttonState2 || buttonState3) == HIGH) {
  if ((buttonState0 && buttonState2) == HIGH) {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    lcd.print("0 and 2! GOOD!");
    delay(2000);
    lcd.clear();
  }
  if ((buttonState1 && buttonState3) == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("1 and 3! BAD!");
    delay(2000);
    lcd.clear();
  }
  if (buttonState4 == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("5 is the best!");
    delay(2000);
    lcd.clear();
  }
}
