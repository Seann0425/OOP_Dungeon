#ifndef GRAPHIC
#define GRAPHIC
#include <ncurses/ncurses.h>

#include <string>
// experimental function
void initGraphic();
const int displayMenu();
void endGraphic();
const int chooseDifficulty();
const std::string inputPlayerName();
const std::string readString();
#endif