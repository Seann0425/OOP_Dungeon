#include "../Headers/GraphicManager.h"

#include <array>
#include <iostream>

// experimental function
void initGraphic() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
    printw("Press the key R when you are ready to play the game with current window size.\n");
    int input;
    while ((input = getch()) != static_cast<int>('r')) {
        printw("Do not spam other keys\n");
    }
    clear();
    refresh();
}
void displayMenu() {
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
        if (choice == 10) {
            if (curButton == 2) {
                endwin();
                return;
            }
            int x, y;
            getyx(stdscr, y, x);
            std::string tmp = "You choose ";
            tmp.append(options[curButton]);
            mvwprintw(stdscr, y, x, tmp.c_str());
            refresh();
            break;
        }
    }

    // make the program not to stop for now
    getch();
    endwin();
}
void endGraphic() {
    endwin();
}