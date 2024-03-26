#include "../Headers/GameCharacter.h"

GameCharacter::GameCharacter() {
}
GameCharacter::GameCharacter(string n, string tag, int mxHP, int curHP, int atk, int def) : Object(n, tag) {
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
const bool GameCharacter::checkDead() const {
    return currentHealth == 0;
}
const int GameCharacter::getMaxHealth() const {
    return this->maxHealth;
}
const int GameCharacter::getCurrentHealth() const {
    return this->currentHealth;
}
const int GameCharacter::getAttack() const {
    return this->attack;
}
const int GameCharacter::getDefense() const {
    return this->defense;
}