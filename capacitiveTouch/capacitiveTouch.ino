#include <LiquidCrystal.h>

// this constant won't change. It's the pin number of the sensor's output:
const int blue = A0;
const int green = A1;
const int red = A2;
const int yellow = A3;
const int white = A4;
const int rs = 52, en = 53, d4 = 51, d5 = 50, d6 = 49, d7 = 48;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// wire states
int blueState = 0, greenState = 0, redState = 0, yellowState = 0, whiteState = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(blue, INPUT);
  pinMode(green, INPUT);
  pinMode(red, INPUT);
  pinMode(yellow, INPUT);
  pinMode(white, INPUT);
  lcd.print("Touch Wires!");
}

void loop() {
  readTouches();

  if (blueState == LOW) {
    touchWires("BLUE");
    delay(1000);
    touchWires("");
  }
  if (greenState == LOW) {
    touchWires("GREEN");
    delay(1000);
    touchWires("");
  }
  if (redState == LOW) {
    touchWires("RED");
    delay(1000);
    touchWires("");
  }
  if (yellowState == LOW) {
    touchWires("YELLOW");
    delay(1000);
    touchWires("");
  }
  if (whiteState == LOW) {
    touchWires("WHITE");
    delay(1000);
    touchWires("");
  }
}

void readTouches() {
  // Read the button states
  blueState = digitalRead(blue);
  greenState = digitalRead(green);
  redState = digitalRead(red);
  yellowState = digitalRead(yellow);
  whiteState = digitalRead(white);
}

void touchWires(String message) {
  // Output the main push buttons text, with additional message line
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Touch Wires!");
  lcd.setCursor(0, 1);
  lcd.print(message);
}
