//
// Created by peter on 13/6/20.
//

#include "GameRunner.h"

void GameRunner::runGame(queue<SDL_Event> * q) {

    this->q = *q;

    SDL_Event event;
    int quit = 0;

    /* Initialise SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
        fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
        exit( -1 );
    }

    /* Set a video mode */
    SDL_Window *screen = SDL_CreateWindow("My Game Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_OPENGL);


    /* Loop until an SDL_QUIT event is found */
    while( !quit ) {
        /* Poll for events */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
            switch (event.key.type){
                case SDL_KEYDOWN:
                    q->push(event);
                    break;
                case SDL_KEYUP:
                    q->push(event);
                    break;
            }
        }
    }
    /* Clean up */
    SDL_Quit();
    exit( 0 );
}

void GameRunner::sendView(int x, int y) {

    this->x = x;
    this->y = y;

}

void GameRunner::close(){
    SDL_Quit();
}
