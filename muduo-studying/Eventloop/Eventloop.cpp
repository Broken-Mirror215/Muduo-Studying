#include "Eventloop.h"
#include "../Channel/Channel.h"
Eventloop::Eventloop()    
:_looping(false),
_quit(false),
_epr(new Epoller(this))
{}

void Eventloop::loop(){
    _looping =true;

    while (!_quit){
        activechannels.clear();
        //阻塞,事件注册进activechannels里面
        _epr->Epoll(10000,activechannels);
        for (auto C:activechannels){
            C->handlerEvent();
        }
        //把队列的东西放进来执行清除了
        doqueue();
    }
    _looping=false;

}

void Eventloop::quit(){
    _quit=true;
}

void Eventloop::updateChannel(Channel * c1){
    _epr->updateChannel(c1);
}

void Eventloop::removeChannel(Channel* c1){
    _epr->removeChannel(c1);
}

void Eventloop::queueinLoop(functor cb){
    _pendingfunctors.push_back(cb);   
}

void Eventloop::doqueue(){
    std::vector<functor> functors;
    functors.swap(_pendingfunctors);
    for (const functor& functor : functors)
    {
        functor();
    }
}


