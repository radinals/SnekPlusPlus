#include "Snake.h"
#include <vector>
#include "Map.h"

Map::Map(Snake* snake, Food* food)
{
	this->snake = snake;
	this->food = food;

	this->size.x = 10;
	this->size.y = 10;

	init_map(size);
	set_snake();
	set_food();
}

Map::Map(Snake* snake, Food* food, Vec size)
{
	this->snake = snake;
	this->food = food;
	this->size = size;

	init_map(size);
	set_snake();
	set_food();
}

void
Map::init_map(Vec size)
{
	bmap.reserve(size.y);
	std::vector<MapBitType> line (size.x, MapBitType::EmptyBit);
	for (int y=0; y < size.y; y++)
	{
		bmap.push_back(line);
	}
}

void
Map::set_bit(Vec target, MapBitType bit)
{
	try{
		bmap.at(target.y).at(target.x) = bit;
	} catch (...)
	{
		return;
	}
}

void
Map::unset_snake()
{
	for(auto coord : snake->bmap)
		set_bit(coord, MapBitType::EmptyBit);
}

void
Map::set_snake()
{
	for(auto coord : snake->bmap)
		set_bit(coord, MapBitType::PlayerBit);
}

void
Map::unset_food()
{
	set_bit(food->coord, MapBitType::EmptyBit);
}

void
Map::set_food()
{
	set_bit(food->coord, MapBitType::FoodBit);
}

void
Map::update()
{
	unset_food();
	set_food();
	unset_snake();
	set_snake();
}
