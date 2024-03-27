#include <iostream>

#include "../Headers/GraphicManager.h"
#include "../Headers/Item.h"

int main() {
    // game menu
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