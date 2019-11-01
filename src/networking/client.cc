#include "client.hh"

Client::Client(char *address, int port)
{
    this->server_address = address;
    this->server_port = port;
}

int Client::open()
{
    sockaddr_in server_address;
    int status;

    // Create socket
    // AF_INET - specifies which IP range to use
    // SOCK_STREAM - specifies connection type
    this->socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket_file_descriptor == -1) {
        perror("error setting up socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(this->server_port);

    // Convert IPv4 and IPv6 addresses from text to binary form 
    status = inet_pton(AF_INET, this->server_address, &server_address.sin_addr);
	if(status == -1) 
	{ 
		perror("error translating address");
        exit(EXIT_FAILURE);
	} 

    status = connect(this->socket_file_descriptor, (sockaddr*) &server_address, sizeof(server_address));
    if (status == -1) {
        perror("error connecting to server");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int Client::receiveMessage(char *buffer, int size)
{
    int status = read(this->socket_file_descriptor, buffer, size);
    if (status == -1) {
        perror("error receiving message");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Client::sendMessage(char *message, int size)
{
    int sent = send(this->socket_file_descriptor, message, size, 0);
    if (sent < 0) {
        perror("error sending message");
        exit(EXIT_FAILURE);
    }
    return 0;
}
