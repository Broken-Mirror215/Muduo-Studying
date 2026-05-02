#include "Player.h"

Player::Player(int id,const std::shared_ptr<Tcpconnection>& conn)
:_id(id),
_conn(conn)
{}

int Player::ID(){
    return _id;
}

std::shared_ptr<Tcpconnection> Player::CON()
{
    return _conn;
}