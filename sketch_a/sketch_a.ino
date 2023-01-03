#include <Arduino.h>
#include <neotimer.h>

#define RUNNING_GREEN_LED 2
#define RECOVERY_BLUE_LED 3
#define IDLE_RED_LED 4

#define START_STOP_BTN 5

#define NO_RELAY 7
#define NC_RELAY 8

#define TIMES 3
//  8 m = 1000*60*8 = 480000 ms
//  6 m = 1000*60*6 = 360000 ms
// 30 s = 1000*30 = 30000 ms
#define RUN_TIME 480000
// 16 m = 1000*60*16 = 960000 ms
// 40 s = 1000*40 = 40000 ms
#define RECOVERY_TIME 960000

// Magnetic contactor reaction time
#define MC_REACTION_TIME 500

uint8_t remaningCount;
Neotimer runTimer = Neotimer(RUN_TIME);
Neotimer recoveryTimer = Neotimer(RECOVERY_TIME);

void closeOpenRelay(uint8_t pin) {
  digitalWrite(pin, HIGH); // close the relay
  delay(MC_REACTION_TIME); // wait some time (close to magnetic reaction time)
  digitalWrite(pin, LOW);  // open the relay
}

void onPump() {
  // simulate a push on the start button (normally open) of the magnetic contactor
  closeOpenRelay(NO_RELAY);
  // start the run timer
  runTimer.start();
}

void offPump() {
  // simulate a push on the stop button (normally closed) of the magnetic contactor
  closeOpenRelay(NC_RELAY);
  // start the recovery timer
  recoveryTimer.start();
}

void onRunningStart() {
  digitalWrite(IDLE_RED_LED, LOW);
  digitalWrite(RUNNING_GREEN_LED, HIGH);
  onPump();
}

void onRunningEnd() {
  digitalWrite(RECOVERY_BLUE_LED, LOW);
  digitalWrite(RUNNING_GREEN_LED, LOW);
  digitalWrite(IDLE_RED_LED, HIGH);
  recoveryTimer.reset();
}

void onRecoveryStart() {
  digitalWrite(RECOVERY_BLUE_LED, HIGH);
  if (remaningCount == 1) {
    digitalWrite(RUNNING_GREEN_LED, LOW);
    digitalWrite(IDLE_RED_LED, HIGH);
  }
  runTimer.reset();
  remaningCount--;
  offPump();
}

void onRecoveryEnd() {
  digitalWrite(RECOVERY_BLUE_LED, LOW);
  recoveryTimer.reset();
  onPump();
}

void onRunningStop() {
  digitalWrite(RUNNING_GREEN_LED, LOW);
  digitalWrite(IDLE_RED_LED, HIGH);
  runTimer.reset();
  offPump();
}

void setup() {
  // configure the pins of the LEDs
  pinMode(RUNNING_GREEN_LED, OUTPUT);
  pinMode(RECOVERY_BLUE_LED, OUTPUT);
  pinMode(IDLE_RED_LED, OUTPUT);
  // configure touch sensor pin
  pinMode(START_STOP_BTN, INPUT);
  // configure the pins of the relays
  pinMode(NO_RELAY, OUTPUT);
  pinMode(NC_RELAY, OUTPUT);
  // turn on red led
  digitalWrite(IDLE_RED_LED, HIGH);
}

void loop() {
  if (digitalRead(START_STOP_BTN) == HIGH) {
    if (runTimer.waiting()) {
      onRunningStop();
    } else if (recoveryTimer.waiting()){
      onRunningEnd();
    } else {
      remaningCount = TIMES;
      onRunningStart();
    }
  }

  if (runTimer.done()) {
     onRecoveryStart();
  }

  if (recoveryTimer.done()) {
    if (remaningCount > 0) {
      onRecoveryEnd();
    } else {
      onRunningEnd();
    }
  }
}
