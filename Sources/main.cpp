#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Headers/Entity.h"
#include "../Headers/GraphicManager.h"
#include "../Headers/Item.h"

using JSON = nlohmann::json;

int main() {
    // read Settings.json file
    JSON Settings;
    std::ifstream jfile("../assets/Settings.json");
    jfile >> Settings;
    jfile.close();

    // initialize some game settings
    const size_t Player::EQUIPMENT_MAX = Settings.at("PLAYER_EQUIPMENT_MAX");

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