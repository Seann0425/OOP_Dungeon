#include "../Headers/Item.h"

// definition of Item
Item::Item() = default;
Item::Item(std::string name, const std::string tag, int price) : Object(std::move(name), tag) {
    this->price = price;
}
void Item::setDescription(std::string _d) {
    this->description = std::move(_d);
}
const std::string Item::getDescription() const {
    return this->description;
}
// definition of equipment
Equipment::Equipment() : Item(), health(0), attack(0), defense(0) {
}
Equipment::Equipment(std::string name, int price, int health, int attack, int defense)
    : Item(std::move(name), "Equipment", price), health(health), attack(attack), defense(defense) {
}
int Equipment::getHealth() const {
    return this->health;
}
int Equipment::getAttack() const {
    return this->attack;
}
int Equipment::getDefense() const {
    return this->defense;
}

// definition of consumable
Consumable::Consumable() : Item() {
    this->health = 0;
    this->hunger = 0;
    this->thirsty = 0;
    this->poisonous = 0;
    this->antinode = 0;
}
Consumable::Consumable(std::string name, int price, int health, int hunger, int thirsty, int poisonous, bool antinode)
    : Item(name, "Consumable", price) {
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
