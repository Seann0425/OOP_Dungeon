#ifndef DUNGEON
#define DUNGEON

#include <algorithm>
#include <ctime>
#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <random>
#include <utility>
#include <vector>

#include "Entity.h"
#include "Room.h"

class Dungeon {
public:
    // generate rooms, set the adjacent relationship between rooms
    Dungeon();
    /**
     * @brief Initialize some settings for the dungeon
     */
    void initGame();
    /**
     * @brief Create a Player object and put the player into the starting room
     * @param name Player's name
     */
    void createPlayer(const std::string &name);
    Player *getPlayer() const;
    const std::pair<int, int> getCurrentIndex() const;
    void changeRoom(int, WINDOW *);
    void generateObject();
private:
    Player *player;
    std::vector<std::vector<Room *>> rooms; // 3 * 3
    Room *boss_room;
    Room *key_room;
    Room *init_room;
    std::pair<size_t, size_t> current_room_idx;
};

#endif