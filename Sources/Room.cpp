#include "../Headers/Room.h"

Room::Room() {
}

void Room::setEco(Ecosystem _e) {
    this->eco = _e;
}

// BUG CANDIDATE
void Room::setExit(size_t y, size_t x) {
    // up, down, left, right
    hasExit[0] = (y > 0);
    hasExit[1] = (y < 2);
    hasExit[2] = (x > 0);
    hasExit[3] = (x < 2);
}

const std::array<bool, 4> Room::getExit() const {
    return this->hasExit;
}