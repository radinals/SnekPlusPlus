#include <vector>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <stdexcept>

#include "Utils.h"

using std::vector;
using std::size_t;

#ifndef __SNAKE__
#define __SNAKE__


class
SnakeInvalidMovement : public std::exception
{
    private:
	    char const* message;

    public:
	    SnakeInvalidMovement(char const* msg) : message(msg) {}
	    char const* what () { return message; }
};

class Snake
{
	private:
		const size_t min_len = 4;
		// first element is ALWAYS the head
		// last element is the "tail"
		vector<COORD> body;
	public:
		Direction head_direction;

	private:
		void set_new_head(COORD nw_head);
		void add_new_tail(COORD nw_tail);
		void remove_tail();
		bool coord_valid(COORD coord);
	public:
		COORD get_head();
		size_t snake_len();
		void move_up();
		void move_down();
		void move_left();
		void move_right();
		void grow_snake(COORD food_coord);
		vector<COORD> get_snake_body();
		Snake(vector<COORD> head, Direction starting_direction);
};

#endif // __SNAKE__
