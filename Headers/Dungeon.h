#ifndef DUNGEON
#define DUNGEON

#include <ctime>
#include <random>
#include <vector>

#include "Entity.h"
#include "Room.h"

class Dungeon {
public:
    // generate rooms, set the adjacent relationship between rooms
    Dungeon();
    // generate player, put player into the starting room
    // set each room its utility, such as boss room, different eco
    // or the room that contains the key to the boss room
    void initGame();
    void createPlayer(const std::string&);
    void createMap();
    void runDungeon();
private:
    Player* player;
    std::vector<std::vector<Room*>> rooms;  // 3 * 3
    Room* boss_room;
    Room* key_room;
    Room* init_room;
};

#endif