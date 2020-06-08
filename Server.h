#ifndef TALLER_SERVER_H
#define TALLER_SERVER_H

#include <netinet/in.h>
#include <vector>
#include <thread>

#include "CommunicateData.h"

using namespace std;

typedef struct Client {
    bool isConnected;
    int clientSocket;
    int clientAddrlen;
    thread* hilo;
    View view;
    Command command;
} client_info;

class Server {
    int serverSocket;
    //ToDo: 2 Threads del server, 1 para enviar data, otro para aceptar clientes

    client_info* clients;

    int clientes_esperados;

    vector<client_info> connections;

    struct Command client_command;

    void initializeData(struct View* client_view);

    bool playersAreConnected();

    void processData(SDL_Event event, struct View* view);

    int sendData(struct View* client_view);

    void desencolar();

    int enviarInformacionAClientes();


public:
    void initServer(char *argv);

    void acceptClient();

    void chatWhitClients();

    int receiveData(client_info *client);

    void closeServer();

};


#endif //TALLER_SERVER_H
