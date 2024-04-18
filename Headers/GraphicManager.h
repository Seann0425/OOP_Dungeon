#ifndef GRAPHIC
#define GRAPHIC
#include <ncurses/ncurses.h>

#include <string>

#include "Dungeon.h"

#define COLOR_TAKO 8
#define COLOR_PINK 9

#define TAKO_BACKGROUND 1
#define REVERSE_PAIR 2
#define TAKO_PAIR 3
#define RED_PAIR 4
#define RED_BACKGROUND 5
#define GREEN_PAIR 6
#define YELLOW_PAIR 7
#define PINK_PAIR 8

// base class for different scene
class Scene {
public:
    Scene();
    void drawMiniMap(Dungeon *);
    void drawOptions();
    void showStatus(const Player *);
    void showInventory(const Player *);
    int inOptions();
    WINDOW *getDialogues();
    virtual void clearScene() = 0;
    virtual void drawDialogues();
protected:
    // info for player
    WINDOW *buttons;
    WINDOW *dialogues;
    WINDOW *mini_map;
    std::vector<std::string> optionButtons;
};

// player walking in rooms
class ExploringScene : public Scene {
public:
    ExploringScene();
    void drawRoom(const Player *);
    WINDOW *getRoom();
    void clearScene();
private:
    WINDOW *room;
};

// player fighting
class FightingScene : public Scene {
public:
    FightingScene();
    void clearScene();
    void drawMonster(Monster *);
    void drawDialogues(Monster *);
    void updateSituation(Player *, Monster *, int, int);
private:
    WINDOW *battle;
};

// player having fun trading with NPCs
class TradingScene : public Scene {
public:
    TradingScene();
    void drawVendor(const NPC *);
    void drawShop();
    WINDOW *getVendor();
    WINDOW *getShop();
    void clearScene();
    void drawDialogues();
private:
    WINDOW *vendor; // left side
    WINDOW *shop; // right side
};

// experimental function
void initGraphic();
const int displayMenu();
void endGraphic();
const int chooseDifficulty();
const std::string inputPlayerName();
const std::string readString();
void displayEndAnimation();
#endif