#include <cstdlib>
#include <curses.h>
#include <ncurses.h>

#include "Utils.h"
#include "Curse.h"

CurseWindow::CurseWindow(Vec win_size)
{
	stdscr = initscr();

	termsize.y = getmaxy(stdscr);
	termsize.x = getmaxx(stdscr);

	winstart.x = 0;
	winstart.y = 0;

	winsize = win_size;

	if ((winsize > termsize) || winsize <= winstart)
		exit(-100); // TODO: ERORR

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
