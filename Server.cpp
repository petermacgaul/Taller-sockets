#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


void Server::initServer(char *argv) {

    int port = atoi(argv);

    struct sockaddr_in server_addr;

    printf("Arguments: 1) port: %d \n", port);

    // Create Socket
    // int socket(int domain, int type, int protocol);
    // Domain: AF_INET (IPv4 Internet protocols)
    // Type: SOCK_STREAM (Provides  sequenced,  reliable, two-way connection-based byte streams.)
    // Protocol: 0 (chosen automatically)
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Could not create socket");
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
    server_addr.sin_port = htons(
            port); // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
    //------------------------

    int val = 1;

    setsockopt(serverSocket,SOL_SOCKET,SO_REUSEPORT,&val,sizeof(val));

    // Bind
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    // sockfd -> file descriptor that refers to a socket
    // addr -> pointer to sockaddr_in structure of the SERVER
    // addrlen -> size of the sockaddr_in structure
    // bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd.
    if (bind(serverSocket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed. Error");
    }
    printf("Bind done\n");
    //------------------------

    // Listen
    // int listen(int sockfd, int backlog);
    // sockfd -> file descriptor that refers to a socket,in this case of type SOCK_STREAM
    // backlog-> The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow.
    // listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept();

    initializeData(&client_view);
}

int Server::sendData(struct View* client_view){

    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(struct View);

    // Send
    // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    // sockfd -> file descriptor that refers to a socket
    // buf ->  the message is found in buf.
    // len -> the message and has length len
    // flags
    // The system call send() is used to transmit a message to another socket.
    // The send() call may be used only when the socket is in a connected state (so that the intended recipient is known).

    while ((send_data_size > total_bytes_written) && client.isConnected){
        bytes_written = send(client.clientSocket, (client_view + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
        if (bytes_written < 0) { // Error
            return bytes_written;
        }
        else if (bytes_written == 0) { // Socket closed
            client.isConnected = false;
        }
        else {
            total_bytes_written += bytes_written;
        }
    }

    return 0;
}

int Server::receiveData(struct Command* client_command){

    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(struct Command);

    // Receive
    // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    // sockfd -> file descriptor that refers to a socket
    // buf -> where the received message into the buffer buf.
    // len -> The caller must specify the size of the buffer in len.
    // flags
    // The recv() call are used to receive messages from a socket.
    // If no messages are available at the socket, the receive call wait for a message to arrive. (Blocking)

    while ((receive_data_size > bytes_receive) && client.isConnected) {
        bytes_receive = recv(client.clientSocket, (client_command + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);
        if (bytes_receive < 0) { // Error
            return bytes_receive;
        }
        else if (bytes_receive == 0) { // Socket closed
            client.isConnected = false;
        }
        else {
            total_bytes_receive += bytes_receive;
        }
    }

    return 0;
}

void Server::acceptClient(){
    int clientes_esperados = 1;

    if (listen(serverSocket , clientes_esperados) < 0)
    {
        perror("Listen failed. Error");
    }

    //------------------------
    // Accept incoming connection from a client
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    // sockfd -> socket that has been created with socket(), bound to a local address with bind(), and is listening for connections after a listen()
    // addr -> pointer to a sockaddr structure for the CLIENT.
    // addrlen -> size of sockaddr structure for the CLIENT.
    client.clientSocket = accept(serverSocket, (struct sockaddr *) &client_addr, (socklen_t*) &client.clientAddrlen);
    if (client.clientSocket < 0)
    {
        perror("Accept failed");
    }
    printf("Connection accepted\n\n");

    client.isConnected = true;
}

void Server::processData(SDL_Event event, struct View* view) {

    int PLAYER_VEL = 10;

    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
        client.isConnected = false;
    }
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {

        //Adjust the velocity
        switch (event.key.keysym.sym) {
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
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {

        //Adjust the velocity
        switch (event.key.keysym.sym) {
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
    close(client.clientSocket);
    printf("Client socket number %d closed\n",client.clientSocket);
    close(serverSocket);
    printf("Server socket number %d closed\n",serverSocket);
}

bool Server::playersAreConnected() {
    return client.isConnected;
}

void Server::start() {
    while ( playersAreConnected() ) {

        // Receive data (command)
        receiveData(&client_command);

        // Process model
        processData( client_command.command_event, &client_view);
        //--------------------

        // Send data (view)
        if (sendData(&client_view) < 0) {
            perror("Send Data Error");
        }
        printf("Send data: pos(X,Y) = (%d,%d)\n\n", client_view.positionX, client_view.positionY);
        //--------------------
    }

}
