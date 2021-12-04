#include <Arduino.h>
#include <neotimer.h>

#define RUNNING_GREEN_LED 2
#define RECOVERY_BLUE_LED 3
#define IDLE_RED_LED 4

#define START_STOP_BTN 5

#define NO_RELAY 7
#define NC_RELAY 8

#define TIMES 3
// 8 minutes
#define RUN_TIME 480000
// 16 minutes
#define RECOVERY_TIME 960000

boolean idle;
uint8_t runCount, runTotal;
Neotimer runTimer = Neotimer(RUN_TIME);
Neotimer recoveryTimer = Neotimer(RECOVERY_TIME);

void closeOpenRelay(uint8_t pin) {
    digitalWrite(pin, HIGH); // close the relay
    delay(500);              // wait some time (close to magnetic reaction time)
    digitalWrite(pin, LOW);  // open the relay
}

void startMotor() {
    // turn on the green LED and turn off the other LEDs
    digitalWrite(RECOVERY_BLUE_LED, LOW);
    digitalWrite(IDLE_RED_LED, LOW);
    digitalWrite(RUNNING_GREEN_LED, HIGH);
    // simulate a push on the start button (normally open) of the magnetic contactor
    closeOpenRelay(NO_RELAY);
    // start the run timer
    runTimer.start();
}

void stopMotor() {
    // simulate a push on the stop button (normally closed) of the magnetic contactor
    closeOpenRelay(NC_RELAY);
    // turn on the blue LED and turn off the green LED
    digitalWrite(RUNNING_GREEN_LED, LOW);
    digitalWrite(RECOVERY_BLUE_LED, HIGH);
    // start the recovery timer
    recoveryTimer.start();
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
    idle = true;
    // turn on red led
    digitalWrite(IDLE_RED_LED, HIGH);
}

void loop() {
    if (digitalRead(START_STOP_BTN) == HIGH) {
        if (idle) { // on idle
            runCount = 0;
            runTotal = TIMES;
            idle = false;
            startMotor();
        } else {   // on running or on recovering
            runTotal = runCount;
            if (runTimer.waiting()) { // on running
                runTimer.reset(); // reset method make a call to stop method during its execution
                stopMotor();
            }
        }
    }

    if (runTimer.done()) {
        runTimer.reset();
        runCount++;
        stopMotor();
    }

    if (recoveryTimer.done()) {
        recoveryTimer.reset();
        if (runCount < runTotal) {  // start again if the repetitive process is not finished
            startMotor();
        } else {                    // go idle if the repetitive process finished
            idle = true;
            digitalWrite(RECOVERY_BLUE_LED, LOW);
            digitalWrite(IDLE_RED_LED, HIGH);
        }
    }
}
