//
// Created by peter on 13/6/20.
//

#ifndef UNTITLED1_GAMERUNNER_H
#define UNTITLED1_GAMERUNNER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <queue>

using namespace std;

class GameRunner {

public:

    void runGame(queue<SDL_Event> * q);

    queue<SDL_Event> q;

    void PrintKeyInfo(SDL_KeyboardEvent *pEvent);

    void sendView(int x, int y);

    int x;
    int y;
};


#endif //UNTITLED1_GAMERUNNER_H
