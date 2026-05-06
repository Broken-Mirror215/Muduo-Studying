#include "Room.h"

Room::Room(int id)
:_id(id)
{}


bool Room::Full(){
    return _c1!=nullptr&&_c2!=nullptr;
}

void Room::Join(const std::shared_ptr<Player> & player)
{
    if (!_c1){
        _c1=player;
    }   
    else if (!_c2){
        _c2=player;
    }
}

void Room::Forward(const std::shared_ptr<Player>& from,const std::string& msg){
    if (!_c1||!_c2){
        return;
    }
    if (from==_c1){
        _c2->CON()->send(msg);
    }
    if (from==_c2){
        _c1->CON()->send(msg);
    }
}

void Room::Broadcast(const std::string& msg)
{
    if (_c1) {
        _c1->CON()->send(msg);
    }

    if (_c2) {
        _c2->CON()->send(msg);
    }
}



