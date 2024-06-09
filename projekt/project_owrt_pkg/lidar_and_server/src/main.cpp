#include <unistd.h>
#include <string>

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include "Servo.hpp"
#include "VL53L0_1XV2.hpp"
#include "Server.hpp"


#define SERVO_ROTATION_DEGREES 5
#define SERVO_ROTATION_TIME_MS 500
#define SERVO_SETUP_TIME_MS 2000


VL53L0_1XV2 *tof_sensor = nullptr;


void cleanup() {
    if (tof_sensor) {
        tof_sensor->close();
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Invalid number of arguments");
        exit(1);
    }
    int port = atoi(argv[1]);

    atexit(cleanup);

    // Setup the servo, ToF sensor and the server

    int servo_angle = 0;
    Servo servo = Servo();
    servo.rotate(0);
    usleep(SERVO_SETUP_TIME_MS * 1000);

    // Dynamic due to the need of invoking close() at SIGINT
    tof_sensor = new VL53L0_1XV2;
    VL53L0X_Error tof_sensor_status = tof_sensor->init();
    if (tof_sensor_status != VL53L0X_ERROR_NONE) {
        printf("Error: VL53L0_1XV2 init failed.\n");
        exit(1);
    }

    Server server = Server(port);

    // Wait for the client to connect to us

    server.wait_for_connection();

    // Start measuring the distance

    while (servo_angle < SERVO_MAX_ANGLE) {
        // Rotate the servo
        servo.rotate(servo_angle);
        usleep(SERVO_ROTATION_TIME_MS * 1000);

        // Measure the distance
        uint16_t distance = tof_sensor->measure_distance();
        printf("Measured distance: %i\n\n", distance);

        // Send the data to the client
        data_t data = {
            (uint16_t) servo_angle,
            distance
        };
        server.send_a_message(data);

        servo_angle += SERVO_ROTATION_DEGREES;
    }

    // Send the end message
    data_t data = {
        htons((uint16_t)0xffff),
        htons((uint16_t)0xffff),
    };
    server.send_a_message(data);

    return 0;
}