#include <LiquidCrystal.h>
#include <Keypad.h>

#define Password_Length 9

int signalPin = 40;

char Data[Password_Length]; 
char Master[Password_Length] = "01181903"; 
byte data_count = 0, master_count = 0;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;
const int rs = 52, en = 53, d4 = 51, d5 = 50, d6 = 49, d7 = 48;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {23, 25, 27, 29}; 
byte colPins[COLS] = {31, 33, 35, 37}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Enter Password:");
  lcd.setCursor(0,1);
  pinMode(signalPin, OUTPUT);
}
  
void loop(){  
  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
  }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.print("Correct");
      digitalWrite(signalPin, HIGH); 
      delay(5000);
      digitalWrite(signalPin, LOW);
      }
    else{
      lcd.print("Incorrect");
      delay(1000);
      }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  return;
}
