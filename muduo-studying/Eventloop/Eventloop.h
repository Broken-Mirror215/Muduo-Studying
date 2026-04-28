#pragma once
#include <memory>
#include <vector>
#include "../Epoller/Epoller.h"
#include <functional>
#include <vector>
class Epoller;
class Channel;
typedef std::vector<Channel*> Channellist;
class Eventloop
{
public:

    using functor=std::function<void()>;
    Eventloop();
    void loop();
    void quit();


    void updateChannel(Channel * c1);//事件注册

    void removeChannel(Channel* c1);//

    void queueinLoop(functor cb);
    void doqueue();
private:
    bool _looping;
    bool _quit;
    std::shared_ptr<Epoller > _epr;
    Channellist activechannels;

    std::vector<functor> _pendingfunctors;
};
