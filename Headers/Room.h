#ifndef ROOM
#define ROOM

#include <array>
#include <utility>
#include <vector>

#include "GameCharacter.h"

enum Ecosystem { Desert, Forest, Swamp };

class Room {
public:
    Room();
    static const int room_height = 15;
    static const int room_width = 30;
    static const int exit_Y = 7;
    static const int exit_X = 15;
    void setEco(Ecosystem);
    void setExit(size_t, size_t, bool);
    const std::array<bool, 4> getExit() const;
    void addObject(Object *, int, int);
    void removeObject(Object *);
    const std::vector<Object *> &getObjects() const;
    const std::vector<std::pair<int, int>> &getLocs() const;
    Ecosystem getEco() const;
private:
    std::vector<Object *> objects;
    std::vector<std::pair<int, int>> locations;
    Ecosystem eco;
    std::array<bool, 4> hasExit; // up, down, left, right
};
#endif