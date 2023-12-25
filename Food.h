#include "Utils.h"

#ifndef __FOOD__
#define __FOOD__

class Food
{
	private:
		Vec rand_coord();
		int rand_range(int min, int max);
		Vec max = {10, 10};

	public:
		Vec coord;

	public:
		Food();
		Food(Vec max);
		void init();

};

#endif // !__FOOD__
