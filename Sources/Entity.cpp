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
void Player::setCoordinate(int y, int x) {
    this->coordinate = std::make_pair(y, x);
}
// void Player::changeCoordinate(int _y, int _x) {
//     this->coordinate.first += _y;
//     this->coordinate.second += _x;
// }
const int Player::getCoordinateY() const {
    return this->coordinate.first;
}
const int Player::getCoordinateX() const {
    return this->coordinate.second;
}
const Room* Player::getRoom() const {
    return this->currentRoom;
}
void Player::playerMove(int direction, WINDOW* room) {
    // clear original position
    mvwaddch(room, this->coordinate.first, this->coordinate.second, ' ');
    // change player's position
    if (direction == 0403) {
        this->coordinate.first--;
        if (coordinate.first < 1) coordinate.first = 1;
    } else if (direction == 0402) {
        this->coordinate.first++;
        if (coordinate.first > Room::room_height - 2) coordinate.first = Room::room_height - 2;
    } else if (direction == 0404) {
        this->coordinate.second--;
        if (coordinate.second < 1) coordinate.second = 1;
    } else if (direction == 0405) {
        this->coordinate.second++;
        if (coordinate.second > Room::room_width - 2) coordinate.second = Room::room_width - 2;
    }
}