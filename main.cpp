#include <SDL2/SDL.h>
#include <pthread.h>
#include "Server.h"
#include "Client.h"

const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 600;

const int MINIMUM_AMOUNT_OF_ARGUMENTS = 1;
const int AMOUNT_OF_ARGUMENTS_WITH_LEVEL = 2;
const int LEVEL = 1;

int main( int argc, char* argv[] ) {
    Server server;
    Client cliente;

    if( strcmp(argv[1],"SERVER") == 0 ){

        server.initServer(argv[2]);

        server.acceptClient();

        server.start();
    }

    if( strcmp(argv[1],"CLIENT") == 0 ) {

        cliente.setPort(argv[3]);
        cliente.setIP(argv[2]);

        pthread_t hiloUno ;
        pthread_t hiloDos ;
        pthread_create(&hiloUno, NULL, cliente.connectToServer(), NULL );



        printf("Seguro hay que agregar un thread\n");

    }
    server.closeServer();

    cliente.closeClient();

    return 0;

}
