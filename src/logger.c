#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

int initLogger(char* filename)
{
	int filename_len = strlen(filename);
	GlobalLogger.filename = calloc(filename_len + 1, sizeof(char));
	strncpy(GlobalLogger.filename, filename, filename_len);
	GlobalLogger.filename[filename_len] = '\0';

	errno = 0;
	GlobalLogger.fd = fopen(GlobalLogger.filename, "a+");
	if (GlobalLogger.fd == NULL) {
		return errno;
	}

	return 0;
}

void logInfo(char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	if (LOG_LEVEL <= LEVEL_INFO) {
		fprintf(GlobalLogger.fd, "INFO ");
		vfprintf(GlobalLogger.fd, fmt, args);
	}
	va_end(args);
}

void destroyLogger()
{
	fclose(GlobalLogger.fd);
	free(GlobalLogger.filename);
}
