#ifndef TALLER_SERVER_H
#define TALLER_SERVER_H

#include <netinet/in.h>
#include <vector>
#include <thread>

#include "QueueMultithread.h"
#include "CommunicateData.h"
#include <map>

using namespace std;

struct QueueCommand{
    int client_socket;
    int process_event;
    char* buffer_command;
};

typedef struct Cliente {
    bool isConnected;
    int clientSocket;
    int clientAddrlen;
} client_info;

class Server {
    int serverSocket;
    bool serverOnline;

    map<int,client_info> clients;
    int expectedClients;
    char buffer[1024];

    QueueMultithread<QueueCommand> eventQueue;

    void initializeData();

    char * processData(char* comando);

    int sendData(client_info *client);

    void popCommand();

    int acceptClient();

    void chatWhitClients(int client_socket);

    int receiveData(client_info *client);

    int howManyPlayersAreConnected();

    void closeServer();

public:

    int initServer(char *argv);

    char buffer_enviador[1024];
};


#endif //TALLER_SERVER_H
