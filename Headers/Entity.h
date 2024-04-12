#ifndef ENTITY
#define ENTITY

#include <ncurses/ncurses.h>

#include <unordered_map>
#include <utility>
#include <vector>

#include "GameCharacter.h"
#include "Item.h"
#include "Room.h"

class Player;

class Monster : public GameCharacter {
public:
    Monster();
    Monster(const std::string &, int, int, int, int);
private:
};

class NPC : public GameCharacter {
public:
    NPC();
    NPC(const std::string &);
    void listCommodity();
    // take commodity id as parameter and return successful or not
    bool sellItem(int);
    // return successful or not since some items might not be sellable
    bool buyItem();
    virtual void activated(WINDOW *, WINDOW *, Player *);
private:
    std::unordered_map<std::string, std::string> scripts; // not sure if vector is better
    std::vector<std::pair<Item *, int>> commodity; // item, amount
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
    void addEquipment(Equipment *); // not implemented
    void addConsumable(Consumable *); // not implemented
    void changeStatus(int); // equipment for atk or def, not implemented
    void setRoom(Room *);
    void setCoordinate(int, int);
    void changeCoordinate(int, int);
    const int getCoordinateY() const;
    const int getCoordinateX() const;
    const Room *getRoom() const;
    int playerMove(int, WINDOW *);
    bool checkKey() const;
    void setKey(bool);
private:
    static int health_initializer;
    static int attack_initializer;
    static int defense_initializer;
    std::vector<Equipment *> inventory;
    std::vector<Consumable *> sack;
    Room *currentRoom;
    std::pair<int, int> poisoned; // time / dps
    std::pair<int, int> coordinate; // y, x
    bool hasKey;
};

class Tester : public NPC {
public:
    Tester();
    Tester(const std::string &);
    void activated(WINDOW *, WINDOW *, Player *);
};
#endif