#include <cstdlib>
#include <curses.h>
#include <ncurses.h>

#include "Utils.h"
#include "Curse.h"

CurseWindow::CurseWindow(Vec win_size)
{
	initscr();

	termsize.y = getmaxy(stdscr);
	termsize.x = getmaxx(stdscr);

	if ((win_size > termsize) || win_size <= winstart)
		exit(-100); // TODO: ERORR

	winsize = win_size;

	this->win = newwin(winsize.y, winsize.x, winstart.x, winstart.y);

	preset();
}

CurseWindow::~CurseWindow()
{
	delwin(win);
	endwin();
	std::system("stty sane");
}

void
CurseWindow::preset()
{
	noecho(); cbreak();
	keypad(win, true);
	nodelay(win, true);
	curs_set(false);
}

int
CurseWindow::get_keypress()
{
	int key = wgetch(win);
	flushinp();
	return key;
}

void
CurseWindow::printout(char c, Vec coord)
{
	mvwaddch(win, coord.y, coord.x, c);
}

void
CurseWindow::clear_screen()
{
	clear();
}

void
CurseWindow::refresh()
{
	wrefresh(win);
}

void
CurseWindow::sleep(int ms)
{
	napms(ms);
}
