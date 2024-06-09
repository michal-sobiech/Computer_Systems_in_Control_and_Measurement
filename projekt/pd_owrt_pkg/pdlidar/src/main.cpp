#include <cstdlib>
#include <csignal>
#include <string>
#include <random>  
#include <thread>
#include <algorithm>
#include "Server.hpp"

#define SERVO_ROTATION_DEGREES 5
#define SERVO_ROTATION_TIME_MS 500
#define SERVO_SETUP_TIME_MS 2000
#define SERVO_MAX_ANGLE 360  // Assuming SERVO_MAX_ANGLE is defined somewhere

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);  // Change the range as needed
    return dis(gen);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Invalid number of arguments\n");
        exit(1);
    }
    int port = atoi(argv[1]);

    int servo_angle = 0;
    Server server = Server(port);

    // Wait for the client to connect to us
    server.wait_for_connection();

    printf("Client connected!\n");

    uint16_t distance = generateRandomNumber(1000, 1500);
    while (servo_angle < SERVO_MAX_ANGLE) {
        std::this_thread::sleep_for(std::chrono::milliseconds(SERVO_ROTATION_TIME_MS));

        distance += generateRandomNumber(-100, 100);
        distance = std::max((uint16_t)0, distance);
        distance = std::min((uint16_t)2000, distance);

        // Generate random distance
        printf("Angle: %i, distance: %i\n\n", servo_angle, distance);

        // Send the data to the client
        data_t data = {
            htons((uint16_t)servo_angle),
            htons((uint16_t)distance),
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
