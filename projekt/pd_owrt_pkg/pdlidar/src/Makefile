all: fake_lidar

clean:
	rm -f fake_lidar

fake_lidar: main.cpp Server.cpp 
	$(CXX) \
	-I . \
	$(CXXFLAGS) \
	-o fake_lidar main.cpp Server.cpp
	
