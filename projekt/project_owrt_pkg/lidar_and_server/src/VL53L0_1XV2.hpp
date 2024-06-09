#ifndef VL53L0_1XV2_HPP
#define VL53L0_1XV2_HPP

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"


class VL53L0_1XV2 {
public:
    VL53L0_1XV2() = default;
    VL53L0X_Error init();
    uint16_t measure_distance();
    void close();
private:
    VL53L0X_Dev_t device;

    void print_pal_error(VL53L0X_Error status);
    bool is_data_valid(VL53L0X_RangingMeasurementData_t &measurement_data);
    uint16_t get_distance(VL53L0X_RangingMeasurementData_t &measurement_data);
    VL53L0X_Error perform_a_measurement(VL53L0X_RangingMeasurementData_t &measurement_data);
};

#endif