#include "../Headers/GameManager.h"

// game menu function, return true if exit
bool runMenu(Dungeon *dungeon) {
    int option = 1;
    std::string name;
    while (option == 1) {
        option = displayMenu();
        switch (option) {
        // start
        case 0:
            name = inputPlayerName();
            break;
        case 1:
            chooseDifficulty();
            break;
        case 2:
            endGraphic();
            return true;
        default:
            break;
        }
    }
    dungeon->createPlayer(name);
    return false;
}

Object *checkEvent(Player *player) {
    const std::vector<Object *> &objects = player->getRoom()->getObjects();
    const std::vector<std::pair<int, int>> &locations = player->getRoom()->getLocs();
    const auto N = objects.size();
    const auto y = player->getCoordinateY();
    const auto x = player->getCoordinateX();
    for (size_t i = 0; i < N; i++) {
        if (locations[i].first == y && locations[i].second == x) {
            return objects[i];
        }
    }
    return nullptr;
}

void deleteObject(Object *object, Player *player) {
    player->getRoom()->removeObject(object);
}