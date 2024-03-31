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
    Monster(const std::string &, int, int, int, int);
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
    static const int &INIT_HEALTH;
    static const int &INIT_ATTACK;
    static const int &INIT_DEFENSE;
    const size_t EQUIPMENT_MAX = 10;
    const size_t CONSUMABLE_MAX = 3;
    Player();
    Player(const std::string &, int, int, int, int);
    static void health_init(int);
    static void attack_init(int);
    static void defense_init(int);
    void addEquipment(Equipment *);    // not implemented
    void addConsumable(Consumable *);  // not implemented
    void changeStatus(int);            // equipment for atk or def, not implemented
    void setRoom(Room *);
private:
    static int health_initializer;
    static int attack_initializer;
    static int defense_initializer;
    std::vector<Equipment *> inventory;
    std::vector<Consumable *> sack;
    Room *currentRoom;
    std::pair<int, int> poisoned;  // time / dps
};
#endif