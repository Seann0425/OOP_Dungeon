#ifndef ENTITY
#define ENTITY

#include <utility>
#include <vector>

#include "GameCharacter.h"
#include "Item.h"
#include "Room.h"

class Monster : public GameCharacter {
public:
    Monster();
    Monster(std::string, int, int, int, int);
private:
};

class Player : public GameCharacter {
public:
    Player();
    Player(std::string, int, int, int, int);
private:
    std::vector<Equipment*> inventory;
    std::vector<Consumable*> sack;
    // Room* currentRoom;
    std::pair<int, int> poisoned;
};
#endif