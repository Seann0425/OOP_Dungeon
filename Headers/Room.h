#ifndef ROOM
#define ROOM

#include <array>
#include <vector>

#include "Object.h"

class Room {
public:
    Room();
private:
    std::array<Room*, 4> adjRooms;  // right, down, left, up
    std::vector<Object*> objects;
};
#endif