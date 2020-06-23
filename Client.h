#ifndef TALLER_CLIENT_H
#define TALLER_CLIENT_H

#include "CommunicateData.h"
#include "GameRunner.h"
#include <queue>
#include <thread>

using namespace std;

class Client {

    queue<SDL_Event> q;

    GameRunner* game;

    int client_socket;

    struct sockaddr_in server;

    bool isConnected;

    char buffer_enviado[1024];

    char buffer_receptor[1024];

public:

    void closeClient();

    int connectToServer(char *ip, char *port);

    int receiveData();

    int sendData();

    void chatToServer();

    void sendDataToServer();

    void endGame();

};


#endif //TALLER_CLIENT_H
