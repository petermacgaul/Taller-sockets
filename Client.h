//
// Created by peter on 28/5/20.
//

#ifndef TALLER_CLIENT_H
#define TALLER_CLIENT_H
#include <SDL2/SDL.h>
#include "struct.h"

class Client {
    int client_socket;

    char *ip_conect;
    char* puerto;

    struct sockaddr_in server;

    struct Command client_command;

    struct View client_view;

    bool isConnected;

public:

    void closeClient();

    void connectToServer(char *ip_conect, char* puerto);

    int receiveData(int* client_socket, struct View* client_view);

    int sendData(int* client_socket, struct Command* client_command);

    void setPort(char *string);

    void setIP(char *string);
};


#endif //TALLER_CLIENT_H
