// blink_led_bar_74HC595_up_down.ino
// sketch for a 10-pins led bar using two 74HC595 shift registers
//
// modification of a sketch by stevenart
// by Floris Wouterlood
// public domain
// so use it freely and have fun
// November 15, 2019

#define NUM_LEDS 10

int datapin = 0;
int latchpin = 1;
int clockpin = 2;
boolean registers[NUM_LEDS];

void setup() {
  pinMode(datapin,OUTPUT);
  pinMode(latchpin,OUTPUT);
  pinMode(clockpin,OUTPUT);
  writereg();
}

void loop(){
  leds_stay_up();
  delay(500);
  leds_stay_down();
  delay(500);
}

// ============== subroutines =====================

void writereg() {
  digitalWrite(latchpin, LOW);
  for (int i = NUM_LEDS-1; i >= 0; i--)
  {
    digitalWrite(clockpin, LOW);
    digitalWrite(datapin, registers[i] );
    digitalWrite(clockpin, HIGH);
  }
  digitalWrite(latchpin, HIGH);
}

// ============== leds go down ====================

void leds_go_down () {
  for (int i = 0; i <  NUM_LEDS; i++)
  { 
    registers[(i)] = HIGH;
    writereg();
    delay(10);
    registers[(i)] = LOW;
    writereg();
    delay(10);
  }
}

// ============== leds go up =======================

void leds_go_up () {
  for (int i = NUM_LEDS-1; i >= 0; i--)
  {
    registers[(i)] = HIGH;
    delay(10);
    writereg();
    registers[(i)] = LOW;
    delay(10);
    writereg();
  }
}

// ============== leds stay up ======================

void leds_stay_up () {
  for (int i = 0; i < NUM_LEDS; i++)
  {
    registers[(i)] = HIGH;
    delay(10);
    writereg();
  }
}

// ============== leds stay down ======================

void leds_stay_down () {
  for (int i = NUM_LEDS; i > 0; i--)
  {
    registers[(i-1)] = LOW;
    delay(10);
    writereg();
  }
}
