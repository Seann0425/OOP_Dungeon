#include "../Headers/Dungeon.h"

Dungeon::Dungeon() : rooms(3, std::vector<Room *>(3)) {
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
            rooms[y][x]->setExit(y, x, rooms[y][x] == boss_room);
        }
    }
}

void Dungeon::initGame() {
    // trivial random number generator to set ecosystem
    std::random_device generator;
    std::vector<int> ecos{0, 0, 0, 1, 1, 1, 1, 2, 2};
    std::shuffle(ecos.begin(), ecos.end(), generator);
    size_t idx = 0;
    for (auto &room_seq : rooms) {
        for (auto &room : room_seq) {
            room->setEco(static_cast<Ecosystem>(ecos[idx++]));
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

void Dungeon::changeRoom(int direction, WINDOW *dialogues) {
    // {0, 1, 2, 3} -> {up, down, left, right}
    std::pair<size_t, size_t> &roomIdx = current_room_idx;
    auto [originY, originX] = roomIdx;
    switch (direction) {
    case 0:
        roomIdx.first--;
        break;
    case 1:
        roomIdx.first++;
        break;
    case 2:
        roomIdx.second--;
        break;
    case 3:
        roomIdx.second++;
        break;
    default:
        break;
    }
    if (boss_room != rooms[roomIdx.first][roomIdx.second]) {
        player->setRoom(rooms[roomIdx.first][roomIdx.second]);
    } else {
        wclear(dialogues);
        box(dialogues, 0, 0);
        if (player->checkKey()) {
            mvwprintw(dialogues, 1, 1, "You opened the door with the key!");
            mvwprintw(dialogues, 2, 1, "Enjoy the boss fight!!");
            player->setKey(false);
            player->setRoom(rooms[roomIdx.first][roomIdx.second]);
        } else {
            mvwprintw(dialogues, 1, 1, "The door is locked...");
            roomIdx.first = originY, roomIdx.second = originX;
            if (player->getCoordinateY() == Room::exit_Y && player->getCoordinateX() == 1) {
                // from left door
                player->setCoordinate(player->getCoordinateY(), Room::room_width - 2);
            } else if (player->getCoordinateY() == Room::room_height - 2 && player->getCoordinateX() == Room::exit_X) {
                // from down door
                player->setCoordinate(1, player->getCoordinateX());
            }
        }
        wrefresh(dialogues);
    }
}

void Dungeon::generateObject() {
    // TODO: make it random (Fisher-Yates Shuffle Algorithm)
    // a NPC that will give you the key to the boss room
    Tester *keyHolder = new Tester("Tester");
    key_room->addObject(keyHolder, 7, 15);
    // a NPC that help the developer finish his homework before deadline
    Helper *helper = new Helper("Helper");
    init_room->addObject(helper, 13, 1);
    // boss, probably the only monster in the game
    Boss *boss = new Boss("Deadline", 50, 50, 5, 5);
    boss_room->addObject(boss, 7, 15);
    // cute kitten
    Cat *kitten = new Cat("Kitten");
    rooms[1][1]->addObject(kitten, 7, 15);
    // developer himself
    Tako *tako = new Tako("Tako");
    rooms[2][2]->addObject(tako, 13, 28);
    // just a temporary monster
    Monster *monster = new Monster("Lab", 20, 20, 3, 3);
    rooms[1][0]->addObject(monster, 3, 6);
}
