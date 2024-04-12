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
            if (option != -1) dungeon->changeRoom(option);
            break;
        case 27: // ESC
            option = exploring.inOptions();
            if (option == 0) return 0;
            else if (option == 1) {
                // TODO: show status in dialogue
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

        // trigger fighting

        // trigger trading
        if (gameStatus[2]) {
            exploring.clearScene();
            trading.drawVendor(static_cast<NPC *>(target));
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
                default:
                    break;
                }
                trading.drawOptions();
            }
        }

        exploring.drawMiniMap(dungeon);
        exploring.drawRoom(player);
        exploring.drawOptions();
    }
    return 0;
}