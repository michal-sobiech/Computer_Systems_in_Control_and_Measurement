#include "Server.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "datagram.hpp"


Server::Server(int port) {
    sockfd = create_a_socket(port);
}


void Server::wait_for_connection() {
    data_t placeholder_message; // the contents will not matter.
    receive_a_message(placeholder_message, client_address);
}


int Server::create_a_socket(int port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd  < 0) {
        perror("Failed to create a socket");
        exit(1);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) == -1) {
        perror("Failed to bind a socket");
        exit(1);
    }

    return sockfd;
}


void Server::receive_a_message(data_t &message, sockaddr_in &sender_address) {
    socklen_t sender_address_size = (socklen_t) sizeof(sender_address);
    int data_length = recvfrom(
        sockfd,
        &message, 
        sizeof(message),
        0,
        (struct sockaddr *) &sender_address,
        &sender_address_size
    );
    if (data_length == -1) {
        perror("Failed to receive the message");
        exit(1);
    }
}


void Server::send_a_message(data_t &message) {
    int data_length = sendto(
        sockfd,
        &message,
        sizeof(message),
        0,
        (struct sockaddr *) &client_address,
        (socklen_t){sizeof(client_address)}
    );
    if (data_length == -1) {
        perror("Failed to send the message");
        exit(1);
    }
}