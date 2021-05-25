// Morse code - Receiver
#include "RF24.h"
#include <nRF24L01.h>
#include <Servo.h>
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C
#define ANSWER_LENGTH 8

// Delay between button pushes
const int unitDelay = 250;

// Define pins
const int receptionPin = 12;
const int ledPin = 10;
const int lockPin = 2;
const int cePin = 7;
const int csnPin = 8;

// servo positions
const int lockedPos = 90;  // locked position of servo
const int unlockedPos = 180; // unlocked position of servo

// Initial pin states
int ledState = LOW;
int receptionState = LOW;
int lastReceptionState = LOW;

long signalLength = 0;
long pause = 0;
String morse = "";
String dash = "-";
String dot = ".";

boolean checker = false;
boolean linechecker = false;
boolean locked = true;                  // is the container locked or not
char data[ANSWER_LENGTH];               // String received via morse code
char master[ANSWER_LENGTH] = "MARCONI"; // String needed to unlock the container
byte dataCount = 0;                     // number of chars received so far

const byte rxAddress[5] = {'R','N','o','d','e'};

// Create the display object and servo object
SSD1306AsciiWire oled;
Servo lock;

// instantiate an object for the nRF24L01 transceiver
RF24 radio(cePin, csnPin);

void setup() {
  Wire.begin();
  Wire.setClock(400000L);

  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(ZevvPeep8x16);
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Decoding morse!");
  oled.setCursor(0, 2);
  pinMode(ledPin, OUTPUT);

  if (!radio.begin()) {
    oled.print("Rx not working");
    for ( int i = 0; i< 10; i++) {
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      delay(1000);
    }
  }

  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,rxAddress);
  radio.startListening();

  digitalWrite(ledPin, LOW);

  lock.attach(lockPin);
  lockContainer();
}

void loop() {
  char incomingMorse[32];                // Variable for morse code

  if(radio.available()) {
    while(radio.available()) {           // While there is data ready
      radio.read(&incomingMorse, sizeof(incomingMorse));        // Get the payload
    }
  }

  if (isArrayEmpty(incomingMorse)) {
    oled.print("array Empty");
  } else {
    oled.print(incomingMorse);
    char result = morseDecode(incomingMorse);
    if (locked) {
      addChar(result);
    } else {
      lockContainer();
      clearData();
    }
  }
}

char morseDecode(String testCode) {
  static String encoded[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
                             "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
                             ".----", "..---", "...--", "....-", ".....", "-....", "--...",
                             "---..","----.", "-----", ".-.-.-", "--..--", "-.-.-", "---...",
                             "..--..", ".----.", ".--.-.", "-.--.", "-.--.-", "-..-.", "-....-",
                             "-...-", "!"};
  static char decoded[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                           'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2',
                           '3', '4', '5', '6', '7', '8', '9', '0', '.', ',', ';', ':', '?', '\'',
                           '@', '(', ')', '/', '-', '='};

  for (int i = 0; i <= 48; i++) {
    delay(unitDelay/15);
    if (encoded[i] == testCode) {
      return decoded[i];
    } else if (encoded[i] == "!") {
      return ' ';
    }
  }
}

void unlockContainer() {
  lock.write(unlockedPos);  // tell servo to go to unlocked position
  delay(15);                // waits 15ms for the servo to reach the position
  statusMessage("Unlocked!");
  delay(unitDelay*4);
  locked = false;
}

void lockContainer() {
  lock.write(lockedPos);  // tell the servo to go to the locked position
  delay(15);              // waits 15ms for the servo to reach the position
  statusMessage("Locked!");
  delay(unitDelay*4);
  locked = true;
}

void statusMessage(String message) {
  oled.setCursor(0, 5);
  oled.clearToEOL();
  oled.print(message);
  oled.setCursor(0, 2);
  oled.clearToEOL();
}

// Store the character in the data array
void storeChar(char value) {
  data[dataCount] = value;
  oled.setCursor(dataCount*8, 2);
  oled.print(String(data[dataCount]));
  dataCount++;
  delay(unitDelay/2);
}

void clearData() {
  while (dataCount != 0) {
    data[dataCount--] = 0;
  }
  return;
}

void addChar(char result) {
  storeChar(result);
  if (dataCount == ANSWER_LENGTH - 1) {
    if (!strcmp(data, master)) {
      statusMessage("CORRECT!");
      unlockContainer();
      oled.write("Send any code");
      clearData();
    } else {
      statusMessage("INCORRECT!");
      clearData();
    }
  }
}

bool isArrayEmpty(char incomingMorse[]) {
 for (int i = 0; i<32; i++) {
  if (incomingMorse[i] != 0) {
    return false;
  }
 }
 return true;
}
