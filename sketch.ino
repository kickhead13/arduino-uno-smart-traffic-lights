
const int led = 10;
const int yellow_led = 9;
const int green_led = 8;


const int semaphore_sec[] = {10, 9, 8};
const int semaphore_princ[] = {13, 12, 11};

const int btn_princ = 4;
const int btn_sec = 3;

const int btn_princ_pressed = 0;
const int btn_sec_pressed = 0;

static int semaphore_state = 1;

static int a = 1;
static int b = 1;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //digitalWrite(led, HIGH);
  pinMode(btn_princ, INPUT_PULLUP);
  pinMode(btn_sec, INPUT_PULLUP);

  digitalWrite(semaphore_princ[0], HIGH);
  digitalWrite(semaphore_sec[2], HIGH);

}

void switch_semaphore_state() {

  if (semaphore_state == 1) {
    // switch sec. sem. from green to yellow and then to red
    digitalWrite(semaphore_sec[2], LOW);
    digitalWrite(semaphore_sec[1], HIGH);
    delay(2000);
    digitalWrite(semaphore_sec[1], LOW);
    digitalWrite(semaphore_sec[0], HIGH);

    // switch princ. sem. from red to green
    digitalWrite(semaphore_princ[0], LOW);
    digitalWrite(semaphore_princ[2], HIGH);
  } else {
    // switch princ. sem. from green to yellow and then to red
    digitalWrite(semaphore_princ[2], LOW);
    digitalWrite(semaphore_princ[1], HIGH);
    delay(2000);
    digitalWrite(semaphore_princ[1], LOW);
    digitalWrite(semaphore_princ[0], HIGH);

    // switch sec. sem. from red to green
    digitalWrite(semaphore_sec[0], LOW);
    digitalWrite(semaphore_sec[2], HIGH);
  }
  semaphore_state *= -1;

}

void handle_leds() {

  //switch_semaphore_state();
  //delay(5000);

}

void handle_buttons() {

  if(digitalRead(btn_sec) == LOW && semaphore_state == -1)  {
    switch_semaphore_state();
    delay(100);
    Serial.print("sem1");
  } else { 
    if(digitalRead(btn_princ) == LOW && semaphore_state == 1)  {
      switch_semaphore_state();
      delay(100);
      Serial.print("sem2");
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  handle_buttons();
  //handle_leds();

}
