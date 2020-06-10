
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
        T item = cola.front();
        cola.pop();
        cantidadDeElementos--;
        mutexLocker.unlock();
        return item;
    }

    bool isEmpty(){
        return cantidadDeElementos == 0;
    }
};


#endif //UNTITLED1_COLAMULTIHILO_H
