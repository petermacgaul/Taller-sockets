#ifndef TALLER_CLIENT_H
#define TALLER_CLIENT_H

#include "CommunicateData.h"
#include <thread>
using namespace std;

class Client {
    int client_socket;

    struct sockaddr_in server;

    struct Command command;

    struct View view;

    bool isConnected;

public:

    void closeClient();

    void connectToServer(char *ip, char *port);

    int receiveData(int* client_socket, struct View* client_view);

    int sendData(int* client_socket, struct Command* client_command);

    void chatToServer();

    void recibeDataFromServer();

};


#endif //TALLER_CLIENT_H
