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
    static const size_t &EQUIPMENT_MAX;
    static const size_t &CONSUMABLE_MAX;
    Player();
    Player(const std::string, int, int, int, int);
    static void EQUIPMENT_LIMIT(size_t);
    static void CONSUMABLE_LIMIT(size_t);
    void addEquipment(Equipment *);    // not implemented
    void addConsumable(Consumable *);  // not implemented
private:
    static size_t equipment_init;
    static size_t consumable_init;
    std::vector<Equipment *> inventory;
    std::vector<Consumable *> sack;
    // Room* currentRoom; room.h hasn't been implemented
    std::pair<int, int> poisoned;  // time / dps
};
#endif