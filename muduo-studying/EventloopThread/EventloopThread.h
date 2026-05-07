#pragma once
#include "../Eventloop/Eventloop.h"
#include <pthread.h>
class EventloopThread{
public:
    EventloopThread();
    
    Eventloop* EventloopStart();
    void Threadfunc();

private:
    static void* StartThread(void * arg);
    
private:
    Eventloop * _loop;
    bool _existing;
    bool _started;

    pthread_t _threadid;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
};