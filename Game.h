#include <string>
#include "Curse.h"
#include "Map.h"
#include "Snake.h"
#include "Food.h"

#ifndef __GAME__
#define __GAME__


enum CollisionType {FoodCollision, BodyCollision, BorderCollision, NoCollision };
class Game
{
	private:
	private:
		Map* game_map;
		Food* food;
		Snake* snake;
		CurseWindow* screen;

	private:
		CollisionType check_collision();
		void move_snake();
		void draw_map();
		void place_food();
	public:
		Game();
		~Game();
		void run();
};

#endif // !__GAME__
