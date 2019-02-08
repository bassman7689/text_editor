#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "logger.h"
#include "screen.h"

void initBuffer(buffer *b) {
    b->status_message = NULL;
    b->lines = NULL;
    b->num_lines = 0;
    b->c = malloc(sizeof(cursor));
    b->c->row = 0;
    b->c->col = 0;
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

void deleteCharBuffer(buffer *b) {
    cursor *c = b->c;
    char *cur_line = b->lines[c->row];
    if (cur_line == NULL) {
        return;
    }

    int line_len = strlen(cur_line);
    if (line_len == 0) {
        return;
    }
    cur_line = realloc(cur_line, (line_len) * sizeof(char));

    memmove(cur_line + c->col - 1,
            cur_line + c->col,
            line_len - c->col + 1);

    cur_line[line_len] = '\0';

    b->lines[c->row] = cur_line;
    moveCursorBuffer(b, DIR_LEFT);

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

    switch (direction) {
        case DIR_UP: c->row--;
                     break;

        case DIR_DOWN: c->row++;
                       break;

        case DIR_LEFT: c->col--;
                       break;

        case DIR_RIGHT: c->col++;
                        break;
    }

    int screen_lines = LINES - STATUS_LINE_HEIGHT - 1;
    int buffer_lines = b->num_lines - 1;
    int min_lines = screen_lines < buffer_lines ? screen_lines : buffer_lines;

    if (c->row < 0) {
        c->row = 0;
    } else if (c->row > screen_lines || c->row > buffer_lines)  {
        c->row = min_lines;
    }

    int screen_cols = COLS - 1;
    int buffer_cols = strlen(b->lines[c->row]);
    int min_cols =  screen_cols < buffer_cols ? screen_cols : buffer_cols;

    if (c->col < 0) {
        c->col = 0;
    } else if (c->col > screen_cols || c->col > buffer_cols) {
        c->col = min_cols;
    }
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
