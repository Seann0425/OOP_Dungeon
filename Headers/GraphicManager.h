#ifndef GRAPHIC
#define GRAPHIC
#include <ncurses/ncurses.h>

#include <string>

#include "Dungeon.h"

// base class for different scene
class Scene {
public:
    Scene();
    void drawMiniMap(Dungeon*);
protected:
    // info for player
    WINDOW* buttons;
    WINDOW* dialogues;
    WINDOW* mini_map;
};

// player walking in rooms
class ExploringScene : public Scene {
public:
    ExploringScene();
private:
    WINDOW* gamePlay;
};

// player fighting
class FightingScene : public Scene {
public:
    FightingScene();
private:
    WINDOW* battle;
};

// player having fun trading with NPCs
class TradingScene : public Scene {
public:
    TradingScene();
private:
    WINDOW* vendor;  // left side
    WINDOW* shop;    // right side
};

// experimental function
void initGraphic();
const int displayMenu();
void endGraphic();
const int chooseDifficulty();
const std::string inputPlayerName();
const std::string readString();
#endif