#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

class Server {
    private:
        int server_port;
        int socket_file_descriptor;
    public:
        Server(int port);
        int open();
        int receiveMessage(char *buffer, int size);
        int sendMessage(char *message, int size);
};

#endif // NETWORK_SERVER_H
