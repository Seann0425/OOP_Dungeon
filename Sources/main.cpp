#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Headers/Entity.h"
#include "../Headers/GraphicManager.h"
#include "../Headers/Item.h"

using JSON = nlohmann::json;

// initialize game settings
size_t Player::equipment_init = std::numeric_limits<size_t>::max();
size_t Player::consumable_init = std::numeric_limits<size_t>::max();
const size_t &Player::EQUIPMENT_MAX = Player::equipment_init;
const size_t &Player::CONSUMABLE_MAX = Player::consumable_init;

// game menu function, return true if exit
bool runMenu() {
    int option = 1;
    while (option == 1) {
        option = displayMenu();
        switch (option) {
            // start
            case 0:
                inputPlayerName();
                break;
            case 1:
                chooseDifficulty();
                break;
            case 2:
                endGraphic();
                return true;
            default:
                break;
        }
    }
    return false;
}

int main() {
    // read Settings.json file
    JSON Settings;
    std::ifstream jfile("../assets/Settings.json");
    jfile >> Settings;
    jfile.close();

    // initialize game settings
    Player::EQUIPMENT_LIMIT(Settings.at("PLAYER_EQUIPMENT_MAX"));
    Player::CONSUMABLE_LIMIT(Settings.at("PLAYER_CONSUMABLE_MAX"));

    // initialize ncurses and open game menu
    initGraphic();

    // display menu
    if (runMenu() == true) return 0;

    // TODO: intepret story

    // TODO: init ExploringScene
    ExploringScene exploring;

    getch();
    return 0;
}