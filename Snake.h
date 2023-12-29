#include <list>

#include "Utils.h"

#ifndef __SNAKE__
#define __SNAKE__

class Snake
{
	public:
		std::list<Vec> bmap;
		Direction current_direction;
	private:
		Direction def_direction = Direction::Right;
		Vec def_start;
		short def_len = 3;
		short len = 0;

	// methods
	private:
		void nw_head(Vec new_head);
		void rm_tail();
		void create_body(Vec start);
	public:
		Snake();
		Snake(Vec start, short len, Direction direction);
		void move_snake(Direction direction);
		void move_snake();
		void grow_snake();
		Vec get_head();
};

#endif // !__SNAKE__
