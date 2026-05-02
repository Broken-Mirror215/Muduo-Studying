#include "Room.h"

Room::Room(int id)
:_id(id)
{}


bool Room::Full(){
    return _c1!=nullptr&&_c2!=nullptr;
}

void Room::Join(std::shared_ptr<Player> & player)
{
    if (!_c1){
        _c1=player;
    }   
    if (!_c2){
        _c2=player;
    }
}



