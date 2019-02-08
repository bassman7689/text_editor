#include <ncurses.h>
#include <string.h>

#include "screen.h"

void setupScreen() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

void teardownScreen() {
    endwin();
}

static void renderBuffer(buffer* b) {
    for (int i = 0; i < (LINES - STATUS_LINE_HEIGHT) && i < b->num_lines; i++) {
        mvprintw(i, 0, b->lines[i]);
    }
}

static void renderStartupScreen() {
    for(int i = 0; i < LINES - STATUS_LINE_HEIGHT; i++) {
        mvprintw(i, 0, "~");
        if (i == LINES / 3) {
            mvprintw(i, (COLS - strlen(STARTUP_MESSAGE))/2, STARTUP_MESSAGE); 
        }
    }
}

void renderScreen(buffer *b, logger* log) {
    move(0, 0);
    clrtobot();

    //logInfo(log, "cursor: (%d, %d)\n", b.c->row, b.c->col);

    if (b->lines) {
        renderBuffer(b);
    } else {
        renderStartupScreen();
    }


    if (b->status_message) {
        mvprintw(LINES-1, 0, b->status_message);
        mvchgat(LINES-1, 0, -1, A_REVERSE, 0, NULL);
    }

    move(b->c->row, b->c->col);
    refresh();
}
