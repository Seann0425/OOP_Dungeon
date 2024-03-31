#ifndef ROOM
#define ROOM

#include <array>
#include <vector>

#include "Object.h"

enum Ecosystem { Desert, Forest, Swamp };

class Room {
public:
    Room();
    // the value is set temporarily to simplify developer's work
    static const size_t room_height = 15;
    static const size_t room_width = 15;
    void setEco(Ecosystem);
private:
    // currently deemed as not necessary
    // right, down, left, up
    // std::array<Room*, 4> adjRooms;
    std::vector<Object*> objects;
    Ecosystem eco;
};
#endif