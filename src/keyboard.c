#include <ctype.h>
#include <ncurses.h>

#include "buffer.h"
#include "keyboard.h"
#include "logger.h"

int handleKeypress(buffer *b)
{
	int ch = getch();
	switch (ch) {
	case CTRL_KEY('q'):
		debugLogBuffer(b);
		return FALSE;

	case KEY_UP:
		moveCursorBuffer(b, b->c->row - 1, b->c->col);
		return TRUE;
	case KEY_DOWN:
		moveCursorBuffer(b, b->c->row + 1, b->c->col);
		return TRUE;
	case KEY_LEFT:
		moveCursorBuffer(b, b->c->row, b->c->col - 1);
		return TRUE;
	case KEY_RIGHT:
		moveCursorBuffer(b, b->c->row, b->c->col + 1);
		return TRUE;

	case KEY_BACKSPACE:
		deleteCharBuffer(b);
		return TRUE;

	case KEY_ENTER:
	case '\n':
		newLineAtCursorBuffer(b);
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
