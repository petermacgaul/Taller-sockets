#include <SDL2/SDL.h>

#include <pthread.h>
#include <thread>
#include <zconf.h>

#include "Server.h"
#include "Client.h"

int main( int argc, char* argv[] ) {
    Server server;
    Client cliente;

//    pthread_t hiloUno ;
//    pthread_t hiloDos ;

    if( strcmp(argv[1],"SERVER") == 0 ){
        server.initServer(argv[2]);

        thread client_acceptor ( &Server::acceptClient, server );
        client_acceptor.join();

        thread client_chatter ( &Server::chatWhitClients, server );
        client_chatter.join();

        server.closeServer();

    }

    if( strcmp(argv[1],"CLIENT") == 0 ) {


        cliente.connectToServer(argv[2], argv[3]);

        cliente.chatToServer();

        cliente.closeClient();

    }

    return 0;

}
