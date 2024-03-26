#include "../Headers/GraphicManager.h"

// experimental function
void initGraphic() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    printw("Press the key R when you are ready to play the game with current window size.\n");
    int input;
    while ((input = getch()) != static_cast<int>('r')) {
        printw("Do not spam other keys\n");
    }
}
void displayMenu() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    printw("Press the key R when you are ready to play the game with current window size.\n");
    int input;
    while ((input = getch()) != static_cast<int>('r')) {
        printw("Do not spam other keys\n");
    }
    clear();
    refresh();
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);
    WINDOW* title = newwin(10, 80, y_max / 2 - 5, x_max / 2 - 35);
    refresh();
    wprintw(title,
            "/$$$$$$$  /$$   /$$ /$$   /$$  /$$$$$$  /$$$$$$$$  /$$$$$$  /$$   /$$\n\
| $$__  $$| $$  | $$| $$$ | $$ /$$__  $$| $$_____/ /$$__  $$| $$$ | $$\n\
| $$  \\ $$| $$  | $$| $$$$| $$| $$  \\__/| $$      | $$  \\ $$| $$$$| $$\n\
| $$  | $$| $$  | $$| $$ $$ $$| $$ /$$$$| $$$$$   | $$  | $$| $$ $$ $$\n\
| $$  | $$| $$  | $$| $$  $$$$| $$|_  $$| $$__/   | $$  | $$| $$  $$$$\n\
| $$  | $$| $$  | $$| $$\\  $$$| $$  \\ $$| $$      | $$  | $$| $$\\  $$$\n\
| $$$$$$$/|  $$$$$$/| $$ \\  $$|  $$$$$$/| $$$$$$$$|  $$$$$$/| $$ \\  $$\n\
|_______/  \\______/ |__/  \\__/ \\______/ |________/ \\______/ |__/  \\__/\n");
    wrefresh(title);
    getch();
    endwin();
}
void endGraphic() {
    endwin();
}