#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Server
{
    int PORT_SERVER = 8080;
    const char* IP_SERVER = "192.168.31.142";

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int socket_server;
    int socket_client;

public:
    struct Command{
        int command_type = 0;
    };

public:
    Server();
    ~Server();
    int start_server();
    int listen_server();
    int accept_client_to_server();
    int recv_server(struct Command& command);
    int send_server(struct Command& command);
    void close_client();
    void close_server();
};

#endif // SERVER_H
