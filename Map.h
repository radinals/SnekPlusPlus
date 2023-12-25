#include <vector>

#include "Snake.h"
#include "Food.h"
#include "Utils.h"

#ifndef __MAP__
#define __MAP__

enum MapBitType { EmptyBit, PlayerBit, FoodBit };

class Map
{
	public:
		std::vector<std::vector<MapBitType>> bmap;
		Vec size;

	private:
		Vec def_size {10,10}; // default is 10x10
		Snake* snake;
		Food* food;

	// methods
	private:
		void set_bit(Vec target, MapBitType bit);

		void init_map(Vec size);
	public:
		void unset_snake();
		void set_snake();

		void set_food();
		void unset_food();

	public:
		Map(Snake* snake, Food* food);
		Map(Snake* snake, Food* food, Vec size);
		void update();
};

#endif // !__MAP__
