#pragma once
#include <memory>
#include <string>
#include "../Player/Player.h"
class  Room
{
public:
    Room(int id);


    bool Full();

    void Join(const std::shared_ptr<Player>&);//每次只添加一位玩家喵

    void Forward(const std::shared_ptr<Player>& from,const std::string& msg);

    void Broadcast(const std::string& msg);

private:
    int _id;
    std::shared_ptr<Player> _c1;
    std::shared_ptr<Player> _c2;
};
