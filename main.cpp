#include "server.h"

#include <iostream>
#include <sys/socket.h> // сокеты
#include <netinet/in.h> // константы для работы с портами и ip и структура
#include <arpa/inet.h> // ip address, его нужно чтобы передать в строке ip
#include <unistd.h> // закрыть порты

using namespace std;

int main(){

    Server* server = new Server();

    Server::Command command;

    if(server->start_server() < 0){
        delete server;
        return -1;
    }

    if(server->listen_server() < 0){
        delete server;
        return -1;
    }
    if(server->accept_client_to_server()< 0){
        delete server;
        return -1;
    }

    while(true){

        if(server->recv_server(command) < 0) {
            delete server;
            return -1;
        }
        if(command.command_type == 1) {
            if(server->send_time_client()){
                delete server;
                return -1;
            }
        }
        if(command.command_type == 2){
            break;
        }
    }


    server->close_client();
    server->close_server();

    delete server;

    return 0;
}

// int main()
// {
//     int socket_server = socket(AF_INET, SOCK_STREAM, 0);

//     if(socket_server < 0){
//         std::cerr << "не удалось создать сокет" << std::endl;
//         return -1;
//     }

//     struct sockaddr_in server_addr{};
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = 8080;
//     server_addr.sin_addr.s_addr = inet_addr("192.168.31.142");

//     if(bind(socket_server,(struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
//         std::cerr << "Не получилось свзязать ip или порт с socket" << std::endl;
//         return -1;
//     }

//     if(listen(socket_server,SOMAXCONN) < 0){
//         std::cerr << "Ошибка прослушивания входящего соединения" << std::endl;
//         return -1;
//     }

//     sockaddr_in client_address{};
//     socklen_t client_address_len = sizeof(client_address);
//     int socket_client = accept(socket_server, (struct sockaddr *)&client_address, &client_address_len);

//     if(socket_client < 0){
//         std::cerr << "Ошибка при принятии входящего соединения" << std::endl;
//         exit(1);
//     }

//     struct Command{
//         int command_type;
//     }command;

//     if(recv(socket_client,&command, sizeof(command), 0)< 0){
//         std::cerr << "Ошибка при попытке принять команду" << std::endl;
//         return -1;
//     }

//     shutdown(socket_server, 2);
//     shutdown(socket_client, 2);
//     if(socket_client != -1){
//         close(socket_client);
//         socket_client = -1;
//     }

//     if(socket_server != -1){
//         close(socket_server);
//         socket_server = -1;
//     }

//     return 0;
// }
