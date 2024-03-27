#ifndef GC
#define GC
#include <iostream>

#include "Object.h"

class GameCharacter : public Object {
public:
    GameCharacter();
    GameCharacter(const std::string, const std::string, int, int, int, int);
    const bool checkDead() const;
    void takeDamage(int);
    void gotHealed(int);
    const int getMaxHealth() const;
    const int getCurrentHealth() const;
    const int getAttack() const;
    const int getDefense() const;
protected:
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
};

#endif