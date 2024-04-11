#include "../Headers/GameManager.h"

// game menu function, return true if exit
bool runMenu(Dungeon *dungeon) {
    int option = 1;
    std::string name;
    while (option == 1) {
        option = displayMenu();
        switch (option) {
        // start
        case 0:
            name = inputPlayerName();
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
    dungeon->createPlayer(name);
    return false;
}