#include <vector>
#include <exception>
#include <random>

#include "Utils.h"
#include "Snake.h"

#ifndef __GAME__
#define __GAME__

using std::size_t;
using std::vector;

class
GameFoodPlacementFailed : public std::exception
{
    private:
	    char const* message;

    public:
	    GameFoodPlacementFailed(char const* msg) : message(msg) {}
	    char const* what () { return message; }
};

class
SnakeIsDead: public std::exception
{
    private:
	    char const* message;

    public:
	    SnakeIsDead(char const* msg) : message(msg) {}
	    char const* what () { return message; }
};

class Game
{
	public:
		unsigned short game_score = 0;
		vector<vector<CellStatus>> Cells;
		Snake* snake;
		size_t max_x, max_y;
	private:
		COORD food_coord;
		bool food_present = false;

	private:
		void init_empty_map();
		void collision_detected();
		size_t rand_n(size_t max);
	public:
		CellStatus* get_cell(size_t x, size_t y);
		void place_food();
		void place_snake();
		void check_snake_hit_food();
		void reset_map();
		void move_snake(Direction direction);
		void move_snake_to(Direction direction);
		Game(size_t max_x, size_t max_y, Snake* snake);
};

#endif // !__GAME__
