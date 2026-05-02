#pragma once
#include <memory>
#include "../Tcpconnection/Tcpconnection.h"

class Tcpconnection;
class Player
{
public:
    Player(int id,const std::shared_ptr<Tcpconnection>& conn);

    int ID();

    std::shared_ptr<Tcpconnection> CON();


private:

    int _id;
    std::shared_ptr<Tcpconnection> _conn;

};