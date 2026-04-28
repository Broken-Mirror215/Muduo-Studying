#pragma once
#include "../Eventloop/Eventloop.h"
#include "../Channel/Channel.h"
#include <functional>
class Tcpconnection{
public:
    using CloseCallback= std::function<void(int)>;
    Tcpconnection(Eventloop* loop,int connfd);
    

    void connestablished();
    void setcloseCallback(CloseCallback cb){
        _closeback=std::move(cb);
    }

private:
    void handleread();
    void handleclose();

private:
    Eventloop *_loop;
    int _connfd;
    Channel _channel;

    CloseCallback _closeback;
};
