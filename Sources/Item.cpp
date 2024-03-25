#include "../Headers/Item.h"

// definition of equipment
Equipment::Equipment() : Object(), health(0), attack(0), defense(0) {
}
Equipment::Equipment(string name, int health, int attack, int defense) : Object(name, "Equipment"), health(health), attack(attack), defense(defense) {
}
const int Equipment::getHealth() const {
    return this->health;
}
const int Equipment::getAttack() const {
    return this->attack;
}
const int Equipment::getDefense() const {
    return this->defense;
}

// definition of consumable
Consumable::Consumable() : Object() {
    this->health = 0;
    this->hunger = 0;
    this->thirsty = 0;
    this->poisonous = 0;
    this->antinode = 0;
}
Consumable::Consumable(string name, int health, int hunger, int thirsty, int poisonous, bool antinode) : Object(name, "Consumable") {
    this->health = health;
    this->hunger = hunger;
    this->thirsty = thirsty;
    this->poisonous = poisonous;
    this->antinode = antinode;
}
const int Consumable::getHealth() const {
    return this->health;
}
const int Consumable::getHunger() const {
    return this->hunger;
}
const int Consumable::getThirsty() const {
    return this->thirsty;
}
const int Consumable::getPoisonous() const {
    return this->poisonous;
}
const bool Consumable::isAntinode() const {
    return this->antinode;
}
