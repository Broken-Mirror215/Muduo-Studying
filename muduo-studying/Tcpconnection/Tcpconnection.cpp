#include "Tcpconnection.h"

Tcpconnection::Tcpconnection(Eventloop* loop,int connfd)
:_loop(loop),
_connfd(connfd),
_channel(loop,connfd)//这里不直接传channel的原因是防止拷贝，这样多个fd表被拷贝走了。
{
    _channel.SetReadCallBack([this]{
        handleread();//塞进channel的readback里面。
    });
}


void Tcpconnection::connestablished(){
    _channel.enableReading();
}

void Tcpconnection::handleread(){
    char buffer[1024];
    int n=::read(_connfd,buffer,sizeof(buffer)-1);
    if (n > 0)
    {
        std::string msg(buffer, n);
        std::cout << "client says: " << msg << std::flush;
        if (msg.find("quit") != std::string::npos)
        {
            _loop->quit();
        }
    }
    else if (n == 0)
    {
        std::cout << "client closed fd = " << _connfd << std::endl;
        handleclose();
    }
    else
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK){
            return;
        }
        std::cout << "read error fd = " << _connfd << std::endl;
        handleclose();
    }
}

void Tcpconnection::handleclose(){
    if (_connfd<0){
        return ;
    }
    int fd=_connfd;
    //先清除关心的事件
    _channel.Noneall();
    //从epoll中删除这个channel
    _channel.removeChannel();
    //关闭fd
    ::close(_connfd);
    _connfd=-1;
    if (_closeback){
        _closeback(fd);
    }
}
