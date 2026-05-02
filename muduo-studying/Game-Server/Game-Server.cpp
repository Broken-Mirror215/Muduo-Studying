#include "Game-server.h"

gServer::gServer()
:_nextplayerid(1),
_nextRoomid(1)
{}


void gServer::onConnect(const Connptr & conn){
    Tcpconnection* key=conn.get();
    auto p1=std::make_shared<Player>(_nextplayerid++,conn);

    _players[key]=p1;
    std::cout<<"new player id is : "<<p1->ID()<<std::endl;
    conn->send("login success id is " + std::to_string(p1->ID()));
}


void gServer::onMessage(const Connptr& conn,const std::string& msg){
    if (msg=="MATCH"){
        handlematch(conn);
    }
    else{
        conn->send("Invaild msg");
    }
}

void gServer::handlematch(const Connptr & conn){
    Tcpconnection * key=conn.get();

    auto it=_players.find(key);
    if (it==_players.end())
    {
        conn->send("error find msg");
        return ;
    }

    auto currentplayer=it->second;
    //如果玩家进了房间，就别匹配
    if (_connRooms.find(key)!=_connRooms.end()){
        conn->send("err! player has been in the room !");
        return ;
    }

    //如果队列没人，就进队然后等
    if (_mathchqueue.empty()){
        _mathchqueue.push(currentplayer);
        std::cout<<"player "<<currentplayer->ID()<<" waiting in mathch"<<std::endl;
        conn->send("waiting");
        return ;
    }

    //如果队伍有人，就取出来去匹配。
    auto nextplayer=_mathchqueue.front();
    _mathchqueue.pop();
     //AI提示到考虑不要自匹配。
    if (nextplayer == currentplayer)
    {
        conn->send("err not math self");
        return;
    }

    int roomid=_nextRoomid++;
    auto room=std::make_shared<Room>(roomid);
    room->Join(currentplayer);
    room->Join(nextplayer);
    _Rooms[roomid]=room;

    _connRooms[currentplayer->CON().get()]=roomid;
    _connRooms[nextplayer->CON().get()]=roomid;

    std::cout<<"the room created "<<roomid
            <<"player "<<currentplayer->ID()
            <<"is vs player "<<nextplayer->ID()<<std::endl;

    currentplayer->CON()->send(
        "match success roomid "+std::to_string(roomid)+
        "p1 id :"+std::to_string(currentplayer->ID())
        );

    nextplayer->CON()->send(
        "match success roomid "+std::to_string(roomid)+
        "p2 id :"+std::to_string(nextplayer->ID())
        );

}