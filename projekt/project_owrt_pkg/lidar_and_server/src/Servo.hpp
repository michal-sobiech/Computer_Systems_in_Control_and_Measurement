#ifndef SERVO_HPP
#define SERVO_HPP

#include "peripheral_mapping.hpp"

// standard servo freq. is 50Hz, so the period is 0.02s = 20ms = 20 000 us
#define SERVO_PERIOD 20000
// min duty cycle is usually about 1 ms = 1 000 us
#define SERVO_MIN_DUTY_CYCLE 1000
// max duty cycle is usually about 2 ms = 2 000 us
#define SERVO_MAX_DUTY_CYCLE 2000
#define SERVO_MAX_ANGLE 360


class Servo {
public:
    Servo() = default;
    void rotate(int destination_angle);
};

#endif