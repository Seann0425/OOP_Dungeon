#include "../Headers/Dungeon.h"

Dungeon::Dungeon() : rooms(3, std::vector<Room *>(3)){
    // generate rooms
    for (size_t y = 0; y < 3; y++) { // FIXME: maybe there are a more elegant way?
        for (size_t x = 0; x < 3; x++) {
            rooms[y][x] = new Room();
        }
    }

    // set init room, boss room and key room(?
    // TODO: make it random
    boss_room = rooms[0][2];
    key_room = rooms[0][0];
    init_room = rooms[2][0];
    current_room_idx = std::make_pair(2, 0);

    // set exit
    for (size_t y = 0; y < 3; y++) {
        for (size_t x = 0; x < 3; x++) {
            rooms[y][x]->setExit(y, x);
        }
    }
}

void Dungeon::initGame() {
    // trivial random number generator to set ecosystem
    std::default_random_engine generator(time(NULL));
    std::uniform_int_distribution<int> unif(0, 3);
    for (auto &room_seq : rooms) {
        for (auto &room : room_seq) {
            room->setEco(static_cast<Ecosystem>(unif(generator)));
        }
    }
}

void Dungeon::createPlayer(const std::string &name) {
    this->player = new Player(name, Player::INIT_HEALTH, Player::INIT_HEALTH, Player::INIT_ATTACK, Player::INIT_DEFENSE);
    player->setRoom(init_room);
    player->setCoordinate(7, 15);
}

const std::pair<int, int> Dungeon::getCurrentIndex() const {
    return std::make_pair(current_room_idx.first, current_room_idx.second);
}

Player *Dungeon::getPlayer() const {
    return player;
}
