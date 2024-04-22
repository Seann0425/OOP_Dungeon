#include "../Headers/GraphicManager.h"

#include <array>
#include <iostream>
#include <string>

using namespace std::literals::string_literals;

inline void newLine(WINDOW *win, int y, int x) {
    getyx(win, y, x);
    wmove(win, y + 1, 1);
}

// Scene Initialize
Scene::Scene() {
    std::string test = "this is a test"s;
    int Y, X;
    getmaxyx(stdscr, Y, X);
    buttons = newwin(Y / 2, Y / 2, Y / 2, 0);
    dialogues = newwin(Y / 2, X - Y * 3 / 2, Y / 2, Y / 2);
    mini_map = newwin(Y / 2, Y, Y / 2, X - Y);
    refresh();
    box(dialogues, 0, 0);
    wrefresh(dialogues);
    keypad(dialogues, true);
    keypad(buttons, true);
}

void Scene::drawMiniMap(Dungeon *dungeon) {
    wclear(mini_map);
    box(mini_map, 0, 0);
    int y, x;
    int Y, X;
    getmaxyx(stdscr, Y, X);
    getmaxyx(mini_map, y, x);
    wmove(mini_map, y / 3, 1);
    whline(mini_map, ACS_HLINE, x - 2);
    wmove(mini_map, y * 2 / 3, 1);
    whline(mini_map, ACS_HLINE, x - 2);
    wmove(mini_map, 1, x / 3);
    wvline(mini_map, ACS_VLINE, y - 2);
    wmove(mini_map, 1, x * 2 / 3);
    wvline(mini_map, ACS_VLINE, y - 2);
    WINDOW *cur_area = subwin(mini_map, y / 3 - 2, x / 3 - 1, Y / 2 + y / 3 * dungeon->getCurrentIndex().first + 1,
                              X - Y + (x / 3) * dungeon->getCurrentIndex().second + 1);
    wrefresh(mini_map);
    touchwin(mini_map);
    wclear(cur_area);
    wbkgd(cur_area, COLOR_PAIR(REVERSE_PAIR));
    wrefresh(cur_area);
    delwin(cur_area);
}

void Scene::drawOptions() {
    box(buttons, 0, 0);
    for (size_t i = 0; i < optionButtons.size(); i++) {
        mvwprintw(buttons, 1 + 2 * static_cast<int>(optionButtons.size() - 1 - i), 1, optionButtons[i].c_str());
    }
    wrefresh(buttons);
}

void Scene::showStatus(const Player *player) {
    // currently show only HP, ATK, DEF, hunger, thirsty
    int y, x;
    wclear(dialogues);
    box(dialogues, 0, 0);
    wmove(dialogues, 1, 1);
    wprintw(dialogues, "Player Name: %s", player->getName().c_str());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Health: %d/%d", player->getCurrentHealth(), player->getMaxHealth());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Attack: %d", player->getAttack());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Defense: %d", player->getDefense());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Hunger: %d", player->getHunger());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Thirsty: %d", player->getThirsty());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Poisoned: ");
    if (player->getPoisoned().first == 0) wprintw(dialogues, "None");
    else wprintw(dialogues, "%d Steps, %d DPS", player->getPoisoned().first, player->getPoisoned().second);
    newLine(dialogues, y, x);
    wprintw(dialogues, "Dehydration: ");
    if (player->getThirsty() != 0) wprintw(dialogues, "None");
    else wprintw(dialogues, "Dehydrated. Moving slowly.");
    newLine(dialogues, y, x);
    wprintw(dialogues, "Key: %d", player->checkKey());
    wrefresh(dialogues);
}

void Scene::showInventory(const Player *player) {
    int y, x;
    wclear(dialogues);
    box(dialogues, 0, 0);
    wmove(dialogues, 1, 1);
    if (player->getInventory().empty()) {
        wprintw(dialogues, "No equipment in the inventory.");
    } else {
        for (const auto &equipment : player->getInventory()) {
            wprintw(dialogues, "%s x1 ", equipment->getName().c_str());
            wprintw(dialogues, "HP: %d ATK: %d DEF: %d", equipment->getHealth(), equipment->getAttack(), equipment->getDefense());
            newLine(dialogues, y, x);
            wprintw(dialogues, "%s", equipment->getDescription().c_str());
            newLine(dialogues, y, x);
        }
    }
    wrefresh(dialogues);
}

void Scene::showSack(Player *player) {
    int y, x;
    wclear(dialogues);
    box(dialogues, 0, 0);
    wmove(dialogues, 1, 1);
    for (const auto &[consumable, amount] : player->getSack()) {
        wprintw(dialogues, "%s: %d", consumable->getName().c_str(), amount);
        newLine(dialogues, y, x);
        wprintw(dialogues, "%s", consumable->getDescription().c_str());
        newLine(dialogues, y, x);
    }
    newLine(dialogues, y, x);
    wprintw(dialogues, "Press X to leave.");
    newLine(dialogues, y, x);
    wprintw(dialogues, "Press Enter to use items.");
    wrefresh(dialogues);
    inSack(player);
    wclear(dialogues);
    box(dialogues, 0, 0);
    wrefresh(dialogues);
}

// TODO: make it look better
void Scene::inSack(Player *player) {
    int y, x, input;
    size_t curFood = 0;
    bool check = false;
    const std::vector<std::pair<Consumable *, int>> &sack = player->getSack();
    while ((input = wgetch(dialogues))) {
        switch (input) {
        case 120: // X
            return;
        case 10: // Enter
            check = true;
            break;
        default:
            break;
        }
        if (check) break;
    }
    check = false;
    while (true) {
        wclear(dialogues);
        box(dialogues, 0, 0);
        wmove(dialogues, 1, 1);
        for (size_t i = 0; i < sack.size(); i++) {
            if (i == curFood) wattron(dialogues, A_REVERSE);
            wprintw(dialogues, "%s: %d", sack[i].first->getName().c_str(), sack[i].second);
            newLine(dialogues, y, x);
            wprintw(dialogues, "%s", sack[i].first->getDescription().c_str());
            newLine(dialogues, y, x);
            wattroff(dialogues, A_REVERSE);
        }
        getmaxyx(dialogues, y, x);
        if (check) {
            check = false;
            if (sack[curFood].second == 0) mvwprintw(dialogues, y - 2, 1, "You don't have any %s left!", sack[curFood].first->getName().c_str());
            else mvwprintw(dialogues, y - 2, 1, "You used 1 %s!", sack[curFood].first->getName().c_str());
        } else {
            mvwprintw(dialogues, y - 3, 1, "Press X to leave.");
            mvwprintw(dialogues, y - 2, 1, "Press Enter to use items.");
        }
        input = wgetch(dialogues);
        switch (input) {
        case KEY_UP:
            if (curFood == 0) break;
            curFood--;
            break;
        case KEY_DOWN:
            if (curFood == sack.size() - 1ull) break;
            curFood++;
            break;
        default:
            break;
        }
        if (input == 120) return;
        if (input == 10) {
            check = true;
            if (sack[curFood].second > 0) player->useConsumable(curFood, 1);
        }
    }
    wrefresh(dialogues);
}

void Scene::drawDialogues() {
    box(dialogues, 0, 0);
    wrefresh(dialogues);
}

int Scene::inOptions() {
    keypad(buttons, true);
    int keyPressed;
    size_t curButton = optionButtons.size() - 1;
    while (true) {
        for (size_t i = 0; i < optionButtons.size(); i++) {
            if (i == curButton) wattron(buttons, A_REVERSE);
            mvwprintw(buttons, 1 + 2 * static_cast<int>(optionButtons.size() - 1 - i), 1, optionButtons[i].c_str());
            wattroff(buttons, A_REVERSE);
        }
        keyPressed = wgetch(buttons);
        switch (keyPressed) {
        case KEY_UP:
            if (curButton == optionButtons.size() - 1ull) break;
            curButton++;
            break;
        case KEY_DOWN:
            if (curButton == 0) break;
            curButton--;
            break;
        default:
            break;
        }
        if (keyPressed == 27) return -1;
        if (keyPressed == 10) break; // Enter
    }
    wrefresh(buttons);
    return static_cast<int>(curButton);
}

WINDOW *Scene::getDialogues() {
    return this->dialogues;
}

// ====================exploring====================
ExploringScene::ExploringScene() : Scene() {
    optionButtons = {"Exit", "Sack", "Inventory", "Status"};
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);
    room = newwin(y_max / 2, y_max, 0, (x_max - y_max) / 2);
    refresh();
}

// y: 1~13, x:1~28
void ExploringScene::drawRoom(const Player *player) {
    short eco;
    switch (player->getRoom()->getEco()) {
    case Desert:
        eco = YELLOW_PAIR;
        break;
    case Forest:
        eco = GREEN_PAIR;
        break;
    default: // Swamp
        eco = BLUE_PAIR;
        break;
    }
    wclear(this->room);
    wattron(this->room, COLOR_PAIR(eco));
    box(this->room, 0, 0);
    wattroff(this->room, COLOR_PAIR(eco));
    mvwaddch(this->room, player->getCoordinateY(), player->getCoordinateX(), ACS_BLOCK);
    std::array<bool, 4> hasExit = player->getRoom()->getExit();
    if (hasExit[0]) mvwaddch(this->room, 0, Room::exit_X, ' ');
    if (hasExit[1]) mvwaddch(this->room, Room::room_height - 1, Room::exit_X, ' ');
    if (hasExit[2]) mvwaddch(this->room, Room::exit_Y, 0, ' ');
    if (hasExit[3]) mvwaddch(this->room, Room::exit_Y, Room::room_width - 1, ' ');

    // display objects
    const std::vector<Object *> &objects = player->getRoom()->getObjects();
    const std::vector<std::pair<int, int>> &locations = player->getRoom()->getLocs();
    const auto N = objects.size();
    for (size_t i = 0; i < N; i++) {
        if (objects[i]->getTag() == "NPC") {
            wattron(this->room, COLOR_PAIR(GREEN_PAIR));
            mvwaddch(this->room, locations[i].first, locations[i].second, 'N');
            wattroff(this->room, COLOR_PAIR(GREEN_PAIR));
        } else if (objects[i]->getTag() == "Monster") {
            wattron(this->room, COLOR_PAIR(RED_PAIR));
            mvwaddch(this->room, locations[i].first, locations[i].second, 'M');
            wattroff(this->room, COLOR_PAIR(RED_PAIR));
        }
    }
    wrefresh(this->room);
}

WINDOW *ExploringScene::getRoom() {
    return room;
}

void ExploringScene::clearScene() {
    wclear(this->room);
    wclear(this->buttons);
    wclear(this->dialogues);
    wclear(this->mini_map);
    wrefresh(this->room);
    wrefresh(this->buttons);
    wrefresh(this->dialogues);
    wrefresh(this->mini_map);
}

// ====================fighting====================
FightingScene::FightingScene() : Scene() {
    optionButtons = {"Exit", "Retreat", "Sack", "Inventory", "Status", "Attack"};
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);
    battle = newwin(y_max / 2, y_max, 0, (x_max - y_max) / 2);
    refresh();
}

void FightingScene::clearScene() {
    wclear(this->battle);
    wclear(this->buttons);
    wclear(this->dialogues);
    wclear(this->mini_map);
    wrefresh(this->battle);
    wrefresh(this->buttons);
    wrefresh(this->dialogues);
    wrefresh(this->mini_map);
}
void FightingScene::drawMonster(Monster *monster) {
    int y, x;
    wclear(battle);
    box(battle, 0, 0);
    wattron(battle, COLOR_PAIR(RED_PAIR));
    mvwprintw(battle, 0, 0, monster->getName().c_str());
    wattroff(battle, COLOR_PAIR(RED_PAIR));
    // TODO: print moster image
    wattron(battle, COLOR_PAIR(RED_PAIR));
    mvwprintw(battle, 1, 1, "An error occured while ");
    newLine(battle, y, x);
    wprintw(battle, "loading the Monster's image.");
    wattroff(battle, COLOR_PAIR(RED_PAIR));
    wrefresh(battle);
}

void FightingScene::drawDialogues(Monster *monster) {
    int y, x;
    box(dialogues, 0, 0);
    wmove(dialogues, 1, 1);
    wprintw(dialogues, "You met %s!", monster->getName().c_str());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Health: %d/%d", monster->getCurrentHealth(), monster->getMaxHealth());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Attack: %d", monster->getAttack());
    newLine(dialogues, y, x);
    wprintw(dialogues, "Defense: %d", monster->getDefense());
    wrefresh(dialogues);
}

void FightingScene::updateSituation(Player *player, Monster *monster, int playerDmg, int monsterDmg) {
    // player, monster, the dmg player took, the dmg monster took
    int y, x;
    wclear(dialogues);
    box(dialogues, 0, 0);
    wmove(dialogues, 1, 1);
    wprintw(dialogues, "You dealt %d points of damage!", monsterDmg);
    newLine(dialogues, y, x);
    wprintw(dialogues, "%s is now %d/%d", monster->getName().c_str(), monster->getCurrentHealth(), monster->getMaxHealth());
    newLine(dialogues, y, x);
    wprintw(dialogues, "%s dealt %d points of damage!", monster->getName().c_str(), playerDmg);
    newLine(dialogues, y, x);
    wprintw(dialogues, "You are now %d/%d", player->getCurrentHealth(), player->getMaxHealth());
    newLine(dialogues, y, x);
    wrefresh(dialogues);
}

// ====================trading====================
TradingScene::TradingScene() : Scene() {
    optionButtons = {"Exit", "Button1", "Button2"};
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);
    vendor = newwin(y_max / 2, y_max, 0, x_max / 2 - y_max);
    shop = newwin(y_max / 2, y_max, 0, x_max / 2);
    refresh();
}

void TradingScene::clearScene() {
    wclear(this->buttons);
    wclear(this->vendor);
    wclear(this->shop);
    wclear(this->dialogues);
    wrefresh(this->buttons);
    wrefresh(this->vendor);
    wrefresh(this->shop);
    wrefresh(this->dialogues);
}

void TradingScene::drawVendor(const NPC *npc) {
    int y, x;
    wclear(vendor);
    box(vendor, 0, 0);
    wattron(vendor, COLOR_PAIR(GREEN_PAIR));
    mvwprintw(vendor, 0, 0, npc->getName().c_str());
    wattroff(vendor, COLOR_PAIR(GREEN_PAIR));
    if (npc->getImagePath() == nullptr) {
        wattron(vendor, COLOR_PAIR(RED_PAIR));
        mvwprintw(vendor, 1, 1, "An error occured while ");
        newLine(vendor, y, x);
        wprintw(vendor, "loading the NPC's image.");
        wattroff(vendor, COLOR_PAIR(RED_PAIR));
        wrefresh(vendor);
    } else {
        std::ifstream stream(npc->getImagePath());
        std::string image_line;
        int lines = 0;
        y = npc->getImageY();
        x = npc->getImageX();
        while (std::getline(stream, image_line)) {
            wmove(vendor, y++, x);
            wprintw(vendor, image_line.c_str());
        }
        wrefresh(vendor);
    }
}

void TradingScene::drawShop() {
    wclear(shop);
    box(shop, 0, 0);
    mvwprintw(shop, 0, 0, "Shop");
    wrefresh(shop);
}

void TradingScene::drawDialogues() {
    int y, x;
    getmaxyx(dialogues, y, x);
    box(dialogues, 0, 0);
    mvwprintw(dialogues, y - 3, 1, "Press X to leave.");
    mvwprintw(dialogues, y - 2, 1, "Press Enter to continue.");
    wrefresh(dialogues);
}

WINDOW *TradingScene::getShop() {
    return this->shop;
}

WINDOW *TradingScene::getVendor() {
    return this->vendor;
}

// ====================not class====================
// experimental function
void initGraphic() {
    initscr();
    start_color();
    raw();
    noecho();
    printw("Press the key R when you are ready to play the game with current window size.\n");
    printw("And please do not change the size of the window during gameplay.\n");
    int input;
    while ((input = getch()) != static_cast<int>('r')) {
        printw("Do not spam other keys\n");
    }
    curs_set(0);
    clear();
    refresh();

    // initialize the color that will be used later
    init_color(COLOR_TAKO, 484, 422, 551);
    init_pair(TAKO_BACKGROUND, COLOR_BLACK, COLOR_TAKO);
    init_pair(REVERSE_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(TAKO_PAIR, COLOR_TAKO, COLOR_BLACK);
    init_pair(RED_PAIR, COLOR_RED, COLOR_BLACK); // test
    init_pair(RED_BACKGROUND, COLOR_WHITE, COLOR_RED); // test
    init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE_PAIR, COLOR_BLUE, COLOR_BLACK);
}

const int displayMenu() {
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);
    WINDOW *menu = newwin(20, 80, y_max / 2 - 5, x_max / 2 - 35);
    refresh();
    keypad(menu, true);
    wprintw(menu, "%s", readWholeFile("../assets/dungeon_title.txt").c_str());
    wrefresh(menu);

    std::array<std::string, 3> options{"Start", "Difficulty", "Exit"};
    int choice;
    size_t curButton = 0;
    while (true) {
        for (size_t i = 0; i < options.size(); i++) {
            if (i == curButton) wattron(menu, A_REVERSE);
            mvwprintw(menu, 10 + (i + 1) * 2, 30, options[i].c_str());
            wattroff(menu, A_REVERSE);
        }
        choice = wgetch(menu);
        switch (choice) {
        case KEY_UP:
            if (curButton == 0) break;
            curButton--;
            break;
        case KEY_DOWN:
            if (curButton == options.size() - 1) break;
            curButton++;
            break;
        default:
            break;
        }
        if (choice == 10) break;
    }
    wclear(menu);
    wrefresh(menu);
    delwin(menu);
    return static_cast<int>(curButton);
}

const int chooseDifficulty() {
    // haven't implemented it
    printw("This feature will be updated soon\n");
    printw("Press any key to leave\n");
    getch();
    clear();
    return -1;
}

const std::string readString(WINDOW *curWindow) {
    // read only readable character
    //  character count limit could be implemented
    echo();
    int x_origin, y_origin, x_cur, y_cur;
    getyx(curWindow, y_origin, x_origin);
    y_cur = y_origin;
    x_cur = x_origin;
    std::string input = "";
    int ch;
    keypad(curWindow, true);
    while ((ch = wgetch(curWindow)) != '\n') {
        if (ch >= 32 && ch <= 126) {
            input.push_back(ch);
            mvwaddch(curWindow, y_cur, x_cur, ch);
            x_cur++;
        } else if ((ch == 8 || ch == 127 || ch == KEY_BACKSPACE) && x_cur > x_origin) {
            input.pop_back();
            x_cur--;
            mvwaddch(curWindow, y_cur, x_cur, 32); // 32 = space
        }
    }
    getyx(curWindow, y_cur, x_cur);
    while (x_cur >= x_origin) {
        mvwaddch(curWindow, y_cur, x_cur, ' ');
        x_cur--;
    }
    noecho();
    return input;
}

const std::string inputPlayerName() {
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);
    WINDOW *field = newwin(3, x_max, y_max / 2, 0);
    box(field, 0, 0);
    mvwprintw(field, 0, 0, "Please enter your name");
    wmove(field, 1, 1);
    std::string name = readString(field);
    wclear(field);
    std::string msg = "Your name is " + name + "\n";
    mvwprintw(field, 0, 0, msg.c_str());
    mvwprintw(field, 1, 0, "Press any key to continue\n");
    wgetch(field);
    wclear(field);
    wrefresh(field);
    delwin(field);
    return name;
}

void endGraphic() {
    endwin();
}

void displayEndAnimation() {
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);
    WINDOW *animation = newwin(20, 90, y_max / 2 - 5, x_max / 2 - 40);
    refresh();
    keypad(animation, true);
    wattron(animation, COLOR_PAIR(YELLOW_PAIR));
    wprintw(animation, "%s", readWholeFile("../assets/you_win.txt").c_str());
    wattroff(animation, COLOR_PAIR(YELLOW_PAIR));
    mvwprintw(animation, 10, 23, "Press any key to close the game.");
    wgetch(animation);
}