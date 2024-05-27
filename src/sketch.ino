#include <LiquidCrystal.h>
#include "icons.h"
#include "semState.h"

const int led = 10;
const int yellow_led = 9;
const int green_led = 8;

const int btn_princ = 5;
const int btn_sec = 6;

const int dataPin = 2;   /* DS */
const int clockPin = 3;  /* SHCP */
const int latchPin = 4;  /* STCP */

//                       left       l to r      right      r to 
static int semVec[] = { 0b1001000, 0b0101000, 0b0010010, 0b0010100};
static int lenSemVec = 4;
enum semState semStatus = 0;
static int loopIter = 0;

static int timer = 500;

//LCD Display
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void changeSemState(const int state) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, state);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  lcd.begin(20, 4);
  init_icons(lcd);
  update_display(semStatus);
  pinMode(btn_princ, INPUT_PULLUP);
  pinMode(btn_sec, INPUT_PULLUP);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  loopIter = 0;
}

uint8_t handle_buttons(enum semState state) {
  if(digitalRead(btn_princ) == LOW && state == RIGHT) return 1;
  if(digitalRead(btn_sec) == LOW && state == LEFT) return 1;
  return 0;
}

void update_display(enum semState state) {
  lcd.clear();
  switch(state) {
    case LEFT:
      lcd.setCursor(0,0);
      lcd.print("< MERGETI!");
      lcd.setCursor(12,3);
      lcd.print("STATI! >");
      return;
    case RIGHT:
      lcd.setCursor(0, 0);
      lcd.print("< STATI!");
      lcd.setCursor(10,3);
      lcd.print("MERGETI! >");
      return;
  }
}

void loop() {
  changeSemState(semVec[semStatus]);
  if(handle_buttons(semStatus)) {
    incr(&semStatus);
    changeSemState(semVec[semStatus]);
    delay(timer*2);
    incr(&semStatus);
    update_display(semStatus);
  }
}
