#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Headers/Dungeon.h"
#include "../Headers/Entity.h"
#include "../Headers/GameManager.h"
#include "../Headers/GraphicManager.h"
#include "../Headers/Item.h"

using JSON = nlohmann::json;

// initialize game settings
int Player::health_initializer = std::numeric_limits<int>::min();
int Player::attack_initializer = std::numeric_limits<int>::min();
int Player::defense_initializer = std::numeric_limits<int>::min();
const int &Player::INIT_HEALTH = Player::health_initializer;
const int &Player::INIT_ATTACK = Player::attack_initializer;
const int &Player::INIT_DEFENSE = Player::defense_initializer;

int main() {
    JSON Settings;
    std::ifstream jfile("../assets/Settings.json");
    jfile >> Settings;
    jfile.close();

    Player::health_init(Settings.at("PLAYER_INIT_HEALTH"));
    Player::attack_init(Settings.at("PLAYER_INIT_ATTACK"));
    Player::defense_init(Settings.at("PLAYER_INIT_DEFENSE"));

    initGraphic();
    Dungeon *dungeon = new Dungeon;
    dungeon->initGame();
    dungeon->generateObject();

    // display menu
    // runMenu() has called createPlayer()
    if (runMenu(dungeon) == true) return 0;
    Player *player = dungeon->getPlayer();

    // TODO: intepret story

    // exploring window
    ExploringScene exploring;
    exploring.drawMiniMap(dungeon);
    exploring.drawRoom(player);
    exploring.drawOptions();

    // fighting window
    FightingScene fighting;

    // trading window
    TradingScene trading;

    /* game loop
    assume scene can be overlapped after clear()
    while(exploring) {
        if (fighting) {}
        else if (trading) {}
    }
    */
    std::array<bool, 3> gameStatus{true, false, false}; // explore, fight, trade
    int input, option; // store keyboard input, some choice made by player
    int playerDmg, monsterDmg; // store battle situation
    Object *target = nullptr;
    keypad(stdscr, true);
    while (gameStatus[0]) {
        // casually exploring
        switch ((input = getch())) {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            option = player->playerMove(input, exploring.getRoom());
            if (option != -1) dungeon->changeRoom(option, exploring.getDialogues());
            break;
        case 27: // ESC
            option = exploring.inOptions();
            if (option == 0) return 0;
            else if (option == 1) {
                exploring.showInventory(player);
                break;
            } else if (option == 2) {
                exploring.showStatus(player);
                break;
            } else break;
        default:
            break;
        }

        // check if the game status needs to be changed
        target = checkEvent(player);
        if (target != nullptr) {
            if (target->getTag() == "Monster") {
                std::swap(gameStatus[0], gameStatus[1]);
            } else if (target->getTag() == "NPC") {
                std::swap(gameStatus[0], gameStatus[2]);
            }
        }

        // trigger trading
        if (gameStatus[2]) {
            NPC *npc = static_cast<NPC *>(target);
            exploring.clearScene();
            trading.drawVendor(npc);
            trading.drawShop();
            trading.drawOptions();
            trading.drawDialogues();
            trading.drawMiniMap(dungeon);
            while (gameStatus[2]) {
                switch ((input = getch())) {
                case 27: // ESC
                    option = trading.inOptions();
                    if (option == 0) return 0;
                    else break;
                case 120: // X
                    std::swap(gameStatus[0], gameStatus[2]);
                    break;
                case 10: // Enter
                    wclear(trading.getDialogues());
                    box(trading.getDialogues(), 0, 0);
                    wrefresh(trading.getDialogues());
                    npc->activated(trading.getShop(), trading.getDialogues(), player);
                    std::swap(gameStatus[0], gameStatus[2]);
                    break;
                default:
                    break;
                }
                trading.drawOptions();
            }
            trading.clearScene();
            // BUG: Run Time Error
            // if (npc->checkDead()) deleteObject(npc, player);
        }
        // trigger fighting
        if (gameStatus[1]) {
            Monster *monster = static_cast<Monster *>(target);
            exploring.clearScene();
            fighting.drawMonster(monster);
            fighting.drawOptions();
            fighting.drawDialogues(monster);
            fighting.drawMiniMap(dungeon);
            while (gameStatus[1]) {
                switch ((input = getch())) {
                case 27: // ESC
                    option = fighting.inOptions();
                    if (option == 0) return 0;
                    else if (option == 1) {
                        std::swap(gameStatus[0], gameStatus[1]);
                        break;
                    } else if (option == 2) {
                        fighting.showStatus(player);
                        break;
                    } else if (option == 3) {
                        // poorly implemented
                        playerDmg = (monster->getAttack() - player->getDefense() < 0) ? 0 : monster->getAttack() - player->getDefense();
                        monsterDmg = (player->getAttack() - monster->getDefense() < 0) ? 0 : player->getAttack() - monster->getDefense();
                        monster->takeDamage(monsterDmg);
                        player->takeDamage(playerDmg);
                        fighting.updateSituation(player, monster, playerDmg, monsterDmg);
                        break;
                    } else break;
                default:
                    break;
                }
                fighting.drawOptions();
            }
            fighting.clearScene();
        }
        exploring.drawMiniMap(dungeon);
        exploring.drawRoom(player);
        exploring.drawOptions();
        exploring.drawDialogues();
    }
    return 0;
}