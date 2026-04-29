#pragma once
#include "../Eventloop/Eventloop.h"
#include "../Channel/Channel.h"
#include <functional>
#include <memory>
#include <string>
#include "../Buffer/buffer.h"
class Tcpconnection:public std::enable_shared_from_this<Tcpconnection>
{
public:
    using Connptr=std::shared_ptr<Tcpconnection>;
    using CloseCallback= std::function<void(int)>;
    using MessageCallback=std::function<void(const Connptr&,Buffer*)>;
    Tcpconnection(Eventloop* loop,int connfd);
    

    void connestablished();
    void setcloseCallback(CloseCallback cb){
        _closeback=std::move(cb);
    }

    void setmessageback(MessageCallback cb);

    void send(const std::string& msg);

private:
    void handleread();
    void handleclose();

private:
    Eventloop *_loop;
    int _connfd;
    Channel _channel;

    CloseCallback _closeback;
    MessageCallback _messageback;
    Buffer _inputbuffer;
};
