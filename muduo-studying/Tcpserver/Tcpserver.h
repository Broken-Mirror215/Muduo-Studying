#pragma once

#include "../Eventloop/Eventloop.h"
#include "../Acceptor/Acceptor.h"
#include "../Tcpconnection/Tcpconnection.h"
#include <unordered_map>
#include <memory>
#include <string>

class Tcpserver
{
public:
    using TcpconnectionPtr = std::shared_ptr<Tcpconnection>;
    using MessageCallback=Tcpconnection::MessageCallback;
    Tcpserver(Eventloop* loop, const char *ip, uint16_t port);

    void start();

    void setmessageback(const MessageCallback& cb);

private:
    void newConnection(int connfd);
    void removeConnection(int fd);

private:
    Eventloop* _loop;
    Acceptor _acceptor;

    std::unordered_map<int, TcpconnectionPtr> _conns;
    MessageCallback _messageback;
};