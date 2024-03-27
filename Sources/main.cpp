#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Headers/Entity.h"
#include "../Headers/GraphicManager.h"
#include "../Headers/Item.h"

using JSON = nlohmann::json;

// initialize game settings
size_t Player::equipment_init = -1;
size_t Player::consumable_init = -1;
const size_t &Player::EQUIPMENT_MAX = Player::equipment_init;
const size_t &Player::CONSUMABLE_MAX = Player::consumable_init;

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
Menu:
    int option = displayMenu();
    switch (option) {
        // start
        case 0:
            // difficulty
            inputPlayerName();
            break;
        case 1:
            chooseDifficulty();
            goto Menu;
        // exit
        case 2:
            endGraphic();
            break;
        default:
            break;
    }
    return 0;
}