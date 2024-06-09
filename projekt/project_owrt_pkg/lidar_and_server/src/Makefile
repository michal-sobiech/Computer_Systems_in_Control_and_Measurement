all: lidar_and_server


clean:
	rm -f lidar_and_server


VL53L0X_API:
	API_DIR=../stm_api $(MAKE) -C api/VL53L0X_rasp clean all


lidar_and_server: main.cpp Servo.cpp Server.cpp PwmGenerator.cpp VL53L0_1XV2.cpp VL53L0X_API
	$(CXX) \
	-I api/stm_api/Api/core/inc \
	-I api/VL53L0X_rasp/platform/inc \
	-I . \
	$(CXXFLAGS) \
	-o lidar_and_server main.cpp Servo.cpp Server.cpp PwmGenerator.cpp VL53L0_1XV2.cpp \
	-Lapi/VL53L0X_rasp/bin -lVL53L0X_Rasp


# lidar_and_server: main.cpp Servo.cpp Server.cpp PwmGenerator.cpp VL53L0X_API
# 	$(CXX) \
# 	-I api/stm_api/Api/core/inc \
# 	-I api/VL53L0X_rasp/platform/inc \
# 	-I . \
# 	$(CXXFLAGS) \
# 	-o lidar_and_server main.cpp Servo.cpp Server.cpp PwmGenerator.cpp