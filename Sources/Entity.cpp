#include "../Headers/Entity.h"

Monster::Monster() {
    this->tag = "Monster";
}

Monster::Monster(const std::string &name, int mxHp, int curHp, int atk, int def) : GameCharacter(name, "Monster", mxHp, curHp, atk, def) {
}

NPC::NPC() {
    this->tag = "NPC";
}

NPC::NPC(const std::string &name) {
    this->tag = "NPC";
    this->name = name;
}

void NPC::activated(WINDOW *shop, WINDOW *dialogues, Player *player) {
    mvwprintw(dialogues, 1, 1, "ERROR");
    mvwprintw(dialogues, 2, 1, "Press any key to continue.");
    wgetch(dialogues);
}

Player::Player() : GameCharacter() {
    this->tag = "Player";
    hasKey = false;
}

Player::Player(const std::string &name, int mxHP, int curHP, int atk, int def) : GameCharacter(name, "Player", mxHP, curHP, atk, def) {
    hasKey = false;
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

void Player::setRoom(Room *cur) {
    this->currentRoom = cur;
}

void Player::setCoordinate(int y, int x) {
    this->coordinate = std::make_pair(y, x);
}

void Player::changeCoordinate(int _y, int _x) {
    this->coordinate.first += _y;
    this->coordinate.second += _x;
}

const int Player::getCoordinateY() const {
    return this->coordinate.first;
}

const int Player::getCoordinateX() const {
    return this->coordinate.second;
}

const Room *Player::getRoom() const {
    return this->currentRoom;
}

int Player::playerMove(int direction, WINDOW *room) {
    // return {0, 1, 2, 3} = {up, down, left, right} means moving to which room
    int newRoom = -1; // -1 => not changed
    //  clear original position
    mvwaddch(room, this->coordinate.first, this->coordinate.second, ' ');
    // change player's position
    if (direction == 0403) {
        this->coordinate.first--;
    } else if (direction == 0402) {
        this->coordinate.first++;
    } else if (direction == 0404) {
        this->coordinate.second--;
    } else if (direction == 0405) {
        this->coordinate.second++;
    }
    std::array<bool, 4> hasExit = currentRoom->getExit();
    if (hasExit[0] && coordinate.first == 0 && coordinate.second == Room::exit_X) {
        newRoom = 0;
        coordinate.first = Room::room_height - 2;
    } else if (hasExit[1] && coordinate.first == Room::room_height - 1 && coordinate.second == Room::exit_X) {
        newRoom = 1;
        coordinate.first = 1;
    } else if (hasExit[2] && coordinate.first == Room::exit_Y && coordinate.second == 0) {
        newRoom = 2;
        coordinate.second = Room::room_width - 2;
    } else if (hasExit[3] && coordinate.first == Room::exit_Y && coordinate.second == Room::room_width - 1) {
        newRoom = 3;
        coordinate.second = 1;
    }
    if (newRoom == -1) {
        if (coordinate.first < 1) coordinate.first = 1;
        if (coordinate.first > Room::room_height - 2) coordinate.first = Room::room_height - 2;
        if (coordinate.second < 1) coordinate.second = 1;
        if (coordinate.second > Room::room_width - 2) coordinate.second = Room::room_width - 2;
    }
    return newRoom;
}

bool Player::checkKey() const {
    return this->hasKey;
}

void Player::setKey(bool has) {
    this->hasKey = has;
}

Tester::Tester() = default;

Tester::Tester(const std::string &name) : NPC(name) {
}

void Tester::activated(WINDOW *shop, WINDOW *dialogues, Player *player) {
    player->setKey(true);
    mvwprintw(dialogues, 1, 1, "Scripts are under developing.");
    mvwprintw(dialogues, 2, 1, "But you got a key from Tester somehow.");
    mvwprintw(dialogues, 3, 1, "Press any key to continue.");
    wgetch(dialogues);
}