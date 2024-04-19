#ifndef GC
#define GC
#include <iostream>

#include "Object.h"

class GameCharacter : public Object {
public:
    GameCharacter();
    GameCharacter(const std::string, const std::string, int, int, int, int);
    bool checkDead() const;
    void takeDamage(int);
    void gotHealed(int);
    int getMaxHealth() const;
    int getCurrentHealth() const;
    int getAttack() const;
    int getDefense() const;
    const char *const getImagePath() const;
    int getImageY() const;
    int getImageX() const;
protected:
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
    const char *image = nullptr;
    int imageY;
    int imageX;
};

#endif