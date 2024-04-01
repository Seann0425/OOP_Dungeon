#ifndef ROOM
#define ROOM

#include <array>
#include <vector>

#include "Object.h"

enum Ecosystem { Desert, Forest, Swamp };

class Room {
public:
    Room();
    static const int room_height = 15;
    static const int room_width = 30;
    void setEco(Ecosystem);
private:
    std::vector<Object*> objects;
    Ecosystem eco;
};
#endif