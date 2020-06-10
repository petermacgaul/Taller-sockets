#ifndef TALLER_SERVER_H
#define TALLER_SERVER_H

#include <netinet/in.h>
#include <vector>
#include <thread>

#include "ColaMultiHilo.h"
#include "CommunicateData.h"
#include <map>

using namespace std;

struct QueueCommand{
    Command command;
    int client_socket;
};

typedef struct Cliente {
    bool isConnected;
    int clientSocket;
    int clientAddrlen;
    View view;
    Command command;
} client_info;

class Server {
    int serverSocket;

    map<int,client_info> clients;

    int clientes_esperados;

    ColaMultiHilo<QueueCommand> colaDeEventos;

    void initializeData(struct View* client_view);

    void processData(Command* command, View* view);

    int sendData(client_info *client);

    void desencolar();

    int enviarInformacionAClientes();


public:
    void initServer(char *argv);

    void acceptClient();

    void chatWhitClients(int client_socket);

    int receiveData(client_info *client);

    void closeServer();

    bool playersAreConnected();

    bool server_online;
};


#endif //TALLER_SERVER_H
