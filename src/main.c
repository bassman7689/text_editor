#include <ncurses.h>
#include <stdlib.h>

#include "buffer.h"
#include "keyboard.h"
#include "logger.h"
#include "screen.h"

int main()
{
	initLogger("errorlog");

	setupScreen();

	buffer b;
	initBuffer(&b);

	if(!setStatusMessage(&b, "PRESS Ctrl-Q to Exit")) {
		destroyBuffer(&b);
		teardownScreen(&b);
		destroyLogger();
		exit(1);
	}

	int running = 1;
	while(running) {
		renderScreen(&b);
		running = handleKeypress(&b);
	};

	destroyBuffer(&b);
	teardownScreen();
	destroyLogger();

	return 0;
}
