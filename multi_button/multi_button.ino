// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

#define Buttons_Pressed 6

// constants won't change. They're used here to set pin numbers:
const int b1 = 6;       // the first button pin
const int b2 = 5;       // the second button pin
const int b3 = 4;       // the third button pin
const int b4 = 3;       // the fourth button pin
const int b5 = 2;       // the fifth button pin
const int l1 = 13;      // the lock pin
const int sleep = 1000; // set the sleep ms
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo lock;  // create servo object to control a servo

// Button states
int bs1 = 0;
int bs2 = 0;
int bs3 = 0;
int bs4 = 0;
int bs5 = 0;

int pos = 0;    // variable to store the servo position
bool locked = true;
char Data[Buttons_Pressed];
char Master[Buttons_Pressed] = "12345";
byte data_count = 0, master_count = 0;

void unlock_container() {
  lock.write(180);             // tell servo to go to position in variable 'my_pos'
  delay(15);                   // waits 15ms for the servo to reach the position
  push_buttons("Unlocked!");
  delay(sleep);
  locked = false;
}

void lock_container() {
  push_buttons("Locking now!");
  lock.write(90);
  delay(sleep);
  push_buttons("Locked!");
  delay(sleep);
  locked = true;
  push_buttons("");
}

void push_buttons(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push buttons!");
  lcd.setCursor(0, 1);
  lcd.print(message);
}

// Store the button press in the Data array
void store_button_press(char button) {
  Data[data_count] = button;
  lcd.setCursor(data_count,1);
  lcd.print(String(Data[data_count]));
  data_count++;
  delay(250);
}

void clear_data(){
  while(data_count !=0){
    Data[data_count--] = 0;
  }
  push_buttons("");
  return;
}

void button_puzzle() {
  // read the state of the pushbutton values
  bs1 = digitalRead(b1);
  bs2 = digitalRead(b2);
  bs3 = digitalRead(b3);
  bs4 = digitalRead(b4);
  bs5 = digitalRead(b5);

  if (locked) {
    if (bs1 == HIGH){
      store_button_press('1');
    }
    if (bs2 == HIGH){
      store_button_press('2');
    }
    if (bs3 == HIGH){
      store_button_press('3');
    }
    if (bs4 == HIGH){
      store_button_press('4');
    }
    if (bs5 == HIGH){
      store_button_press('5');
    }

    if(data_count == Buttons_Pressed-1){
      if (!strcmp(Data, Master)) {
        push_buttons("CORRECT!!!!!");
        unlock_container();
        delay(sleep+sleep);
        clear_data();
      } else {
        push_buttons("INCORRECT!");
        delay(sleep+sleep);
        clear_data();
      }
    }
  } else {
    lcd.setCursor(0,0);
    lcd.write("Push any button");
    lcd.setCursor(0,1);
    lcd.write("to lock the box!");
    // read the state of the pushbutton values:
    bs1 = digitalRead(b1);
    bs2 = digitalRead(b2);
    bs3 = digitalRead(b3);
    bs4 = digitalRead(b4);
    bs5 = digitalRead(b5);
    if ((bs1 || bs2 || bs3 || bs4 || bs5) == HIGH) {
      lock_container();
    }
  }
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the pushbutton pin as an input:
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  lock.attach(l1);  // attaches the servo on the l1 pin to the servo object
  lock_container();
  push_buttons("");
}

void loop() {
  button_puzzle();
}
