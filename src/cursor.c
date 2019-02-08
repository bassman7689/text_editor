#include <ncurses.h> 

#include "cursor.h"
#include "screen.h"

void initCursor(cursor *c) {
    c->row = 0;
    c->col = 0;
}

void moveCursor(cursor *c, Dir direction) {
    switch (direction) {
        case DIR_UP: if (c->row > 0) c->row--;
                     break;

        case DIR_DOWN: if (c->row < (LINES - STATUS_LINE_HEIGHT - 1)) c->row++;
                        break;

        case DIR_LEFT: if (c->col > 0) c->col--;
                       break;

        case DIR_RIGHT: if (c->col < (COLS - 1)) c->col++;
                        break;
    }
}
