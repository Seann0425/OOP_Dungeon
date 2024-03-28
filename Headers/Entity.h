#ifndef ENTITY
#define ENTITY

#include <unordered_map>
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

class NPC : public GameCharacter {
public:
    NPC();
    void listCommodity();
    // take commodity id as parameter and return successful or not
    bool sellItem(int);
    // return successful or not since some items might not be sellable
    bool buyItem();
private:
    std::unordered_map<std::string, std::string> scripts;  // not sure if vector is better
    std::vector<std::pair<Item *, int>> commodity;         // item, amount
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
    void changeStatus(int);            // equipment for atk or def, not implemented
private:
    static size_t equipment_init;
    static size_t consumable_init;
    std::vector<Equipment *> inventory;
    std::vector<Consumable *> sack;
    Room *currentRoom;
    std::pair<int, int> poisoned;  // time / dps
};
#endif