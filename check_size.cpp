#include <cctype>
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

// an interactive program helps the user to resize the terminal

#define GREEN 1
#define RED 2

int main() {
    const int target_row = 30, target_col = 120;

    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int row, col, prev_row = -1, prev_col = -1;
    int mid_row, print_start_col, exit_start_col;

    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);

    const auto *const print_row = "Current Rows: ";
    const auto *const print_col = ", Current Columns: ";
    const auto print_len = static_cast<int>(std::strlen(print_row) + std::strlen(print_col) + 4);

    const auto *const exit = "(Press Q when done)";
    const auto exit_len = static_cast<int>(std::strlen(exit));

    while (true) {
        getmaxyx(stdscr, row, col);
        if (row != prev_row || col != prev_col) {
            mid_row = row >> 1;
            print_start_col = (col - print_len) >> 1;
            exit_start_col = (col - exit_len) >> 1;

            clear();
            move(mid_row, print_start_col);

            // row
            printw(print_row);
            attron(COLOR_PAIR(row == target_row ? GREEN : RED));
            printw("%d", row);
            attroff(COLOR_PAIR(row == target_row ? GREEN : RED));

            // col
            printw(print_col);
            attron(COLOR_PAIR(col == target_col ? GREEN : RED));
            printw("%d", col);
            attroff(COLOR_PAIR(col == target_col ? GREEN : RED));

            // exit
            mvprintw(mid_row + 1, exit_start_col, exit);
            refresh();

            prev_row = row;
            prev_col = col;
        }
        if (std::toupper(getch()) == 'Q') break;
    }
    endwin();
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
    return 0;
}