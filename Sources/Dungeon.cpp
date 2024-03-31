#include "../Headers/Dungeon.h"

Dungeon::Dungeon() {
    // generate rooms
    rooms.resize(3, std::vector<Room *>(3, new Room));
    // set init room, boss room and key room(?
    // TODO: make it random
    boss_room = rooms[0][2];
    key_room = rooms[1][1];
    init_room = rooms[2][0];
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
}