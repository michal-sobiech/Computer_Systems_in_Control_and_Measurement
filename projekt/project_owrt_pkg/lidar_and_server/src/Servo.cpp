#include "Servo.hpp"
#include "peripheral_mapping.hpp"
#include "PwmGenerator.hpp"


void Servo::rotate(int destination_angle) {
    PwmGenerator pwmGenerator = PwmGenerator();

    int max_min_duty_cycle_diff = SERVO_MAX_DUTY_CYCLE - SERVO_MIN_DUTY_CYCLE;
    int offset = max_min_duty_cycle_diff * destination_angle / SERVO_MAX_ANGLE;
    int duty_cycle = SERVO_MIN_DUTY_CYCLE + offset;

    pwmGenerator.set_pwm_duty_cycle(duty_cycle, SERVO_PERIOD);
}