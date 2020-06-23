#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Client.h"

int Client::connectToServer(char *ip, char *puerto) {

    printf("Arguments: 1) ip: %s ,2) port: %s \n", ip, puerto);

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Could not create socket");
        return -1;
    }
    printf("Socket created\n");

    server.sin_addr.s_addr = inet_addr((const char *) ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(puerto));

    if (connect(client_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        isConnected = false;
        return -1;
    }
    else {
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

        strcpy(buffer_enviado, "Enviado mensaje del cliente al servidor");

        // Send data (command)
        if ( sendData() < 0 && isConnected) {
            perror("Send Data Error");
            isConnected = false;
        }
    }
    closeClient();
}

void Client::chatToServer(){
    while(isConnected){
        // Receive data (view)
        if (receiveData() < 0 && isConnected){
            perror("Receive Data Error");
            isConnected = false;
        }
        printf("mensaje recibido: %s \n", buffer_receptor );
    }
    closeClient();
}

int Client::sendData() {
    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(buffer_enviado);

    while ((send_data_size > total_bytes_written) && isConnected){
        bytes_written = send(client_socket, (buffer_enviado + total_bytes_written), (send_data_size-total_bytes_written), MSG_NOSIGNAL);

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

int Client::receiveData() {
    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(buffer_receptor);

    while ((receive_data_size > bytes_receive) && isConnected) {
        bytes_receive = recv(client_socket, (buffer_receptor + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);

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
    game->close();
}

void Client::endGame(){
    game->close();
}

