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

logger GlobalLogger;

int initLogger(char* filename, LogLevel level);
void logInfo(char* fmt, ...);
void destroyLogger();

#endif
