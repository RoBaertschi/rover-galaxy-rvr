#ifndef INCLUDE_MOTORS_H
#define INCLUDE_MOTORS_H

#define MOTOR_PINS (uint8_t[4]){2, 3, 4, 5}
#define MOTOR_DIRECTIONS (uint8_t[2]){0, 1}

#define MOTOR_POWER_MIN 28  // 28/255

void beginMotors();

void motorsForward(int8_t power);
void motorsBackward(int8_t power);
void motorsTurnLeft(int8_t power);
void motorsTurnRight(int8_t power);
void motorsStop();
void motorsSetMotors(int8_t power, int8_t power2);
void motorsDo360(int8_t direction, int8_t power);

#endif