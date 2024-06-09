#include "PwmGenerator.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include "Servo.hpp"


PwmGenerator::PwmGenerator() {
    write_to_file(SERVO_PWM_GPIO_EXPORT_PATH, "12");
}


PwmGenerator::~PwmGenerator() {
    write_to_file(SERVO_PWM_GPIO_UNEXPORT_PATH, "12");
}


void PwmGenerator::set_pwm_duty_cycle(int duty_cycle_percent, int period_us) {
    int on_time = duty_cycle_percent/100 * period_us;
    int off_time = period_us - on_time;

    auto start_time = std::chrono::system_clock::now();
    while (true) {
        auto current_time = std::chrono::system_clock::now();
        if (current_time - start_time > std::chrono::microseconds(1000)) break;
        write_to_file(SERVO_PWM_GPIO_VALUE_PATH, "high");
        usleep(on_time);
        write_to_file(SERVO_PWM_GPIO_VALUE_PATH, "low");
        usleep(off_time);
    }    
}


void PwmGenerator::write_to_file(std::string path, std::string text) {
    std::ofstream file(path);
    file << text << std::endl;
    file.close();
}