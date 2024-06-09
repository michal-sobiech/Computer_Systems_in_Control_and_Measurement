import socket
import struct
import argparse
import matplotlib.pyplot as plt
import matplotlib

import radarplotter

def parse_command_line():
    parser = argparse.ArgumentParser(description="UDP Client")
    parser.add_argument("--udp_ip", type=str, default="127.0.0.1", help="IP of UDP server")
    parser.add_argument("--udp_port", type=int, default=12345, help="Port of UDP server")
    return parser.parse_args()


class Client:
    udp_ip: str
    udp_port: int
    buffersize: int
    should_continue_running: bool
    plotter: radarplotter.RadarPlotter

    def __init__(self, *, udp_ip, udp_port, number_of_drawn_points) -> None:
        self.udp_ip = udp_ip
        self.udp_port = udp_port
        self.plotter = radarplotter.RadarPlotter(number_of_drawn_points=number_of_drawn_points, path_to_radar_image="radar.png")
        self.buffersize = 1024
    
    def start(self) -> None:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            self.plotter.plot()
            sock.bind(("0.0.0.0", 22222))
            self.send_starting_message(sock)
            try:
                self.should_continue_running = True
                while self.should_continue_running:
                    unpacked_data = self.receive_data(sock)
                    if unpacked_data == (0xffff, 0xffff):
                        # End message
                        print(f"Received the termination message")
                        self.should_continue_running = False
                    else:
                        angle, distance = unpacked_data
                        print(f"Received from {self.senders_address}: angle = {angle}, distance = {distance}")
                        self.plotter.add_point(angle, distance)
                        self.plotter.plot()
            except KeyboardInterrupt:
                print("User interrupt")

    def send_starting_message(self, bound_socket) -> None:
        # We start with START OF TEXT character
        start_message =  "\x02"
        bound_socket.sendto(start_message.encode(), (self.udp_ip, self.udp_port))

    def receive_data(self, bound_socket) -> None:
        received_data, self.senders_address = bound_socket.recvfrom(self.buffersize)
        unpacked_data = struct.unpack('!HH', received_data)
        return unpacked_data

    def stop(self) -> None:
        self.should_continue_running = False

    


if __name__ == "__main__":
    arguments = parse_command_line()
    number_of_drawn_points = 100
    client = Client(
        udp_ip=arguments.udp_ip,
        udp_port=arguments.udp_port,
        number_of_drawn_points=number_of_drawn_points
    )
    client.start()
    plt.ioff()
    plt.show()
