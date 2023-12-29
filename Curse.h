#include <curses.h>
#include <ncurses.h>
#include <string>
#include <memory>

#include "Utils.h"

#ifndef __CURSE__
#define __CURSE__

class CurseWindow
{
	private:
		WINDOW* win;
		Vec winsize;
		Vec termsize;
		Vec winstart;
	private:
		void get_termsize();
		void check_termsize();
		void preset();

	public:
		int get_keypress();
		void printout(char c, Vec coord);
		void refresh();
		void sleep(int ms);
		void clear_screen();

		CurseWindow(Vec winsize);
		~CurseWindow();
};

#endif // !__CURSE__
