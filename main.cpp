
#include "Server.h"
#include "Client.h"

int main( int argc, char* argv[] ) {

    if( argc == 3 && strcmp(argv[1],"SERVER") == 0 ){

        Server server;

        return server.initServer(argv[2]);

    }

    if( argc == 4 && strcmp(argv[1],"CLIENT") == 0 ) {

        Client cliente;

        if( cliente.connectToServer(argv[2], argv[3]) == 0){
            printf("Play the game");
        }
    }

    return 0;

}
