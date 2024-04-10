#include "../Headers/GraphicManager.h"

#include <array>
#include <iostream>

// Scene Initialize
Scene::Scene() {
    int Y, X;
    getmaxyx(stdscr, Y, X);
    buttons = newwin(Y / 2, Y / 2, Y / 2, 0);
    dialogues = newwin(Y / 2, X - Y * 3 / 2, Y / 2, Y / 2);
    mini_map = newwin(Y / 2, Y, Y / 2, X - Y);
    refresh();
    box(buttons, 0, 0);
    box(dialogues, 0, 0);
    box(mini_map, 0, 0);
    wrefresh(buttons);
    wrefresh(dialogues);
    wrefresh(mini_map);
}

// TODO: update mini_map status, which includes current player room and regular rooms
void Scene::drawMiniMap(Dungeon* dungeon) {
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
    WINDOW* cur_area = subwin(mini_map, y / 3 - 2, x / 3 - 1, Y / 2 + y / 3 * dungeon->getCurrentIndex().first + 1,
                              X - Y + (x / 3) * dungeon->getCurrentIndex().second + 1);
    wrefresh(mini_map);
    touchwin(mini_map);
    wclear(cur_area);
    wbkgd(cur_area, COLOR_PAIR(REVERSE_PAIR));
    wrefresh(cur_area);
    delwin(cur_area);
}

void Scene::drawOptions() {
    for (size_t i = 0; i < optionButtons.size(); i++) {
        mvwprintw(buttons, 1 + 2 * static_cast<int>(optionButtons.size() - 1 - i), 1, optionButtons[i].c_str());
    }
    wrefresh(buttons);
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
                if (curButton == optionButtons.size() - 1) break;
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
        if (keyPressed == 10) break;  // Enter
    }
    wrefresh(buttons);
    return static_cast<int>(curButton);
}

ExploringScene::ExploringScene() : Scene() {
    optionButtons = {"Exit", "Status"};
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);
    room = newwin(y_max / 2, y_max, 0, (x_max - y_max) / 2);
    refresh();
    box(room, 0, 0);
    wrefresh(room);
}

// y: 1~13, x:1~28
void ExploringScene::drawRoom(const Player* player) {
    box(this->room, 0, 0);
    mvwaddch(this->room, player->getCoordinateY(), player->getCoordinateX(), ACS_BLOCK);
    std::array<bool, 4> hasExit = player->getRoom()->getExit();
    // BUG CANDIDATE
    if (hasExit[0]) mvwaddch(this->room, 0, Room::exit_X, ' ');
    if (hasExit[1]) mvwaddch(this->room, Room::room_height - 1, Room::exit_X, ' ');
    if (hasExit[2]) mvwaddch(this->room, Room::exit_Y, 0, ' ');
    if (hasExit[3]) mvwaddch(this->room, Room::exit_Y, Room::room_width - 1, ' ');
    wrefresh(this->room);
    // TODO: display object
}

WINDOW* ExploringScene::getRoom() {
    return room;
}

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
    init_pair(RED_PAIR, COLOR_RED, COLOR_BLACK);        // test
    init_pair(RED_BACKGROUND, COLOR_WHITE, COLOR_RED);  // test
}

const int displayMenu() {
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);
    WINDOW* menu = newwin(20, 80, y_max / 2 - 5, x_max / 2 - 35);
    refresh();
    keypad(menu, true);
    wprintw(menu,
            "/$$$$$$$  /$$   /$$ /$$   /$$  /$$$$$$  /$$$$$$$$  /$$$$$$  /$$   /$$\n\
| $$__  $$| $$  | $$| $$$ | $$ /$$__  $$| $$_____/ /$$__  $$| $$$ | $$\n\
| $$  \\ $$| $$  | $$| $$$$| $$| $$  \\__/| $$      | $$  \\ $$| $$$$| $$\n\
| $$  | $$| $$  | $$| $$ $$ $$| $$ /$$$$| $$$$$   | $$  | $$| $$ $$ $$\n\
| $$  | $$| $$  | $$| $$  $$$$| $$|_  $$| $$__/   | $$  | $$| $$  $$$$\n\
| $$  | $$| $$  | $$| $$\\  $$$| $$  \\ $$| $$      | $$  | $$| $$\\  $$$\n\
| $$$$$$$/|  $$$$$$/| $$ \\  $$|  $$$$$$/| $$$$$$$$|  $$$$$$/| $$ \\  $$\n\
|_______/  \\______/ |__/  \\__/ \\______/ |________/ \\______/ |__/  \\__/\n");
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

const std::string readString(WINDOW* curWindow) {
    // read only readable character
    //  character count limit could be implemented
    echo();
    int x_origin, y_origin, x_cur, y_cur;
    getyx(curWindow, y_origin, x_origin);
    y_cur = y_origin;
    x_cur = x_origin;
    std::string input = "";
    nocbreak();
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
            mvwaddch(curWindow, y_cur, x_cur, 32);  // 32 = space
        }
    }
    getyx(curWindow, y_cur, x_cur);
    while (x_cur >= x_origin) {
        mvwaddch(curWindow, y_cur, x_cur, ' ');
        x_cur--;
    }
    cbreak();
    noecho();
    return input;
}

const std::string inputPlayerName() {
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);
    WINDOW* field = newwin(3, x_max, y_max / 2, 0);
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