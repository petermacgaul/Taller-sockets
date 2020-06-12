
#ifndef UNTITLED1_QUEUEMULTITHREAD_H
#define UNTITLED1_QUEUEMULTITHREAD_H

#include <queue>
#include <mutex>

using namespace std;

template<typename T>

class QueueMultithread {
public:
    queue<T> q;
    mutex mutexLocker;
    int elements;

    QueueMultithread<T>(){
        elements = 0;
    }

    void push(T item){
        mutexLocker.lock();
        q.push(item);
        elements++;
        mutexLocker.unlock();
    }

    T pop(){
        mutexLocker.lock();
        T item = q.front();
        q.pop();
        elements--;
        mutexLocker.unlock();
        return item;
    }

    bool isEmpty(){
        return elements == 0;
    }
};


#endif //UNTITLED1_QUEUEMULTITHREAD_H
