//
// Created by peter on 28/5/20.
//

#ifndef TALLER_SERVER_H
#define TALLER_SERVER_H
#include <SDL2/SDL.h>
#include <netinet/in.h>
#include "struct.h"


typedef struct Cliente {
    bool isConnected;
    int clientSocket;
    int clientAddrlen;
} client_info;

class Server {

    void initializeData(struct View* client_view);

    int serverSocket;
    client_info client;

    struct sockaddr_in client_addr;
    struct Command client_command;
    struct View client_view;

public:
    void acceptClient();

    void initServer(char *argv);

    void closeServer();

    bool playersAreConnected();

    int receiveData(struct Command* client_command);

    void processData(SDL_Event event, struct View* view);

    int sendData(struct View* client_view);

    void start();
};


#endif //TALLER_SERVER_H
