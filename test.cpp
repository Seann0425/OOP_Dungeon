#include <iostream>
#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int row, col;
    while (true) {
        getmaxyx(stdscr, row, col);
        mvprintw(0, 0, "%d %d", row, col);
        refresh();
    }
}