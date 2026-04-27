#include <iostream>
#include "../Eventloop/Eventloop.h"
#include "../Channel/Channel.h"
#include <unistd.h>
#include "../Acceptor/Acceptor.h"
int main(){
    Eventloop loop;
    Socket::ServerSocket sock(8080,"127.0.0.1");
    sock.Bind();
    Socket::Setnonblock(sock._sockfd);
    sock.Listen();
    
    Channel listenchannel(&loop,sock._sockfd);
    //这是给listenchannel注册连接到来处理
    listenchannel.SetReadCallBack([&loop,&sock]()
    {
        Socket::Clientsocket clientsock;
        int connfd=sock.Accept(clientsock);
        Socket::Setnonblock(connfd);
        if (connfd<0){
            std::cout<<"accpet error"<<std::endl;
            return;
        }

        Channel * connChannel=new Channel(&loop,connfd);
        connChannel->SetReadCallBack([&loop,connfd](){
            char buffer[1024];
            int n=::read(connfd,buffer,sizeof(buffer)-1);
             if (n > 0)
            {
                std::string msg(buffer, n);
                std::cout << "client says: " << msg;

                if (msg.find("quit") != std::string::npos)
                {
                    loop.quit();
                }
            }
            else if (n == 0)
            {
                std::cout << "client closed fd = " << connfd << std::endl;
                ::close(connfd);
            }
            else
            {
                std::cout << "read error fd = " << connfd << std::endl;
                ::close(connfd);
            }
        });
        //注册是把fd放进内核
        connChannel->enableReading();
    });

    listenchannel.enableReading();
    //上面为连接注册好了回调。


    //下面是事件处理
    loop.loop();
}