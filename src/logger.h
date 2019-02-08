#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

typedef struct {
    char* filename;
    FILE* fd;
} logger;

typedef enum {
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERR,
} LogLevel;

int initLogger(logger* log, char* filename, LogLevel level);
void logInfo(logger* log, char* fmt, ...);
void destroyLogger(logger* log);

#endif
