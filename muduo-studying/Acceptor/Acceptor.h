#pragma once
#include <string>
#include "../Eventloop/Eventloop.h"
#include "../Socket/Socket.h"
using newconnReadback=std::function<void(int)>;//逆天回调
class Acceptor
{
public:
    Acceptor(Eventloop * loop,const char *ip="127.0.0.1",const uint16_t&port=8080);

    void connReadback(newconnReadback cb);


    void listen();


    void handleRead();

private:

    Eventloop * _loop;
    newconnReadback back;
    Socket::ServerSocket sock;
    //fd要利用管道链路注册
    Channel acceptChannel;
};