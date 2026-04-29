#include <iostream>
#include "../Eventloop/Eventloop.h"
#include "../Channel/Channel.h"
#include <unistd.h>
#include "../Acceptor/Acceptor.h"
#include "../Tcpconnection/Tcpconnection.h"
#include <unordered_map>
#include <memory>
#include "Tcpserver/Tcpserver.h"
#include "../Buffer/buffer.h"
int main(){
    Eventloop loop;
    Tcpserver server(&loop,"127.0.0.1",8080);
    server.setmessageback([](const std::shared_ptr<Tcpconnection>& conn,Buffer* buf){
        std::string msg=buf->ClearAll();
        std::cout<<"client says "<<msg<<std::flush;
        conn->send(msg);
    });
    server.start();
    loop.loop();
}
