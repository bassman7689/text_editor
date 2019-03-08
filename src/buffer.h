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
void newLineBuffer(buffer *b);
void moveCursorBuffer(buffer *b, Dir direction);
void insertCharBuffer(buffer *b, char chr);
void deleteCharBuffer(buffer *b);
void appendLineBuffer(buffer *b, char* line);
void destroyBuffer(buffer *b);
int setStatusMessage(buffer *b, char *msg);

#endif

