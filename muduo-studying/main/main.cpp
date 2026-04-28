#include <iostream>
#include "../Eventloop/Eventloop.h"
#include "../Channel/Channel.h"
#include <unistd.h>
#include "../Acceptor/Acceptor.h"
#include "../Tcpconnection/Tcpconnection.h"
#include <unordered_map>
#include <memory>
int main(){
    Eventloop loop;
    // Socket::ServerSocket sock(8080,"127.0.0.1");
    // sock.Bind();
    // Socket::Setnonblock(sock._sockfd);
    // sock.Listen();
    
    // Channel listenchannel(&loop,sock._sockfd);
    //这是给listenchannel注册连接到来处理
    Acceptor acceptor(&loop,"127.0.0.1",8080);
     std::unordered_map<int,std::shared_ptr<Tcpconnection>> conns;
    acceptor.connReadback([&loop,&conns](int connfd)
    {
        if (connfd<0){
            std::cout<<"accpet error"<<std::endl;
            return;
        }
        Socket::Setnonblock(connfd);

        auto conn=std::make_shared<Tcpconnection>(&loop,connfd);
        conns[connfd]=conn;

        conn->setcloseCallback([&conns,&loop](int fd){
            std::cout << "remove connection fd = " << fd << std::endl;
            loop.queueinLoop([&conns,fd]{
                auto it = conns.find(fd);
                if (it != conns.end())
                {
                    conns.erase(it);
                }
            });
            
        });
        conn->connestablished();
    });

    acceptor.listen();
    //上面为连接注册好了回调。


    //下面是事件处理
    loop.loop();
}
