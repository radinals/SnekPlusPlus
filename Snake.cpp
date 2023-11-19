#include "Snake.h"
#include "Utils.h"

void
Snake::move_up()
{
	/*
	 * Decrement head y index, remove_tail();
	*/

	COORD new_head = get_head();

	new_head.y--;


	set_new_head(new_head);
	remove_tail();

	this->head_direction = GoingUp;
}

void
Snake::move_down()
{
	/*
	 * Increment head y index, remove_tail();
	*/

	COORD new_head = get_head();

	new_head.y++;


	set_new_head(new_head);

	remove_tail();

	this->head_direction = GoingDown;
}

void
Snake::move_left()
{

	/*
	 * Decrement head x index, remove_tail();
	*/

	COORD new_head = get_head();

	new_head.x--;


	set_new_head(new_head);

	remove_tail();

	this->head_direction = GoingLeft;

}

void
Snake::move_right()
{

	/*
	 * Increment head x index, remove_tail();
	*/

	COORD new_head = get_head();

	new_head.x++;


	set_new_head(new_head);

	remove_tail();
	this->head_direction = GoingRight;
}

bool
Snake::coord_valid(COORD coord) {
	if (coord.y < 0 || coord.x < 0) return false;
	return true;
}

void
Snake::set_new_head(COORD nw_head)
{
	this->body.insert(this->body.begin(), 1, nw_head);
}

void
Snake::add_new_tail(COORD nw_tail)
{
	this->body.insert(this->body.end(), 1, nw_tail);
}


COORD
Snake::get_head()
{
	return this->body.front();
}

void
Snake::remove_tail()
{
	this->body.erase(this->body.end()-1);
}

void
Snake::grow_snake(COORD food_coord)
{
	set_new_head(food_coord);
}

size_t
Snake::snake_len()
{
	return (this->body.size()) - this->min_len;
}

vector<COORD>
Snake::get_snake_body()
{
	return this->body;
}


Snake::Snake(vector<COORD> initial_coords, Direction starting_direction)
{
	for(auto coord : initial_coords)
		add_new_tail(coord);
	this->head_direction = starting_direction;

}
