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

    /*    // Create Socket
    // int socket(int domain, int type, int protocol);
    // Domain: AF_INET (IPv4 Internet protocols)
    // Type: SOCK_STREAM (Provides  sequenced,  reliable, two-way connection-based byte streams.)
    // Protocol: 0 (chosen automatically)*/
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Could not create socket");
        return -1;
    }
    printf("Socket created\n");
    //------------------------

    // Prepare the sockaddr_in structure
    /* Structures for handling internet addresses
    struct sockaddr_in {
        short            sin_family;   // e.g. AF_INET
        unsigned short   sin_port;     // e.g. htons(3490)
        struct in_addr   sin_addr;     // see struct in_addr, below
        char             sin_zero[8];  // zero this if you want to
    };
    struct in_addr {
        unsigned long s_addr;  // load with inet_aton()
    }; */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //Address to accept any incoming messages. INADDR_ANY accepts any.
    server_addr.sin_port = htons( port ); // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.


    // Habilito el puerto a conectar.
    int val = 1;
    setsockopt(serverSocket,SOL_SOCKET,SO_REUSEPORT,&val,sizeof(val));

    /*
         Bind
         int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
         sockfd -> file descriptor that refers to a socket
         addr -> pointer to sockaddr_in structure of the SERVER
         addrlen -> size of the sockaddr_in structure
         bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd.
    */

    if (bind(serverSocket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed. Error");
        return -1;
    }
    printf("Bind done\n");
    //------------------------

    /*
    Listen
     int listen(int sockfd, int backlog);
     sockfd -> file descriptor that refers to a socket,in this case of type SOCK_STREAM
     backlog-> The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow.
     listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept();
    */
    clientes_esperados = 2 ; //ToDo: cambiar se lee del config

    if (listen(serverSocket , clientes_esperados) < 0)
    {
        perror("Listen failed. Error");
        return -1;
    }
    server_online = true;

    return acceptClient();
}

int Server::acceptClient(){

    sockaddr_in client_addr;

    int clientAddrlen;

    /*
     Accept incoming connection from a clients
     int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
     sockfd -> socket that has been created with socket(), bound to a local address with bind(), and is listening for connections after a listen()
     addr -> pointer to a sockaddr structure for the CLIENT.
     addrlen -> size of sockaddr structure for the CLIENT.
     */

    int clientes_activos = howManyPlayersAreConnected();

    while(server_online && clientes_activos < clientes_esperados){

        int clientSocket = accept(serverSocket, (struct sockaddr *) &client_addr, (socklen_t*) &clientAddrlen);

        if (clientSocket < 0)
        {
            perror("Accept failed");
            continue;
        }

        printf("\nConnection accepted\n");

        clientes_activos++;

        client_info* client = &clients[clientSocket];
        client->clientSocket = clientSocket;
        client->clientAddrlen = clientAddrlen;
        client->isConnected = true;
        initializeData(&client->view);

        if(clients.size() == 1){
            thread hiloDesencolador(&Server::desencolar, this );
            hiloDesencolador.detach();
        }

        thread hiloChatter(&Server::chatWhitClients, this , client->clientSocket);
        hiloChatter.detach();
    }

    while (server_online){
        if (clientes_activos == clientes_esperados){
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
    int send_data_size = sizeof(struct View);

    /*
     Send
     ssize_t send(int sockfd, const void *buf, size_t len, int flags);
     sockfd -> file descriptor that refers to a socket
     buf ->  the message is found in buf.
     len -> the message and has length len
     flags
     The system call send() is used to transmit a message to another socket.
     The send() call may be used only when the socket is in a connected state (so that the intended recipient is known).
     */

    while ((send_data_size > total_bytes_written) && client->isConnected){
        bytes_written = send(client->clientSocket, (&client->view + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
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
    int receive_data_size = sizeof(struct Command);

    /*
     Receive
     ssize_t recv(int sockfd, void *buf, size_t len, int flags);
     sockfd -> file descriptor that refers to a socket
     buf -> where the received message into the buffer buf.
     len -> The caller must specify the size of the buffer in len.
     flags
     The recv() call are used to receive messages from a socket.
     If no messages are available at the socket, the receive call wait for a message to arrive. (Blocking)
    */

    while ((receive_data_size > bytes_receive) && client->isConnected) {
        bytes_receive = recv(client->clientSocket, (&client->command + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_WAITALL);
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

void Server::processData(Command* command, View* view) {

    int PLAYER_VEL = 10;

    if (command->command_event.type == SDL_KEYDOWN && command->command_event.key.repeat == 0) {

        //Adjust the velocity
        switch (command->command_event.key.keysym.sym) {
            case SDLK_UP:
                (*view).positionY -= PLAYER_VEL / 4;
                break;
            case SDLK_DOWN:
                (*view).positionY += PLAYER_VEL / 4;
                break;
            case SDLK_LEFT:
                (*view).positionX -= PLAYER_VEL / 3;
                break;
            case SDLK_RIGHT:
                (*view).positionX += PLAYER_VEL / 5;
                break;
        }

    }
        //If a key was released
    else if (command->command_event.type == SDL_KEYUP && command->command_event.key.repeat == 0) {

        //Adjust the velocity
        switch (command->command_event.key.keysym.sym) {
            case SDLK_UP:
                (*view).positionY += PLAYER_VEL / 4;
                break;
            case SDLK_DOWN:
                (*view).positionY -= PLAYER_VEL / 4;
                break;
            case SDLK_LEFT:
                (*view).positionX += PLAYER_VEL / 3;
                break;
            case SDLK_RIGHT:
                (*view).positionX -= PLAYER_VEL / 5;
                break;
        }
    }
}

void Server::initializeData(struct View* client_view){
    (*client_view).positionX = 0;
    (*client_view).positionY = 0;
    (*client_view).velocityX = 0;
    (*client_view).velocityY = 0;
}

void Server::closeServer() {
    for (auto it=clients.begin(); it!=clients.end(); ++it) {
        if (it->second.isConnected){
            close(it->second.clientSocket);
            printf("Client socket number %d closed\n", it->second.clientSocket);
        }
    }
    server_online = false;

    printf("Server socket number %d closed\n",serverSocket);
    printf("Closing server \n");

    shutdown(serverSocket,SHUT_RDWR);
}

bool Server::playersAreConnected() {
    for (auto it=clients.begin(); it!=clients.end(); ++it){
        if (it->second.isConnected){
            return true;
        }
    }
    return false;
}

void Server::chatWhitClients(int client_socket) {
    printf("Socket of Client: %d \n\n",client_socket);
    /* ToDo: Validar credenciales */

    QueueCommand queueCommand;
    queueCommand.client_socket = client_socket;
    client_info* client = &clients[client_socket];

    while( client->isConnected && server_online ){
        receiveData(client);

        queueCommand.command = client->command;

        colaDeEventos.push(queueCommand);
    }
}

void Server::desencolar(){
    QueueCommand command;
    while ( playersAreConnected() ) {
        while (!colaDeEventos.isEmpty()) {
            command = colaDeEventos.pop();

            processData(&command.command,&clients[command.client_socket].view);

            //Mando la informacion a todos los clientes
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