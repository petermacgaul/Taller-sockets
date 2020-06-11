#ifndef UNTITLED1_COMMUNICATEDATA_H
#define UNTITLED1_COMMUNICATEDATA_H

#include <SDL2/SDL.h>

struct Command {
    int command_event ;
};

struct View {
    int positionX;
    int positionY;
    int velocityX;
    int velocityY;
};

#endif //UNTITLED1_COMMUNICATEDATA_H
