#ifndef TALLER_SERVER_H
#define TALLER_SERVER_H

#include <netinet/in.h>
#include <vector>

#include "CommunicateData.h"

using namespace std;

typedef struct Cliente {
    bool isConnected;
    int clientSocket;
    int clientAddrlen;
} client_info;

class Server {
    int serverSocket;
    //ToDo: 2 Threads del server, 1 para enviar data, otro para aceptar clientes

    client_info client;

    int clientes_activos; //Todo: Cambiar este field a Len de connections
    int clientes_esperados;

    vector<client_info> connections;

    struct Command client_command;
    struct View client_view;

    void initializeData(struct View* client_view);

    bool playersAreConnected();

    int receiveData(struct Command* client_command);

    void processData(SDL_Event event, struct View* view);

    int sendData(struct View* client_view);

    void desencolar();

    int enviarInformacionAClientes();


public:
    void initServer(char *argv);

    void acceptClient();

    void chatWhitClients();

    void closeServer();

};


#endif //TALLER_SERVER_H
