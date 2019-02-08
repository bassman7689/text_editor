#ifndef CURSOR_H
#define CURSOR_H

typedef struct {
    int row, col;
} cursor;

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Dir;

void initCursor(cursor *c);
void moveCursor(cursor *c, Dir direction);
#endif
