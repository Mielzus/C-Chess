#include "server.hh"

Server::Server(int port)
{
    this->server_port = port;
}

int Server::open()
{
    sockaddr_in server_address;
    int status;
    int address_length = sizeof(server_address);

    // Create socket
    // AF_INET - specifies which IP range to use
    // SOCK_STREAM - specifies connection type
    this->socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket_file_descriptor == -1) {
        perror("error setting up socket");
        exit(EXIT_FAILURE);
    }

    // Tell the server to listen on all available interfaces
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind socket to address
    status = bind(this->socket_file_descriptor, (sockaddr*) &server_address, sizeof(server_address));
    if (status == -1) {
        perror("error binding socket to address");
        exit(EXIT_FAILURE);
    }

    // Listen
    status = listen(this->socket_file_descriptor, 3);
    if (status == -1) {
        perror("error listening");
        exit(EXIT_FAILURE);
    }

    // Accept a socket
    this->socket_file_descriptor = accept(this->socket_file_descriptor, (sockaddr*) &server_address, (socklen_t*) &address_length);
    if (this->socket_file_descriptor == -1) {
        perror("error accepting socket");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int Server::receiveMessage(char *buffer, int size)
{
    int status = read(this->socket_file_descriptor, buffer, size);
    if (status == -1) {
        perror("error receiving message");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Server::sendMessage(char *message, int size)
{
    int sent = send(this->socket_file_descriptor, message, size, 0);
    if (sent < 0) {
        perror("error sending message");
        exit(EXIT_FAILURE);
    }
    return sent;
}
