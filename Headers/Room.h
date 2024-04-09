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
    static const int exit_Y = 7;
    static const int exit_X = 15;
    void setEco(Ecosystem);
    void setExit(size_t, size_t);
    const std::array<bool, 4> getExit() const;
private:
    std::vector<Object*> objects;
    Ecosystem eco;
    std::array<bool, 4> hasExit;  // up, down, left, right
};
#endif