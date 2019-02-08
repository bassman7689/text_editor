#ifndef SCREEN_H
#define SCREEN_H

#include "buffer.h"
#include "logger.h"
#include "version.h"

#define STATUS_LINE_HEIGHT 1
#define STARTUP_MESSAGE "Worm Editor " VERSION

void setupScreen();
void teardownScreen();

void renderScreen(buffer *b, logger* log);

#endif
