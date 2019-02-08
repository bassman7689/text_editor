#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "cursor.h"

void initBuffer(buffer *b) {
    b->status_message = NULL;
    b->lines = NULL;
    b->num_lines = 0;
    b->c = malloc(sizeof(cursor));
    initCursor(b->c);
}

// TODO Make this work with empty buffer
void insertCharBuffer(buffer *b, char chr) {
    int row = b->c->row;
    char *cur_line = b->lines[row];

    int line_len = strlen(cur_line);
    cur_line = realloc(cur_line, (line_len + 2) * sizeof(char));

    int col = b->c->col;
    memmove(cur_line + col + 1,
            cur_line + col,
            line_len - col);

    cur_line[col] = chr; 
    cur_line[line_len + 1] = '\0';

    b->lines[row] = cur_line;
    moveCursorBuffer(b, DIR_RIGHT);
}

void appendLineBuffer(buffer *b, char* line) {
    b->num_lines++;
    b->lines = realloc(b->lines, b->num_lines * sizeof(char*));

    int line_len = strlen(line);
    char* tmp = calloc(line_len + 1, sizeof(char));
    strncpy(tmp, line, line_len);
    tmp[line_len] = '\0';

    int cur_idx = b->num_lines - 1;
    b->lines[cur_idx] = tmp;
}

void moveCursorBuffer(buffer *b, Dir direction) {
    cursor *c = b->c;
    moveCursor(c, direction);

    if (c->row > b->num_lines - 1) c->row = b->num_lines - 1;
    else if (c->row < 0) c->row = 0;

    int cur_row_len = strlen(b->lines[c->row]);
    if (c->col > cur_row_len) c->col = cur_row_len;
    else if (c->col < 0) c->col = 0;
}

void destroyBuffer(buffer *b) {
    if (b->status_message) {
        free(b->status_message);
        b->status_message = NULL;
    }

    if (b->c) {
        free(b->c);
        b->c = NULL;
    }

    if (b->lines) {
        for (int i = 0; i < b->num_lines; i++) {
            if (b->lines[i]) free(b->lines[i]);
        }
        free(b->lines);
        b->lines = NULL;
        b->num_lines = 0;
    }

}

int setStatusMessage(buffer *b, char *msg) {
    if (b->status_message) free(b->status_message); 

    int msgLen = strlen(msg);
    b->status_message = calloc(msgLen + 1, sizeof(char));
    if (b->status_message == NULL) {
        return 0;
    }

    strncpy(b->status_message, msg, msgLen);
    // just in case
    b->status_message[msgLen] = '\0';
    return 1;
}
