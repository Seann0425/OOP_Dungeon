#include "../Headers/Entity.h"

Monster::Monster() : GameCharacter() {
    this->tag = "Monster";
}
Monster::Monster(std::string name, int mxHp, int curHp, int atk, int def) : GameCharacter(name, "Monster", mxHp, curHp, atk, def) {
}