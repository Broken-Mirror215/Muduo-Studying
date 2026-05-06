#include <iostream>
#include "../Eventloop/Eventloop.h"
#include "../Channel/Channel.h"
#include <unistd.h>
#include "../Acceptor/Acceptor.h"
#include "../Tcpconnection/Tcpconnection.h"
#include <unordered_map>
#include <memory>
#include "../Tcpserver/Tcpserver.h"
#include "../Buffer/buffer.h"
#include "../Game-Server/Game-server.h"
#include "../Codec/Codec.h"
int main(){
    Eventloop loop;
    Tcpserver server(&loop,"127.0.0.1",8080);
    gServer GameServer;

    Codec codec([&GameServer](const std::shared_ptr<Tcpconnection> & conn,const std::string&msg) 
    {
        std::cout<<"business msg "<<msg<<std::endl;
        GameServer.onMessage(conn,msg);
    });
    server.setmessageback([&codec](const std::shared_ptr<Tcpconnection>& conn,Buffer* buf){
        codec.OnMessage(conn,buf);
    });

    server._setConnectionback([&GameServer](const std::shared_ptr<Tcpconnection>& conn){
        GameServer.onConnect(conn);
    });

    server._setCloseConnback([&GameServer](const std::shared_ptr<Tcpconnection>& conn){
        GameServer.onDisconnect(conn);
    });
    server.start();
    loop.loop();
}
