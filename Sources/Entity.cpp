#include "../Headers/Entity.h"

Monster::Monster() : GameCharacter() {
    this->tag = "Monster";
}
Monster::Monster(const std::string& name, int mxHp, int curHp, int atk, int def) : GameCharacter(name, "Monster", mxHp, curHp, atk, def) {
}
Player::Player() : GameCharacter() {
    this->tag = "Player";
}
Player::Player(const std::string& name, int mxHP, int curHP, int atk, int def) : GameCharacter(name, "Player", mxHP, curHP, atk, def) {
}
void Player::health_init(int hp) {
    health_initializer = hp;
}
void Player::attack_init(int atk) {
    attack_initializer = atk;
}
void Player::defense_init(int def) {
    defense_initializer = def;
}
void Player::setRoom(Room* cur) {
    this->currentRoom = cur;
}