#include "Screen.h"

void
CursesWindow::cursor_visibility()
{
	curs_set(this->show_cursor);
}

void
CursesWindow::printout(char c, int x, int y)
{
	mvwaddch(this->Window, y, x, c);
	refresh_win();
}

void
CursesWindow::printout(string str, int x, int y)
{
	move_cursor(x,y);
	waddstr(this->Window, str.c_str());
	refresh_win();
}

int
CursesWindow::get_keypress(bool non_blocking, bool special_key)
{
	int key;
	noecho();
	cbreak();
	keypad(this->Window, special_key);
	keypad(this->MainScreen, non_blocking);
	nodelay(this->Window, non_blocking);
	nodelay(this->MainScreen, non_blocking);
	key = wgetch(this->Window);
	flushinp();
	return key;
}

void
CursesWindow::move_cursor(int x, int y)
{
	wmove(this->Window, y,x);
}

void
CursesWindow::refresh_win()
{
	cursor_visibility();
	wrefresh(this->Window);
}

void
CursesWindow::check_win_size(int width, int height, int start_x, int start_y)
{
	// get the current terminal size
	get_terminal_size();

	// checking the size
	if ((height > this->TerminalHeight) || (width > this->TerminalWidth) ||
		(start_x > this->TerminalHeight) || (start_y > this->TerminalWidth))
		throw std::out_of_range("check_win_size(): Window is too big!");
}

void
CursesWindow::get_terminal_size()
{
	// get the terminal size
	this->TerminalHeight = getmaxy(this->MainScreen);
	this->TerminalWidth = getmaxx(this->MainScreen);

}

CursesWindow::CursesWindow(int win_width, int win_height, int start_x, int start_y)
{
	// init the ncurses screen
	this->MainScreen = initscr();

	// make sure the window fits!
	check_win_size(win_width, win_height, start_x, start_y);

	// create the window
	this->Window = newwin(win_height, win_width, start_x, start_y);

	this->WindowWidth = win_width;
	this->WindowHeight = win_height;

	this->WindowStartX = start_x;
	this->WindowStartY = start_y;
}

CursesWindow::~CursesWindow()
{
	delwin(this->Window);
	endwin();
	std::system("stty sane");
}
