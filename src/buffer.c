#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "logger.h"
#include "screen.h"

void initBuffer(buffer *b)
{
	b->status_message = NULL;
	b->lines = NULL;
	b->num_lines = 0;
	b->c = malloc(sizeof(cursor));
	b->c->row = 0;
	b->c->col = 0;
}

void insertLineBuffer(buffer *b, int row)
{
    if (row > b->num_lines)
	    row = b->num_lines;

    b->lines = realloc(b->lines, sizeof(char*) * b->num_lines+1);

    if (row != b->num_lines) {
	memmove(b->lines + row + 1, b->lines + row, sizeof(char*) * (b->num_lines - row));
    }
    b->lines[row] = calloc(1, sizeof(char));
    b->lines[row][0] = '\0';
    b->num_lines++;
}

void insertCharBuffer(buffer *b, char chr)
{
	int row = b->c->row;

	if (!b->lines)
	        insertLineBuffer(b, b->num_lines);

	char *cur_line = b->lines[row];
	int line_len = cur_line ? strlen(cur_line) : 0;
	cur_line = realloc(cur_line, (line_len + 2) * sizeof(char));

	int col = b->c->col;
	memmove(cur_line + col + 1,
		cur_line + col,
		line_len - col);

	cur_line[col] = chr;
	cur_line[line_len + 1] = '\0';

	b->lines[row] = cur_line;
	moveCursorBuffer(b, b->c->row, b->c->col + 1);
}

void deleteCharBuffer(buffer *b)
{
	cursor *c = b->c;

	// TODO handle joining lines
	if (c->col == 0) return;

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
	moveCursorBuffer(b, b->c->row, b->c->col - 1);

}

void insertLineAtCursorBuffer(buffer *b, char* line)
{
    if (b->c->row + 1 > b->num_lines) return;

    insertLineBuffer(b, b->c->row + 1);

    int line_len = strlen(line);
    char* tmp = calloc(line_len + 1, sizeof(char));
    strncpy(tmp, line, line_len);
    tmp[line_len] = '\0';

    b->lines[b->c->row + 1] = tmp;
}

void newLineAtCursorBuffer(buffer *b)
{
    if (b->c->row > b->num_lines - 1) {
	insertLineBuffer(b, b->num_lines);
	return;
    }

    char * cur_line = b->lines[b->c->row];

    int line_len = strlen(cur_line);

    char * cur_pos;
    if (b->c->col > line_len - 1) {
	    insertLineAtCursorBuffer(b, "");
	    moveCursorBuffer(b, b->c->row + 1, 0);
	    return;
    } else {
	    cur_pos = cur_line + b->c->col;
	    insertLineAtCursorBuffer(b, cur_pos);
	    int new_line_len = b->c->col;
	    b->lines[b->c->row] = realloc(b->lines[b->c->row], (new_line_len + 1) * sizeof(char));
	    b->lines[b->c->row][new_line_len] = '\0';
	    moveCursorBuffer(b, b->c->row + 1, 0);
    }
}

void appendLineBuffer(buffer *b, char* line)
{
        insertLineBuffer(b, b->num_lines);

	int line_len = strlen(line);
	char* tmp = calloc(line_len + 1, sizeof(char));
	strncpy(tmp, line, line_len);
	tmp[line_len] = '\0';

	int cur_idx = b->num_lines - 1;
	b->lines[cur_idx] = tmp;
}

void moveCursorBuffer(buffer *b, int row, int col)
{
	cursor *c = b->c;

	c->row = row;
	c->col = col;

	int screen_lines = LINES - STATUS_LINE_HEIGHT - 1;
	int buffer_lines = b->num_lines - 1;
	int min_lines = screen_lines < buffer_lines ? screen_lines : buffer_lines;

	if (c->row < 0) {
		c->row = 0;
	} else if (c->row > screen_lines || c->row > buffer_lines)  {
		c->row = min_lines;
	}

	int screen_cols = COLS - 1;
	int buffer_cols = b->lines[c->row] ? strlen(b->lines[c->row]) : 0;
	int min_cols =  screen_cols < buffer_cols ? screen_cols : buffer_cols;

	if (c->col < 0) {
		c->col = 0;
	} else if (c->col > screen_cols || c->col > buffer_cols) {
		c->col = min_cols;
	}
}

void destroyBuffer(buffer *b)
{
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

int setStatusMessage(buffer *b, char *msg)
{
	if (b->status_message) free(b->status_message);

	int msgLen = strlen(msg);
	b->status_message = calloc(msgLen + 1, sizeof(char));
	if (b->status_message == NULL) {
		return 0;
	}

	strncpy(b->status_message, msg, msgLen);
	// strncpy may not do this, doing it for safety.
	b->status_message[msgLen] = '\0';
	return 1;
}

void debugLogBuffer(buffer* b)
{
	for (int i = 0; i < b->num_lines; i++) {
	    logInfo("\"%.*s\"\n", COLS, b->lines[i]);
	}
}
