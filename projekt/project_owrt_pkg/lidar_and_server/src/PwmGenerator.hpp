#ifndef PwmGenerator_HPP
#define PwmGenerator_HPP

#include <string>


class PwmGenerator {
public:
    PwmGenerator();
    ~PwmGenerator();
    void set_pwm_duty_cycle(int duty_cycle_percent, int period_us);
private:
    void write_to_file(std::string path, std::string text);
};

#endif