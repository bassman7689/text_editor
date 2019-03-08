#include <ctype.h>
#include <ncurses.h>

#include "buffer.H"
#include "keyboard.h"

int handleKeypress(buffer *b)
{
	int ch = getch();
	switch (ch) {
	case CTRL_KEY('q'):
		return FALSE;

	case KEY_UP:
		moveCursorBuffer(b, DIR_UP);
		return TRUE;
	case KEY_DOWN:
		moveCursorBuffer(b, DIR_DOWN);
		return TRUE;
	case KEY_LEFT:
		moveCursorBuffer(b, DIR_LEFT);
		return TRUE;
	case KEY_RIGHT:
		moveCursorBuffer(b, DIR_RIGHT);
		return TRUE;

	case KEY_BACKSPACE:
		deleteCharBuffer(b);
		return TRUE;

	case KEY_ENTER:
	case '\n':
		newLineBuffer(b);
		moveCursorBuffer(b, DIR_DOWN);
		return TRUE;

	case '\r':
		return TRUE;

	case '\t':
		return TRUE;

	default:
		if (!iscntrl(ch) && isascii(ch)) insertCharBuffer(b, ch);
		return TRUE;
	}
}
