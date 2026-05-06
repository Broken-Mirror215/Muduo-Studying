#include "Tcpserver.h"
#include "../Socket/Socket.h"

#include <iostream>

Tcpserver::Tcpserver(Eventloop* loop, const char*ip, uint16_t port)
:_loop(loop),
_acceptor(loop, ip, port)
{
    _acceptor.connReadback([this](int connfd) {
        this->newConnection(connfd);
    });
}

void Tcpserver::start()
{
    _acceptor.listen();
}

void Tcpserver::newConnection(int connfd)
{
    if (connfd < 0)
    {
        std::cout << "accept error" << std::endl;
        return;
    }

    Socket::Setnonblock(connfd);

    auto conn = std::make_shared<Tcpconnection>(_loop, connfd);

    _conns[connfd] = conn;

    conn->setcloseCallback([this](const TcpconnectionPtr& conn) {
        if (_closeback){
            _closeback(conn);
        }
        this->removeConnection(conn);
    });

    conn->setmessageback(_messageback);
    conn->connestablished();

    if (_connback)
    {
        _connback(conn);
    }
    std::cout << "new connection fd = " << connfd << std::endl;
}

void Tcpserver::removeConnection(const TcpconnectionPtr & conn)
{
    int fd=conn->fd();
    std::cout << "remove connection fd = " << fd << std::endl;

    _loop->queueinLoop([this, fd,conn] {
        auto it = _conns.find(fd);

        if (it != _conns.end()&&it->second==conn)
        {
            _conns.erase(it);
        }
    });
}

void Tcpserver::setmessageback(const MessageCallback& cb){
    _messageback=std::move(cb);
}

void Tcpserver::_setConnectionback(const Connectionback& cb){
    _connback=std::move(cb);
}

void Tcpserver::_setCloseConnback(const CloseConnback&cb){
    _closeback=std::move(cb);
}
