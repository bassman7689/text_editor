#ifndef BUFFER_H
#define BUFFER_H

#include "cursor.h"

typedef struct {
    cursor* c;
    char *status_message;
    char **lines;
    int num_lines;
} buffer;

void initBuffer(buffer *b);
void moveCursorBuffer(buffer *b, Dir direction);
void insertCharBuffer(buffer *b, char chr);
void appendLineBuffer(buffer *b, char* line);
void destroyBuffer(buffer *b);
int setStatusMessage(buffer *b, char *msg);

#endif

