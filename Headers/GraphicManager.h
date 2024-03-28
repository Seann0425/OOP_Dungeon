#ifndef GRAPHIC
#define GRAPHIC
#include <ncurses/ncurses.h>

#include <string>
// base class for different scene
class Scene {
public:
    Scene();
protected:
    // info for player
    WINDOW* buttons;
    WINDOW* dialogues;
    WINDOW* mini_map;
};

// player walking in rooms
class ExploringScene : public Scene {};

// player fighting
class FightingScene : public Scene {};

// player having fun trading with NPCs
class TradingScrene : public Scene {};

// experimental function
void initGraphic();
const int displayMenu();
void endGraphic();
const int chooseDifficulty();
const std::string inputPlayerName();
const std::string readString();
#endif