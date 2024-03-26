#ifndef GC
#define GC
#include <bits/stdc++.h>

#include "Object.h"
using namespace std;

class GameCharacter : public Object {
public:
    GameCharacter();
    GameCharacter(string, string, int, int, int, int);
    const bool checkDead() const;
    void takeDamage(int);
    void gotHealed(int);
    const int getMaxHealth() const;
    const int getCurrentHealth() const;
    const int getAttack() const;
    const int getDefense() const;
private:
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
};

#endif