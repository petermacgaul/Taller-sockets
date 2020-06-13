#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Client.h"

int Client::connectToServer(char *ip, char *puerto) {

    printf("Arguments: 1) ip: %s ,2) port: %s \n", ip, puerto);

    /*
     Create Socket
     int socket(int domain, int type, int protocol);
     Domain: AF_INET (IPv4 Internet protocols)
     Type: SOCK_STREAM (Provides  sequenced,  reliable, two-way connection-based byte streams.)
     Protocol: 0 (chosen automatically)
    */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Could not create socket");
        return -1;
    }
    printf("Socket created\n");

    // Prepare the sockaddr_in structure
    server.sin_addr.s_addr = inet_addr((const char *) ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(puerto));
    //------------------------

    /*
     Connect to remote server
     int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
     sockfd -> file descriptor that refers to a socket
     addr -> pointer to sockaddr_in structure for the SERVER.
     addrlen -> size of sockaddr_in structure for the SERVER.
     The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr.
     */

    if (connect(client_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        isConnected = false;
        return -1;
    } else {
        printf("Connected\n\n");
        isConnected = true;

        thread hiloReciver(&Client::chatToServer,this) ;
        hiloReciver.detach();

        thread hiloSender(&Client::sendDataToServer,this) ;
        hiloSender.detach();

        game = new GameRunner();
        game->runGame(&q);
    }
    return 0;
}

void Client::sendDataToServer(){

    //keep communicating with server
    while(isConnected) {
        int result = 0;

        if (!q.empty()){
            SDL_Event event = q.front();
            result = processEvent( event );
            q.pop();
            command.command_event = result;
            printf("Commando mandado : %d ",result);
        }

        // Send data (command)
        if (sendData(&client_socket, &command) < 0 && isConnected) {
            perror("Send Data Error");
            isConnected = false;
        }
    }
    closeClient();
}

void Client::chatToServer(){
    while(isConnected){
        // Receive data (view)
        if (receiveData(&client_socket, &view) < 0 && isConnected){
            perror("Receive Data Error");
            isConnected = false;
        }
        game->sendView(view.positionX,view.positionY);
    }
    closeClient();
}

int Client::sendData(int *client_socket, struct Command *client_command) {
    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(struct Command);

    while ((send_data_size > total_bytes_written) && isConnected){
        bytes_written = send(*client_socket, (client_command + total_bytes_written), (send_data_size-total_bytes_written), MSG_NOSIGNAL);

        if (bytes_written < 0) { // Error
            return bytes_written;
        }
        else if (bytes_written == 0) { // Socket closed
            isConnected = false;
        }
        else {
            total_bytes_written += bytes_written;
        }
    }

    return 0;
}

int Client::receiveData(int *client_socket, struct View *client_view) {
    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(struct View);

    while ((receive_data_size > bytes_receive) && isConnected) {
        bytes_receive = recv(*client_socket, (client_view + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);

        if (bytes_receive < 0) { // Error
            return bytes_receive;
        }
        else if (bytes_receive == 0) { // Socket closed
            isConnected = false;
        }
        else {
            total_bytes_receive += bytes_receive;
        }
    }
    return 0;
}

void Client::closeClient() {
    close(client_socket);
    printf("Socket number %d closed\n", client_socket);
}

int Client::processEvent(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    return 1;
                case SDLK_DOWN:
                    return -1;
                case SDLK_LEFT:
                    return 2;
                case SDLK_RIGHT:
                    return -2;
                default:
                    break;
            }
            break;
    }
    return 0;
}

