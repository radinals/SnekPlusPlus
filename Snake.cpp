#include "Utils.h"
#include <stdexcept>
#include "Snake.h"

Snake::Snake()
{
	this->len = def_len;
	this->current_direction = def_direction;
	create_body(def_start);
}

Snake::Snake(Vec start, short len, Direction direction)
{
	this->len = len;
	this->current_direction = direction;
	create_body(start);
}

Vec
Snake::get_head()
{
	return bmap.back();
}

void
Snake::nw_head(Vec new_head)
{
	bmap.push_back(new_head);
}

void
Snake::rm_tail()
{
	bmap.pop_front();
}

void
Snake::create_body(Vec start)
{
	nw_head(start);
	for(short i=0; i < len; i++, nw_head(start))
	{
		if (start < Vec{0, 0})
			throw std::out_of_range("Snake::create_body():OUT OF RANGE\n"); // TODO: error checking

		switch(current_direction)
		{
			case Up:
				start.y--;
				break;
			case Down:
				start.y++;
				break;
			case Left:
				start.x--;
				break;
			case Right:
				start.x++;
				break;
		}

	}
}

void
Snake::grow_snake()
{
	Vec head = get_head();
	switch(current_direction)
	{
		case Up:
			head.y--;
			break;
		case Down:
			head.y++;
			break;
		case Left:
			head.x--;
			break;
		case Right:
			head.x++;
			break;
	}
	nw_head(head);
}

void
Snake::move_snake(Direction direction)
{
	current_direction = direction;
	grow_snake();
	rm_tail();

}

void
Snake::move_snake()
{
	grow_snake();
	rm_tail();
	len++;

}
