//
// Created by peter on 1/6/20.
//

#ifndef UNTITLED1_STRUCT_H
#define UNTITLED1_STRUCT_H

#include <SDL2/SDL.h>

struct Command {
    SDL_Event command_event ;
};

struct View {
    int positionX;
    int positionY;
    int velocityX;
    int velocityY;
};

#endif //UNTITLED1_STRUCT_H
