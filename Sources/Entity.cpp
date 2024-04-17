#include "../Headers/Entity.h"

Monster::Monster() {
    this->tag = "Monster";
}

Monster::Monster(const std::string name) {
    this->tag = "Monster";
    this->name = name;
}

Monster::Monster(const std::string name, int mxHp, int curHp, int atk, int def) : GameCharacter(name, "Monster", mxHp, curHp, atk, def) {
}

void Monster::deathAction(WINDOW *dialogues, std::array<bool, 3> &gameStatus) {
    int y, x;
    wprintw(dialogues, "You won the battle!");
    getyx(dialogues, y, x);
    wmove(dialogues, y + 1, 1);
    wprintw(dialogues, "Press any key to continue.");
    wgetch(dialogues);
    std::swap(gameStatus[0], gameStatus[1]);
}

NPC::NPC() {
    this->tag = "NPC";
}

NPC::NPC(const std::string name) {
    this->tag = "NPC";
    this->name = name;
}

void NPC::activated(WINDOW *shop, WINDOW *dialogues, Player *player) {
    mvwprintw(dialogues, 1, 1, "ERROR");
    mvwprintw(dialogues, 2, 1, "Press any key to continue.");
    wgetch(dialogues);
}

Player::Player() : GameCharacter(), sack(Player::CONSUMABLE_MAX) {
    this->tag = "Player";
    hasKey = false;
    hunger = Player::HUNGER_MAX;
    thirsty = Player::THIRSTY_MAX;
    this->sack[0] = std::make_pair(new Consumable("Bread", 0, 0, 1, 0, 0, false), 0);
    sack[0].first->setDescription("Restore 1 hunger.");
    this->sack[1] = std::make_pair(new Consumable("Steak", 0, 0, 3, 0, 0, false), 0);
    sack[1].first->setDescription("Restore 3 hunger.");
    this->sack[2] = std::make_pair(new Consumable("Cookie", 0, 0, 5, 0, 0, false), 0);
    sack[2].first->setDescription("Cookies restore 5 hunger <3");
    this->sack[3] = std::make_pair(new Consumable("Bottle of Water", 0, 0, 0, 1, 0, false), 0);
    sack[3].first->setDescription("Restore 1 thirsty.");
    this->sack[4] = std::make_pair(new Consumable("Milk", 0, 0, 0, 0, 0, true), 0);
    sack[4].first->setDescription("Clear debuffs.");
}

Player::Player(const std::string &name, int mxHP, int curHP, int atk, int def)
    : GameCharacter(name, "Player", mxHP, curHP, atk, def), sack(Player::CONSUMABLE_MAX) {
    hasKey = false;
    hunger = Player::HUNGER_MAX;
    thirsty = Player::THIRSTY_MAX;
    this->sack[0] = std::make_pair(new Consumable("Bread", 0, 0, 1, 0, 0, false), 0);
    sack[0].first->setDescription("Restore 1 hunger.");
    this->sack[1] = std::make_pair(new Consumable("Steak", 0, 0, 3, 0, 0, false), 0);
    sack[1].first->setDescription("Restore 3 hunger.");
    this->sack[2] = std::make_pair(new Consumable("Cookie", 0, 0, 5, 0, 0, false), 0);
    sack[2].first->setDescription("Cookies restore 5 hunger <3");
    this->sack[3] = std::make_pair(new Consumable("Bottle of Water", 0, 0, 0, 1, 0, false), 0);
    sack[3].first->setDescription("Restore 1 thirsty.");
    this->sack[4] = std::make_pair(new Consumable("Milk", 0, 0, 0, 0, 0, true), 0);
    sack[4].first->setDescription("Clear debuffs.");
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

Room *Player::getRoom() const {
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

void Player::addConsumable(size_t id, int amount) {
    this->sack[id].second += amount;
}

int Player::getHunger() const {
    return this->hunger;
}

int Player::getThirsty() const {
    return this->thirsty;
}

const std::vector<Equipment *> &Player::getInventory() const {
    return this->inventory;
}
const std::vector<std::pair<Consumable *, int>> &Player::getSack() const {
    return this->sack;
}

void Player::addEquipment(Equipment *equipment) {
    // TODO: exceed limit
    // check exist
    for (const auto &EQ : inventory) {
        if (EQ->getName() == equipment->getName()) return;
    }
    inventory.push_back(equipment);
    this->maxHealth += equipment->getHealth();
    this->currentHealth += equipment->getHealth();
    this->attack += equipment->getAttack();
    this->defense += equipment->getDefense();
}

Tester::Tester() = default;

Tester::Tester(const std::string name) : NPC(name) {
}

void Tester::activated(WINDOW *shop, WINDOW *dialogues, Player *player) {
    player->setKey(true);
    mvwprintw(dialogues, 1, 1, "Scripts are under developing.");
    mvwprintw(dialogues, 2, 1, "But you got a key from Tester somehow.");
    mvwprintw(dialogues, 3, 1, "Press any key to continue.");
    wgetch(dialogues);
    this->currentHealth = 0;
}

Helper::Helper() = default;
Helper::Helper(const std::string name) : NPC(name) {
}
void Helper::activated(WINDOW *shop, WINDOW *dialogues, Player *player) {
    mvwprintw(dialogues, 1, 1, "The Developer has no time to build this dungeon.");
    mvwprintw(dialogues, 2, 1, "So I'm here to give you every items you need to beat the game.");
    mvwprintw(dialogues, 3, 1, "And he's very sorry about this.");
    mvwprintw(dialogues, 4, 1, "Remember to check your inventory.");
    mvwprintw(dialogues, 5, 1, "Press any key to continue.");
    wgetch(dialogues);
    player->addConsumable(0, Helper::bread);
    player->addConsumable(1, Helper::steak);
    player->addConsumable(2, Helper::cookie);
    player->addConsumable(3, Helper::bottle_of_water);
    player->addConsumable(4, Helper::milk);
    Equipment *sword = new Equipment("OOP Sword", 0, 90, 999, 999);
    sword->setDescription("Overly OverPowered Sword.");
    player->addEquipment(sword);
}

Boss::Boss() = default;
Boss::Boss(const std::string name) : Monster(name) {
}
Boss::Boss(const std::string name, int mxHp, int curHp, int atk, int def) : Monster(name, mxHp, curHp, atk, def) {
}
void Boss::deathAction(WINDOW *dialogues, std::array<bool, 3> &gameStatus) {
    int y, x;
    wprintw(dialogues, "You won the battle!");
    getyx(dialogues, y, x);
    wmove(dialogues, y + 1, 1);
    wprintw(dialogues, "Press any key to continue.");
    wgetch(dialogues);
    gameStatus[1] = false;
}