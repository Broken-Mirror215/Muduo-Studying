#pragma once
#include <memory>
#include <vector>

class Epoller;
class Channel;
typedef std::vector<Channel*> Channellist;
class Eventloop
{
public:

    Eventloop();
    void loop();
    void quit();


    void updateChannel(Channel * c1);

private:
    bool _looping;
    bool _quit;
    std::shared_ptr<Epoller > _epr;
    Channellist activechannels;
};
