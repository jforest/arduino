
/*
 * sensoryOverload
 * 
 * Geocache puzzle, with a bunch of sensors, that must be triggered
 * in a specific order to open the box.
 * 
 * jforest 6/29/21
 */
#include <Wire.h> // Required Library
#include <LiquidCrystal_I2C.h> // Required Library

#define I2C_ADDRESS 0x27
#define NUM_LEDS 10

int datapin = 4;
int latchpin = 3;
int clockpin = 2;
boolean registers[NUM_LEDS];
int activatedSensors = 0;

LiquidCrystal_I2C lcd(I2C_ADDRESS,20, 4);

void setup() {
  // set the pins for output, then clear LEDs
  pinMode(datapin,OUTPUT);
  pinMode(latchpin,OUTPUT);
  pinMode(clockpin,OUTPUT);
  resetLeds();

  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Sensory Overload!");
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_LEDS; i++) {
    incrementLeds();
    delay(50);
    activatedSensors += 1;
  }
  delay(1000);
  resetLeds();
  activatedSensors = 0;
}


void incrementLeds() {
  /* Light up another led on the 10 segment display
   * If the display is now full, open the box */
   registers[activatedSensors] = HIGH;
   displayLeds();
   /*if (allSensorsActivated()) {
    puzzleSolved();
   }*/
}

void resetLeds() {
  /* Set the LEDS back to empty */
  for (int i = 0; i < NUM_LEDS; i++) {
    registers[i] = LOW;
  }
  displayLeds();
}

void displayLeds() {
  /* Actually light up (or not) the LEDs */
  digitalWrite(latchpin, LOW);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    digitalWrite(clockpin, LOW);
    digitalWrite(datapin, registers[i] );
    digitalWrite(clockpin, HIGH);
  }
  digitalWrite(latchpin, HIGH);
}

boolean allSensorsActivated() {
 /* Check to see if all the sensors are activated */
 for ( int i = 0;i < NUM_LEDS; i++) {
  if (registers[i] != HIGH) {
    return false;
  }
 }
 return true;
}

void puzzleSolved() {
  /* Print out success, and unlock the box */
}

void puzzle() {
  /* The actual puzzle, which sensor activated in which order */
}
