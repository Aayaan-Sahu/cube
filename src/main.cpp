#include <chrono>
#include <thread>
#include <cstdio>
#include <iostream>
#include <ncurses.h>

#include "../include/Vector.hpp"
#include "../include/Matrix.hpp"
#include "../include/Cube.hpp"

void setup_curses() {
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    cbreak();
    nodelay(stdscr, true);
}

void clean_curses() {
    curs_set(1);
    getch();
    endwin();
}

void plot(int x, int y, size_t cols, size_t rows, wchar_t c) {
    auto col_to_plot = (int)(((cols) / 2) + x);
    auto row_to_plot = (int)(rows - ((rows / 2) + y) - 1);
    mvaddch(row_to_plot, col_to_plot, c);
}

bool keyboard_hit() {
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return true;
    }
    return false;
}

int main(void) {
    const size_t COLS = 61;
    const size_t ROWS = 31;
    const bool DRAW_BACKGROUND = false;

    Cube cube;

    setup_curses();

    while (true) {
        // events
        if (keyboard_hit()) {
            exit(EXIT_SUCCESS);
        }

        // draw board
        if (DRAW_BACKGROUND) {
            for (auto y = 0; y < ROWS; y++) {
                for (auto x = 0; x < COLS; x++) {
                    mvaddch(y, x, '.');
                }
            }
        }

        // update cube
        cube.update();

        // draw
        clear();
        cube.display(plot, COLS, ROWS);
        refresh();


        // sleep bc fast
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    clean_curses();
}
