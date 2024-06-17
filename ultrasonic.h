#ifndef INCLUDE_ULTRASONIC_H
#define INCLUDE_ULTRASONIC_H

#define ULTRASONIC_PIN_TRIG 10
#define ULTRASONIC_PIN_ECHO 10

#define ULTRASONIC_READ_TIMEOUT 18000 // us , 2*300/34000*1000000 ~= 17647 us

#define MAX_DISTANCE 300

void beginUS(void);

byte usGetRead();

bool usObstacleNear();

bool usClear();

#endif