#include <curses.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>

using std::string;

#ifndef __SCREEN__
#define __SCREEN__

class CursesWindow
{
	private:
		WINDOW* MainScreen = stdscr;
		WINDOW* Window;
		int TerminalWidth=0, TerminalHeight=0;
		int WindowWidth, WindowHeight;
		int WindowStartX, WindowStartY;
		short show_cursor = false;

	private:
		void get_terminal_size();
		void check_win_size(int width, int height, int start_x, int start_y);
		void cursor_visibility();
	public:
		int get_keypress(bool non_blocking, bool special_key);
		void move_cursor(int x, int y);
		void refresh_win();

		void printout(char c, int x, int y);
		void printout(string c, int x, int y);

		CursesWindow(int win_width, int win_height, int start_x, int start_y);
		~CursesWindow();
};

#endif // !__SCREEN__
