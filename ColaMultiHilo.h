//
// Created by peter on 7/6/20.
//

#ifndef UNTITLED1_COLAMULTIHILO_H
#define UNTITLED1_COLAMULTIHILO_H

#include <queue>
#include <mutex>

using namespace std;

template<typename T>

class ColaMultiHilo {
public:
    queue<T> cola;
    mutex mutexLocker;
    int cantidadDeElementos;

    ColaMultiHilo<T>(){
        cantidadDeElementos = 0;
    }

    void push(T item){
        mutexLocker.lock();
        cola.push(item);
        cantidadDeElementos++;
        mutexLocker.unlock();
    }

    T pop(){
        mutexLocker.lock();
        cola.pop();
        cantidadDeElementos--;
        mutexLocker.unlock();
    }

    bool isEmpty(){
        return cantidadDeElementos == 0;
    }
};


#endif //UNTITLED1_COLAMULTIHILO_H
