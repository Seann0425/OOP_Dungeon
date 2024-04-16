#include "../Headers/Room.h"

Room::Room() = default;

void Room::setEco(Ecosystem _e) {
    this->eco = _e;
}

void Room::setExit(size_t y, size_t x, bool isBoosRoom) {
    if (isBoosRoom) {
        hasExit = {};
        return;
    }
    // up, down, left, right
    this->hasExit[0] = (y > 0);
    this->hasExit[1] = (y < 2);
    this->hasExit[2] = (x > 0);
    this->hasExit[3] = (x < 2);
}

const std::array<bool, 4> Room::getExit() const {
    return this->hasExit;
}

void Room::addObject(Object *object, int y, int x) {
    objects.push_back(object);
    locations.emplace_back(y, x);
}

void Room::removeObject(Object *object) {
    int i = 0;
    for (auto itr = objects.begin(); itr != objects.end(); itr++, i++) {
        if (*itr == object) {
            objects.erase(itr);
            break;
        }
    }
    locations.erase(locations.begin() + i);
    delete object;
}

const std::vector<Object *> &Room::getObjects() const {
    return this->objects;
}

const std::vector<std::pair<int, int>> &Room::getLocs() const {
    return this->locations;
}