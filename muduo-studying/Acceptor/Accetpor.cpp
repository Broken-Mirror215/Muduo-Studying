#include "Acceptor.h"
#include <cstdlib>
#include <cstdio>
Acceptor::Acceptor(Eventloop * loop,const char *ip,const uint16_t&port)
:_loop(loop),
sock(port,ip),
acceptChannel(loop,sock._sockfd)
{
    if (sock.Bind()<0){
        perror("bind error");
        std::abort();
    }
    Socket::Setnonblock(sock._sockfd);

    //accpetor设置了读的fd
    acceptChannel.SetReadCallBack([this](){
            handleRead();
    });
}

void Acceptor::setconnReadback (newconnReadback cb){
    _ConnReadback=std::move(cb);
}

void Acceptor::listen(){
    if (sock.Listen()<0){
        perror("listen error");
        std::abort();
    }
    acceptChannel.enableReading();
}

void Acceptor::handleRead(){
    Socket::Clientsocket client;
    int connfd=sock.Accept(client);
    if (connfd<0){
        std::cout<<"accpet error"<<std::endl;
        return;
    }
    Socket::Setnonblock(connfd);

    //如果这个函数对象不是空的就可以进去了
    if (_ConnReadback){
        _ConnReadback(connfd);
    }

}
