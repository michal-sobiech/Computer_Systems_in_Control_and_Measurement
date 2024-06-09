#pragma once
#include <arpa/inet.h>
#include "datagram.hpp"


class Server {
public:
    // Sets up the socket
    Server(int port);
    // Sets up the communication with the sender (saves their address in the object's field)
    void wait_for_connection();
    // Sends a message to the saved client address (client_address)
    void send_a_message(data_t &message);
private:
    int sockfd;
    sockaddr_in client_address;

    int create_a_socket(int port);
    void receive_a_message(data_t &message, sockaddr_in &sender_address);
};