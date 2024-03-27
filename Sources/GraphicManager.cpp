#include "../Headers/GraphicManager.h"

#include <array>
#include <iostream>

// experimental function
void initGraphic() {
    initscr();
    raw();
    noecho();
    printw("Press the key R when you are ready to play the game with current window size.\n");
    int input;
    while ((input = getch()) != static_cast<int>('r')) {
        printw("Do not spam other keys\n");
    }
    curs_set(0);
    clear();
    refresh();
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
    refresh();
    getch();
    clear();
    return -1;
}

const std::string readString(WINDOW* curWindow) {
    // read only readable character
    //  character count limit could be implemented
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
    mvwprintw(field, 1, 0, "Press any key to leave");
    wgetch(field);
    wclear(field);
    wrefresh(field);
    delwin(field);
    return name;
}

void endGraphic() {
    endwin();
}