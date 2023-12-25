#include <random>

#include "Utils.h"
#include "Food.h"

Food::Food() {}

Food::Food(Vec max) { this->max = max; }

int
Food::rand_range(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> dist(min,max-1);
	return dist(rng);
}

Vec
Food::rand_coord()
{
	return {rand_range(0, this->max.y), rand_range(0, this->max.x)};
}

void
Food::init()
{
	do {
		coord = rand_coord();
	} while (coord.y > max.y || coord.x > max.x);
}
