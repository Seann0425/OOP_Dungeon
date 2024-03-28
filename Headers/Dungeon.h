#ifndef DUNGEON
#define DUNGEON

#include <vector>

#include "Entity.h"
#include "Room.h"

class Dungeon {
public:
    Dungeon();
    void startGame();
    void createPlayer();
    void createMap();
    void runDungeon();
private:
    Player* player;
    std::vector<std::vector<Room*>> rooms;
};

#endif