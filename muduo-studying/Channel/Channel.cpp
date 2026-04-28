#include "Channel.h"
#include "../Eventloop/Eventloop.h"
#include <sys/epoll.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(Eventloop *looper,int fd)
:_fd(fd),
_looper(looper),
_events(kNoneEvent),
_revents(kNoneEvent)
{}



void Channel::update()
{
    _looper->updateChannel(this);
}

void Channel::enableReading(){
    _events |=kReadEvent;
    update();
}

void Channel::disableReading(){
    _events &= ~kReadEvent;
    update();
}

void Channel::enableWriting(){
    _events |=kWriteEvent;
    update();
}

void Channel::disableWriting(){
    _events &=~kWriteEvent;
    update();
}

void Channel::Noneall()
{
    _events = kNoneEvent;
    update();
}

void Channel::handlerEvent()
{
    if ((_revents & EPOLLIN) && readCallback_)
    {
        readCallback_();
    }

    if ((_revents & EPOLLOUT) && writeCallback_)
    {
        writeCallback_();
    }
}

void Channel::removeChannel(){
    _looper->removeChannel(this);
}

