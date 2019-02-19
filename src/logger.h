#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#ifndef LOG_LEVEL
#define DEBUG
#define LOG_LEVEL LEVEL_DEBUG
#endif

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

int initLogger(char* filename);
void logInfo(char* fmt, ...);
void destroyLogger();

#endif
