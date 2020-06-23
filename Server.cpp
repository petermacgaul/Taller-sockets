#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>


int Server::initServer(char *argv) {

    int port = atoi(argv);

    struct sockaddr_in server_addr;

    printf("Arguments: 1) port: %d \n", port);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Could not create socket");
        return -1;
    }
    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //Address to accept any incoming messages. INADDR_ANY accepts any.
    server_addr.sin_port = htons( port ); // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.

    int val = 1;
    setsockopt(serverSocket,SOL_SOCKET,SO_REUSEPORT,&val,sizeof(val));

    if (bind(serverSocket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed. Error");
        return -1;
    }
    printf("Bind done\n");

    expectedClients = 2 ; //ToDo: cambiar se lee del config

    if (listen(serverSocket , expectedClients) < 0)
    {
        perror("Listen failed. Error");
        return -1;
    }
    serverOnline = true;

    return acceptClient();
}

int Server::acceptClient(){
    sockaddr_in client_addr;

    int clientAddrlen;

    struct timeval tv;
    tv.tv_sec = 30;
    tv.tv_usec = 0;

    int clientes_activos = howManyPlayersAreConnected();

    while(serverOnline && clientes_activos < expectedClients){

        int clientSocket = accept(serverSocket, (struct sockaddr *) &client_addr, (socklen_t*) &clientAddrlen);

        if (clientSocket < 0)
        {
            perror("Accept failed");
            continue;
        }

        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        setsockopt(clientSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof tv);

        printf("\nConnection accepted\n");

        clientes_activos++;

        client_info* client = &clients[clientSocket];
        client->clientSocket = clientSocket;
        client->clientAddrlen = clientAddrlen;
        client->isConnected = true;
        initializeData();

        if(clients.size() == 1){
            thread hiloDesencolador(&Server::popCommand, this );
            hiloDesencolador.detach();
        }

        thread hiloChatter(&Server::chatWhitClients, this , client->clientSocket);
        hiloChatter.detach();
    }

    while (serverOnline){
        if (clientes_activos == expectedClients){
            clientes_activos = howManyPlayersAreConnected();
            usleep(1000);
        }
        else{
            return acceptClient();
        }
    }
    return 0;
}

int Server::sendData(client_info *client) {

    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(buffer_enviador);

    while ((send_data_size > total_bytes_written) && client->isConnected){
        bytes_written = send(client->clientSocket, (&buffer_enviador + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
        if (bytes_written < 0) { // Error
            client->isConnected = false;
            return bytes_written;
        }
        else if (bytes_written == 0) { // Socket closed
            client->isConnected = false;
        }
        else {
            total_bytes_written += bytes_written;
        }
    }

    return 0;
}

int Server::receiveData(client_info *client){

    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(buffer);

    while ((receive_data_size > bytes_receive) && client->isConnected) {
        bytes_receive = recv(client->clientSocket, (&buffer + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_WAITALL);
        if (bytes_receive < 0) { // Error
            client->isConnected = false;
            return bytes_receive;
        }
        else if (bytes_receive == 0) { // Socket closed
            client->isConnected = false;
        }
        else {
            total_bytes_receive += bytes_receive;
        }
    }

    return 0;
}

char * Server::processData(char* comando) {
    printf("Mensaje recibido: %s \n", comando);
    return "Enviado mensaje del servidor ";
}

void Server::initializeData(){
    memset( buffer_enviador,0 ,sizeof(buffer_enviador) );
    strcpy( buffer_enviador, " Conectado ");
}

void Server::closeServer() {
    for (auto it=clients.begin(); it!=clients.end(); ++it) {
        if (it->second.isConnected){
            close(it->second.clientSocket);
            printf("Client socket number %d closed\n", it->second.clientSocket);
        }
    }
    serverOnline = false;

    printf("Server socket number %d closed\n",serverSocket);
    printf("Closing server \n");

    shutdown(serverSocket,SHUT_RDWR);
}

void Server::chatWhitClients(int client_socket) {
    printf("Socket of Client: %d \n\n",client_socket);
    /* ToDo: Validar credenciales */

    QueueCommand queueCommand;
    queueCommand.client_socket = client_socket;
    client_info* client = &clients[client_socket];

    while(client->isConnected && serverOnline ){
        receiveData(client);

        if(queueCommand.process_event) {

            queueCommand.buffer_command = buffer;

            eventQueue.push(queueCommand);
        }
    }
}

void Server::popCommand(){
    QueueCommand command;
    while ( howManyPlayersAreConnected() != 0 ) {
        while (!eventQueue.isEmpty()) {
            command = eventQueue.pop();

            strcpy(buffer_enviador, processData(command.buffer_command));

            for (auto it=clients.begin(); it!=clients.end(); ++it){
                if (&it->second.isConnected)
                    sendData(&it->second);
            }
        }
        usleep(1000);
    }
    closeServer();
}

int Server::howManyPlayersAreConnected(){
    int i = 0;
    for (auto it=clients.begin(); it!=clients.end(); ++it){
        if (it->second.isConnected){
            i++;
        }
    }
    return i;
}