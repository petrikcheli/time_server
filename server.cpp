#include "server.h"
#include <iostream>

Server::Server() {}
Server::~Server(){
    close_all();
}

int Server::start_server(){

    socket_server = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_server < 0){
        std::cerr << "Ошибка инциализации сокета" << std::endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT_SERVER;
    server_addr.sin_addr.s_addr = inet_addr(IP_SERVER);

    if(bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        std::cerr << "не удалось связать порт и ip с soket" << std::endl;
        return -1;
    }
    return 0;
}

int Server::listen_server(){

    if(listen(socket_server, SOMAXCONN) < 0){
        std::cerr << "Ошибка при прослушивании порта" << std::endl;
        return -1;
    }

    return 0;
}


int Server::accept_client_to_server(){

    socklen_t len_socket_client = sizeof(client_addr);

    socket_client = accept(socket_server, (struct sockaddr *)&client_addr, &len_socket_client);

    if(socket_client < 0){
        std::cerr << "Ошибка при принятии входящего соединения" << std::endl;
        return -1;
    }
    return 0;
}

int Server::send_server(struct Command & command){

    //тут нужно придумать то, что будет возвразать сервер

    if(send(socket_client, &command, sizeof(command), 0) < 0){
        std::cerr << "Не удалось отправить сообщение клиенту" << std::endl;
        return -1;
    }

    return 0;
}

int Server::recv_server(struct Command & command){

    if(recv(socket_client, &command, sizeof(command), 0) < 0){
        std::cerr << "Не удалось принять сообщение от клиента" << std::endl;
        return -1;
    }

    return 0;
}

void Server::close_client(){
    shutdown(socket_client, 2);

    if(socket_client != -1){
        close(socket_client);
        socket_client = -1;
    }
}

void Server::close_server(){
    shutdown(socket_server, 2);

    if(socket_server != -1){
        close(socket_server);
        socket_server = -1;
    }
}

void Server::close_all(){
    Server::close_client();
    Server::close_server();
}

int Server::send_time_client(){

    struct Time_server time_s;
    time_s.seconds = time(NULL);

    if(send(socket_client, &time_s, sizeof(time_s), 0) < 0){
        std::cerr << "Не удалось отправить время клиенту" << std::endl;
        return -1;
    }

    return 0;
}
