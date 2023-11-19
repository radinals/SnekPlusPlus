#include "Game.h"

// set all cells on the map to empty
void
Game::init_empty_map()
{
	for(size_t y=0; y < this->max_y; y++) {
		vector <CellStatus> line;
		for(size_t x=0; x < this->max_x; x++ )
			line.push_back(CellEmpty);
		this->Cells.push_back(line);
	}
}

// return a pointer to a cell in the map
CellStatus*
Game::get_cell(size_t x, size_t y)
{
	try {
		return &this->Cells.at(y).at(x);

	} catch (...) {

		return nullptr;
	}
}

// random number between 0, and max;
size_t
Game::rand_n(size_t max)
{
	// random number generator, from /dev/urandom. used for the seed.
	std::random_device rd;

	// >=c++11 32bit pseudo-random number generator.
	std::mt19937 rng(rd());

	// range of numbers between min & max.
	std::uniform_int_distribution<size_t> uni(0,max);

	return uni(rng);

}

// modify the food_present attribute
// sets to false if no food is placed in the map, otherwise true
void
Game::check_snake_hit_food()
{
	if (this->food_coord.x == this->snake->get_head().x &&
		this->food_coord.y == this->snake->get_head().y) {
		this->snake->grow_snake(this->food_coord);
		this->food_present = false;
	}
}

// place the food in a random empty cell on the map
// or if already placed just replace it
void
Game::place_food()
{
	size_t x, y;

	check_snake_hit_food();

	try {
		while(true) {
			x = (food_present) ? food_coord.x : rand_n(this->max_x-1);
			y = (food_present) ? food_coord.y : rand_n(this->max_y-1);

			CellStatus* cell_ptr = get_cell(x,y);
			if (cell_ptr != nullptr && *cell_ptr == CellEmpty) {
				*cell_ptr = CellFood;
				break;
			}
		}
	} catch (...) {
		throw (GameFoodPlacementFailed("place_food(): failed to place food"));
	}

	if (! food_present) {
		food_coord.x = x;
		food_coord.y = y;
		food_present = true;
	}
}

// place the snake on the game map
void
Game::place_snake()
{
	for ( COORD coord : this->snake->get_snake_body() ) {
		CellStatus*  cell_ptr = get_cell(coord.x, coord.y);
		if (cell_ptr != nullptr && *cell_ptr == CellEmpty) *cell_ptr = CellSnake;
	}
}

// directly move the snake, without checking
void
Game::move_snake_to(Direction direction) {
	switch (direction) {
		case GoingRight:
			this->snake->move_right();
			break;
		case GoingLeft:
			this->snake->move_left();
			break;
		case GoingUp:
			this->snake->move_up();
			break;
		case GoingDown:
			this->snake->move_down();
			break;
	}
	collision_detected();
}

// checks first the movement
// a snake can only go left or right of his head
void
Game::move_snake(Direction move_to)
{
	Snake* snake = this->snake;

	if (move_to == snake->head_direction)
		return;
	else if (move_to == GoingDown && snake->head_direction == GoingUp)
		return;
	else if (move_to == GoingUp && snake->head_direction == GoingDown)
		return;
	else if (move_to == GoingLeft && snake->head_direction == GoingRight)
		return;
	else if (move_to == GoingRight && snake->head_direction == GoingLeft)
		return;

	move_snake_to(move_to);
}


// detects any out of bounds movements
// detects if snake hits it's body
void
Game::collision_detected()
{
	COORD snake_head = this->snake->get_head();
	vector<COORD> snake_body = this->snake->get_snake_body();

	if (snake_head.x < 0 || snake_head.y < 0)
		throw SnakeIsDead("collision_detected(): snake is dead!");
	else if (snake_head.x >= max_x || snake_head.y >= max_y)
		throw SnakeIsDead("collision_detected(): snake is dead!");
	else {
		for(size_t i=1; i < snake_body.size(); i++) {
			if (snake_head.x == snake_body.at(i).x && snake_head.y == snake_body.at(i).y)
				throw SnakeIsDead("collision_detected(): snake is dead!");
		}
	}
}

// resets the map
void
Game::reset_map() {
	this->Cells.clear();
	init_empty_map();
	place_food();
	place_snake();
}

Game::Game(size_t max_x, size_t max_y, Snake* snake)
{
	this->max_x = max_x;
	this->max_y = max_y;
	this->snake = snake;

	init_empty_map();
	place_food();
	place_snake();
}
