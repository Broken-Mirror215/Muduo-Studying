#pragma once
#include <memory>
#include "../Player/Player.h"
class  Room
{
public:
    Room(int id);


    bool Full();

    void Join(std::shared_ptr<Player>&);//每次只添加一位玩家喵

private:
    int _id;
    std::shared_ptr<Player> _c1;
    std::shared_ptr<Player> _c2;
};
