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
    using Connectionback=std::function<void(const TcpconnectionPtr&)>;

    Tcpserver(Eventloop* loop, const char *ip, uint16_t port);
    void start();

    void setmessageback(const MessageCallback& cb);

    void _setConnectionback(const Connectionback& cb);

private:
    void newConnection(int connfd);
    void removeConnection(int fd);

private:
    Eventloop* _loop;
    Acceptor _acceptor;

    std::unordered_map<int, TcpconnectionPtr> _conns;
    MessageCallback _messageback;
    Connectionback _connback;

};