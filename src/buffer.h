#ifndef BUFFER_H
#define BUFFER_H

typedef struct {
	int row, col;
} cursor;

typedef enum {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
} Dir;


typedef struct {
	cursor* c;
	char *status_message;
	char **lines;
	int num_lines;
} buffer;

void initBuffer(buffer *b);
void insertLineBuffer(buffer *b, int row);
void newLineAtCursorBuffer(buffer *b);
void moveCursorBuffer(buffer *b, int row, int col);
void insertCharBuffer(buffer *b, char chr);
void deleteCharBuffer(buffer *b);
void appendLineBuffer(buffer *b, char* line);
void destroyBuffer(buffer *b);
int setStatusMessage(buffer *b, char *msg);
void debugLogBuffer(buffer *b);

#endif

