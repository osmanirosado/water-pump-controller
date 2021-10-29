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

void blinkRelay(uint8_t pin) {
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
}

void startMotor() {
    runTimer.reset();
    runTimer.start();
    digitalWrite(RECOVERY_BLUE_LED, LOW);
    digitalWrite(IDLE_RED_LED, LOW);
    digitalWrite(RUNNING_GREEN_LED, HIGH);
    blinkRelay(NO_RELAY);
}

void stopMotor() {
    blinkRelay(NC_RELAY);
    digitalWrite(RUNNING_GREEN_LED, LOW);
    recoveryTimer.reset();
    recoveryTimer.start();
    digitalWrite(RECOVERY_BLUE_LED, HIGH);
}

void setup() {
    pinMode(RUNNING_GREEN_LED, OUTPUT);
    pinMode(RECOVERY_BLUE_LED, OUTPUT);
    pinMode(IDLE_RED_LED, OUTPUT);
    pinMode(START_STOP_BTN, INPUT);
    pinMode(NO_RELAY, OUTPUT);
    pinMode(NC_RELAY, OUTPUT);
    idle = true;
    digitalWrite(IDLE_RED_LED, HIGH);
}

void loop() {
    if (digitalRead(START_STOP_BTN) == HIGH) {
        if (idle) {
            runCount = 0;
            runTotal = TIMES;
            idle = false;
            startMotor();
        } else {
            runTotal = runCount;
            if (runTimer.waiting()) {
                runTimer.stop();
                stopMotor();
            }
        }
    }

    if (runTimer.done()) {
        runCount++;
        stopMotor();
    }

    if (recoveryTimer.done()) {
        digitalWrite(RECOVERY_BLUE_LED, LOW);
        if (runCount < runTotal) {
            startMotor();
        } else {
            idle = true;
            digitalWrite(IDLE_RED_LED, HIGH);
        }
    }
}
