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

void Tcpconnection::setmessageback(MessageCallback cb){
    _messageback = std::move(cb);
}

void Tcpconnection::handleread(){
    char buffer[1024];
    int n=::read(_connfd,buffer,sizeof(buffer)-1);
    if (n > 0)
    {
        _inputbuffer.Append(buffer,n);
        // std::cout << "client says: " << msg << std::flush;
        // if (msg.find("quit") != std::string::npos)
        // {
        //     _loop->quit();
        // }
        if (_messageback)
        {
            _messageback(shared_from_this(),&_inputbuffer);//这个是AI写的，我有点没看懂...
            //把自己和消息一起给上层
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
    if (_closeback){
        _closeback(shared_from_this());
    }

       _connfd=-1;
}

void Tcpconnection::send(const std::string& msg){
    ::write(_connfd,msg.data(),msg.size());
}

int Tcpconnection::fd(){
    return _connfd;
}
