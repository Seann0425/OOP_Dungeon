#include "../Headers/GameCharacter.h"

GameCharacter::GameCharacter() {
    maxHealth = 1;
    currentHealth = 1;
}
GameCharacter::GameCharacter(const std::string n, const std::string tag, int mxHP, int curHP, int atk, int def) : Object(n, tag) {
    this->maxHealth = mxHP;
    this->currentHealth = curHP;
    this->attack = atk;
    this->defense = def;
}
void GameCharacter::takeDamage(int dmg) {
    if (dmg > currentHealth) {
        currentHealth = 0;
        return;
    }
    currentHealth -= dmg;
}
void GameCharacter::gotHealed(int amount) {
    if (currentHealth + amount > maxHealth) {
        currentHealth = maxHealth;
        return;
    }
    currentHealth += amount;
}
bool GameCharacter::checkDead() const {
    return currentHealth == 0;
}
int GameCharacter::getMaxHealth() const {
    return this->maxHealth;
}
int GameCharacter::getCurrentHealth() const {
    return this->currentHealth;
}
int GameCharacter::getAttack() const {
    return this->attack;
}
int GameCharacter::getDefense() const {
    return this->defense;
}

const char *const GameCharacter::getImagePath() const {
    return image;
}

int GameCharacter::getImageY() const {
    return imageY;
}
int GameCharacter::getImageX() const {
    return imageX;
}