// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

#define Buttons_Pressed 9

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

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo lock;  // create servo object to control a servo

// Button states
int bs1 = 0, bs2 = 0, bs3 = 0, bs4 = 0, bs5 = 0, bs6 = 0, bs7 = 0, bs8 = 0, bs9 = 0, bs10 = 0;

// led output
int signalPin = A0;

bool locked = true;
char Data[Buttons_Pressed];
char Master[Buttons_Pressed] = "1*1*1*1*";
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

void read_buttons() {
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

void button_puzzle() {
  // read the state of the pushbutton values
  read_buttons();

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
    if (bs6 == HIGH){
      store_button_press('6');
    }
    if (bs7 == HIGH){
      store_button_press('7');
    }
    if (bs8 == HIGH){
      store_button_press('8');
    }
    if (bs9 == HIGH){
      store_button_press('9');
    }
    if (bs10 == HIGH){
      store_button_press('*');
    }

    if(data_count == Buttons_Pressed-1){
      if (!strcmp(Data, Master)) {
        push_buttons("CORRECT!!!!!");
        unlock_container();
        delay(sleep+sleep);
        clear_data();
      } else {
        push_buttons("INCORRECT!");
        digitalWrite(signalPin, HIGH); 
        delay(5000);
        digitalWrite(signalPin, LOW);
        clear_data();
      }
    }
  } else {
    lcd.setCursor(0,0);
    lcd.write("Push any button");
    lcd.setCursor(0,1);
    lcd.write("to lock the box!");
    
    // read the state of the pushbutton values:
    read_buttons();
    
    if ((bs1 || bs2 || bs3 || bs4 || bs5 || bs6 || bs7 || bs8 || bs9 || bs10) == HIGH) {
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
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);
  pinMode(b8, INPUT);
  pinMode(b9, INPUT);
  pinMode(b10, INPUT);
  lock.attach(l1);  // attaches the servo on the l1 pin to the servo object
  lock_container();
  push_buttons("");
}

void loop() {
  button_puzzle();
}
