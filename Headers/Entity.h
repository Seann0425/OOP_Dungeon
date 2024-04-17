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
    Monster(const std::string);
    Monster(const std::string, int, int, int, int);
    virtual void deathAction(WINDOW *, std::array<bool, 3> &);
protected:
};

class NPC : public GameCharacter {
public:
    NPC();
    NPC(const std::string);
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
    static const size_t EQUIPMENT_MAX = 10;
    static const size_t CONSUMABLE_MAX = 5;
    static const int HUNGER_MAX = 10;
    static const int THIRSTY_MAX = 20;
    Player();
    Player(const std::string &, int, int, int, int);
    static void health_init(int);
    static void attack_init(int);
    static void defense_init(int);
    void addEquipment(Equipment *); // not implemented
    void addConsumable(size_t, int); // not implemented
    void changeStatus(int); // equipment for atk or def, not implemented
    void setRoom(Room *);
    void setCoordinate(int, int);
    void changeCoordinate(int, int);
    const int getCoordinateY() const;
    const int getCoordinateX() const;
    Room *getRoom() const;
    int playerMove(int, WINDOW *);
    bool checkKey() const;
    void setKey(bool);
    int getHunger() const;
    int getThirsty() const;
    const std::vector<Equipment *> &getInventory() const;
    const std::vector<std::pair<Consumable *, int>> &getSack() const;
private:
    static int health_initializer;
    static int attack_initializer;
    static int defense_initializer;
    int hunger;
    int thirsty;
    std::vector<Equipment *> inventory;
    std::vector<std::pair<Consumable *, int>> sack;
    Room *currentRoom;
    std::pair<int, int> poisoned; // time / damage
    std::pair<int, int> coordinate; // y, x
    bool hasKey;
};

class Tester : public NPC {
public:
    Tester();
    Tester(const std::string);
    void activated(WINDOW *, WINDOW *, Player *);
};

class Helper : public NPC {
public:
    static const int bread = 5;
    static const int steak = 3;
    static const int cookie = 1;
    static const int bottle_of_water = 10;
    static const int milk = 1;
    Helper();
    Helper(const std::string);
    void activated(WINDOW *, WINDOW *, Player *);
};

class Boss : public Monster {
public:
    Boss();
    Boss(const std::string);
    Boss(const std::string, int, int, int, int);
    void deathAction(WINDOW *, std::array<bool, 3> &);
};
#endif