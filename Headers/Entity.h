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
    Monster(const std::string, int, int, int, int);
private:
};

class Player : public GameCharacter {
public:
    static const size_t EQUIPMENT_MAX;
    static const size_t CONSUMABLE_MAX;
    Player();
    Player(const std::string, int, int, int, int);
    void addEquipment(Equipment*);    // not implemented
    void addConsumable(Consumable*);  // not implemented
private:
    std::vector<Equipment*> inventory;
    std::vector<Consumable*> sack;
    // Room* currentRoom; room.h hasn't been implemented
    std::pair<int, int> poisoned;  // time / dps
};
#endif