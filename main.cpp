
#include "Server.h"
#include "Client.h"

int main( int argc, char* argv[] ) {
    Server server;
    Client cliente;

    if( argc == 3 && strcmp(argv[1],"SERVER") == 0 ){

        return server.initServer(argv[2]);

    }

    if( argc == 4 && strcmp(argv[1],"CLIENT") == 0 ) {

        cliente.connectToServer(argv[2], argv[3]);

    }

    return 0;

}
