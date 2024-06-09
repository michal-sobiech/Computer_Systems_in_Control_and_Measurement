#include "VL53L0_1XV2.hpp"
#include <stdio.h>
#include <string>
#include <linux/i2c-dev.h>
// #include "vl53l0x_api.h"
// #include "vl53l0x_platform.h"
#include "peripheral_mapping.hpp"


#define VL53L0_1XV2_I2C_ADDR 0x29


void VL53L0_1XV2::print_pal_error(VL53L0X_Error status){
    char buf[VL53L0X_MAX_STRING_LENGTH];
    VL53L0X_GetPalErrorString(status, buf);
    printf("API Status: %i : %s\n", status, buf);
}


bool VL53L0_1XV2::is_data_valid(VL53L0X_RangingMeasurementData_t &measurement_data) {
    uint8_t range_status = measurement_data.RangeStatus;
    return range_status == 0;
}


uint16_t VL53L0_1XV2::get_distance(VL53L0X_RangingMeasurementData_t &measurement_data) {
    return measurement_data.RangeMilliMeter;
}


VL53L0X_Error VL53L0_1XV2::init() {
    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    device.I2cDevAddr = VL53L0_1XV2_I2C_ADDR;

    std::string dev_path = VL53L0_1XV2_I2C_PATH;
    // char dev_path_char_arr[dev_path.length() + 1];
    // std::copy(dev_path.begin(), dev_path.end(), dev_path_char_arr);
    // dev_path_char_arr[sizeof(dev_path_char_arr)];
    // printf("Device file path: %s\n", dev_path.c_str();
    // char* dev_path_char_arr = dev_path.c_str();

    device.fd = VL53L0X_i2c_init(const_cast<char*>(dev_path.c_str()), device.I2cDevAddr);

    if (device.fd < 0) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
        printf("Failed to init\n");
    }

    if (status == VL53L0X_ERROR_NONE)
    {
        printf("Call of VL53L0X_DataInit\n");
        status = VL53L0X_DataInit(&device);
        print_pal_error(status);
    }

    if (status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_StaticInit\n");
        status = VL53L0X_StaticInit(&device);
        print_pal_error(status);
    }
    
    uint32_t ref_spad_count;
    uint8_t is_aperture_spads;
    uint8_t vhv_settings;
    uint8_t phase_cal;

    if (status == VL53L0X_ERROR_NONE)
    {
        printf("Call of VL53L0X_PerformRefCalibration\n");
        status = VL53L0X_PerformRefCalibration(&device,
        		&vhv_settings, &phase_cal);
        print_pal_error(status);
    }

    if (status == VL53L0X_ERROR_NONE)
    {
        printf("Call of VL53L0X_PerformRefSpadManagement\n");
        status = VL53L0X_PerformRefSpadManagement(&device,
        		&ref_spad_count, &is_aperture_spads);
        printf("ref_spad_count = %d, is_aperture_spads = %d\n", ref_spad_count, is_aperture_spads);
        print_pal_error(status);
    }

    if (status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_SetDeviceMode\n");
        status = VL53L0X_SetDeviceMode(&device, VL53L0X_DEVICEMODE_SINGLE_RANGING);
        print_pal_error(status);
    }
	
    if (status == VL53L0X_ERROR_NONE) {
        status = VL53L0X_SetLimitCheckEnable(&device,
        		VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }
    if (status == VL53L0X_ERROR_NONE) {
        status = VL53L0X_SetLimitCheckEnable(&device,
        		VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }
				
    if (status == VL53L0X_ERROR_NONE) {
        status = VL53L0X_SetLimitCheckValue(&device,
        		VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
        		(FixPoint1616_t)(0.1*65536));
	}

    if (status == VL53L0X_ERROR_NONE) {
        status = VL53L0X_SetLimitCheckValue(&device,
        		VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
        		(FixPoint1616_t)(60*65536));			
    }

    if (status == VL53L0X_ERROR_NONE) {
        status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(&device,
        		33000);
	}
	
    if (status == VL53L0X_ERROR_NONE) {
        status = VL53L0X_SetVcselPulsePeriod(&device, 
		        VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
    }

    if (status == VL53L0X_ERROR_NONE) {
        status = VL53L0X_SetVcselPulsePeriod(&device, 
		        VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
    }

    return status;
}


VL53L0X_Error VL53L0_1XV2::perform_a_measurement(
        VL53L0X_RangingMeasurementData_t &measurement_data) {
    VL53L0X_Error status;

    printf("Call of VL53L0X_PerformSingleRangingMeasurement\n");
    status = VL53L0X_PerformSingleRangingMeasurement(&device, &measurement_data);
    print_pal_error(status);

    return status;
}


uint16_t VL53L0_1XV2::measure_distance() {
    VL53L0X_RangingMeasurementData_t measurement_data;

    VL53L0X_Error status = perform_a_measurement(measurement_data);
    if (status == VL53L0X_ERROR_NONE) {
        return get_distance(measurement_data);
    }
    return -1;
}


void VL53L0_1XV2::close() {
    printf("Closing VL53L0.\n");
    VL53L0X_i2c_close();
}