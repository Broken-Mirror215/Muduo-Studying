#include "Acceptor.h"
Acceptor::Acceptor(Eventloop * loop,const char *ip,const uint32_t&port)
:_loop(loop),
sock(port,ip),
acceptChannel(loop,sock._sockfd)
{
    sock.Bind();
    Socket::Setnonblock(sock._sockfd);

    acceptChannel.SetReadCallBack([this]{
        handleRead();
    });

}

void Acceptor::connReadback (newconnReadback cb){
    back=std::move(cb);
}

void Acceptor::listen(){
    sock.Listen();
    acceptChannel.enableReading();//这个不用设置fd的吗？
}

void Acceptor::handleRead(){
    Socket::Clientsocket client;
    int connfd=sock.Accept(client);
    Socket::Setnonblock(connfd);




}