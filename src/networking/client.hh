#ifndef NETWORK_CLIENT_C
#define NETWORK_CLIENT_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Client
{
    private:
        char *server_address;
        int server_port;
        int socket_file_descriptor;
    public:
        Client(char *address, int port);
        int open();
        int receiveMessage(char *buffer, int size);
        int sendMessage(char *message, int size);
};

#endif // NETWORK_CLIENT_H
