#include <random>

#include "Utils.h"
#include "Food.h"

Food::Food() { max.x = 10; max.y = 10; }

Food::Food(Vec max) { this->max = max; }

int
Food::rand_range(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min,max);
	return dist(gen);
}

void
Food::init()
{
	coord.x=(rand_range(0, max.x));
	coord.y=(rand_range(0, max.y));
}
