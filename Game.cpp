#include <curses.h>
#include <ncurses.h>
#include <stdexcept>
#include "Curse.h"
#include "Map.h"
#include "Snake.h"
#include "Food.h"
#include "Game.h"
#include "Utils.h"

Game::Game()
{
	this->food = new Food(Vec{25,10});
	this->snake = new Snake({0,0}, 3, Direction::Down);
	this->game_map = new Map(this->snake, this->food, Vec{25,10});
	this->screen = new CurseWindow(Vec{25, 10});
}

Game::~Game()
{
	delete this->game_map;
	delete this->food;
	delete this->snake;
	delete this->screen;
}

CollisionType
Game::check_collision()
{

	if (snake->get_head() == food->coord)
		return CollisionType::FoodCollision;

	else if ((snake->get_head().x > game_map->size.x) || (snake->get_head().y > game_map->size.y)
			|| (snake->get_head().x < 0 || snake->get_head().y < 0))
		return CollisionType::BorderCollision;
	else
	{
		auto it = snake->bmap.begin(); // skip the first index
		for (; it != (--snake->bmap.end()) ; it++)
		{
			if (snake->get_head().y == it->y && snake->get_head().x == it->x)
				return CollisionType::BodyCollision;
		}
	}

	return CollisionType::NoCollision;
}

void
Game::move_snake()
{
	game_map->unset_snake();

	switch(screen->get_keypress())
	{
		case KEY_UP:
			if (snake->current_direction == Direction::Up
					|| snake->current_direction == Direction::Down)
				goto MOV;
			snake->move_snake(Direction::Up);
			goto SET;
		case KEY_DOWN:
			if (snake->current_direction == Direction::Down
					|| snake->current_direction == Direction::Up )
				goto MOV;
			snake->move_snake(Direction::Down);
			goto SET;
		case KEY_LEFT:
			if (snake->current_direction == Direction::Left
					|| snake->current_direction == Direction::Right)
				goto MOV;
			snake->move_snake(Direction::Left);
			goto SET;
		case KEY_RIGHT:
			if (snake->current_direction == Direction::Right
					|| snake->current_direction == Direction::Left)
				goto MOV;
			snake->move_snake(Direction::Right);
			goto SET;
		default:
			goto MOV;
	}

	MOV:
		snake->move_snake();

	SET:
		game_map->set_snake();
}


void
Game::draw_map()
{
	screen->clear_screen();

	int y = 0;
	for(auto bits : game_map->bmap)
	{
		int x = 0;
		for (auto bit : bits)
		{
			switch(bit)
			{
				case MapBitType::PlayerBit:
					if (snake->get_head() == Vec{x,y})
						screen->printout('O', Vec{x,y});
					else
						screen->printout('#', Vec{x,y});
					break;
				case MapBitType::FoodBit:
					screen->printout('$', Vec{x,y});
					break;
				case MapBitType::EmptyBit:
					screen->printout('~', Vec{x,y});
					break;
				default:
					screen->printout('X', Vec{x,y});
					break;
			}
			x++;
		}
		screen->refresh();
		y++;
	}
}

void
Game::place_food()
{

	while(true)
	{
		food->init();

		for(auto coord : snake->bmap)
		{
			if (food->coord == coord)
				continue;
		}

		break;
	}
}

void
Game::run()
{
	bool run_game = true;
	place_food();
	game_map->update();

	while(run_game)
	{
		screen->sleep(120);
		draw_map();
		move_snake();

		switch (check_collision())
		{
			case FoodCollision:
				game_map->unset_snake();
				game_map->unset_food();
				place_food();
				snake->grow_snake();
				game_map->set_snake();
				game_map->set_food();
				break;

			case BodyCollision:
			case BorderCollision:
				run_game = false;
				break;
			case NoCollision:
				continue;
			default:
				throw std::out_of_range("Game(): run(), check_collision(), uncaught error!");
				break;
		}
	}

}
