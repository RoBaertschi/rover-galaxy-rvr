#include "Arduino.h"
#include "ultrasonic.h"

void beginUS(void) {

}


byte usGetRead() {
  delay(4);

  pinMode(ULTRASONIC_PIN_TRIG, OUTPUT);
  digitalWrite(ULTRASONIC_PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_PIN_TRIG, LOW);
  pinMode(ULTRASONIC_PIN_ECHO, INPUT);

  float duration = pulseIn(ULTRASONIC_PIN_ECHO, HIGH, ULTRASONIC_READ_TIMEOUT);

  float distance = duration * 0.017;

  if (distance > MAX_DISTANCE || distance == 0) {
    return -1;
  }
  return distance;
}

#define THRESHOLD 300

bool usObstacleNear() {
  // Avoidance Threshold
  return usGetRead() < THRESHOLD;
}

bool usClear() {
  float distance = usGetRead();
  return distance > THRESHOLD || distance < 0;
}