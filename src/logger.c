#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

int initLogger(logger* log, char* filename, LogLevel level) {
    int filename_len = strlen(filename);
    log->filename = calloc(filename_len + 1, sizeof(char));
    strncpy(log->filename, filename, filename_len);
    log->filename[filename_len] = '\0';

    errno = 0;
    log->fd = fopen(log->filename, "a+");
    if (log->fd == NULL) {
        return errno;
    }

    return 0;
}

void logInfo(logger* log, char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(log->fd, "INFO ");
    vfprintf(log->fd, fmt, args);
    va_end(args);
}

void destroyLogger(logger* log) {
    fclose(log->fd);
    free(log->filename);
}
