#include "Snake.cpp"
#include "Game.cpp"
#include "Screen.cpp"

struct GameSymbol {
	const static char CharSnake = 'o';
	const static char CharFood = '$';
	const static char CharEmpty = '_';
} ;

// width and heght of th map and ncurses window
const size_t x_max = 30;
const size_t y_max = 15;

// draws everything on the ncurses window
void
draw_game(CursesWindow* window, Game* game)
{
	for ( size_t cell_y=0; cell_y < game->max_y; cell_y++ ) {
		for ( size_t cell_x=0 ; cell_x < game->max_x; cell_x++ ) {
			switch(*game->get_cell(cell_x, cell_y)) {
				case CellEmpty:
					window->printout(GameSymbol::CharEmpty, cell_x, cell_y);
					break;
				case CellSnake:
					window->printout(GameSymbol::CharSnake, cell_x, cell_y);
					break;
				case CellFood:
					window->printout(GameSymbol::CharFood, cell_x, cell_y);
					break;
				default:
					continue;
			}
		}
	}

}

int
main()
{
	// delay per iteration of 'frame'
	int ms_per_frame = 130;

	vector<COORD> starting_coord = { {1, 3}, {1, 2}, {1, 1} };
	Snake snake = Snake(starting_coord, GoingRight);

	Game game = Game(x_max, y_max, &snake);
	CursesWindow curse_w = CursesWindow(x_max, y_max, 0, 0);

	while(true) {
		try {
			// resets the game game and redraw it
			redraw_screen:
				game.reset_map();
				draw_game(&curse_w, &game);

			// get the keyboard input
			switch(curse_w.get_keypress(true, true)) {
				case KEY_UP:
					game.move_snake(GoingUp);
					// go to redraw directly
					// to minimize input delay
					goto redraw_screen;
				case KEY_DOWN:
					game.move_snake(GoingDown);
					goto redraw_screen;
				case KEY_LEFT:
					game.move_snake(GoingLeft);
					goto redraw_screen;
				case KEY_RIGHT:
					game.move_snake(GoingRight);
					goto redraw_screen;
				default:
					game.move_snake_to(game.snake->head_direction);
			}

			napms(ms_per_frame);

		} catch (SnakeIsDead) {
			break;
		}
	}

	return 0;
}
