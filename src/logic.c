#include "logic.h"

void mark_cell(game_t *game, int x, int y) {
	if(game->field[x + y * COLUMNS] != OPENED_CELL)
		game->field[x + y * COLUMNS] ^= MARKED;
}

void open_cell(game_t *game, int x, int y) {
	if(game->field[x + y * COLUMNS] == CLOSED_BOMB_CELL) {
	printf("BOOM!! In {%d,%d} cell.\n", x, y);
	} else if (game->field[x + y * COLUMNS] == CLOSED_CELL){
		game->field[x + y * COLUMNS] = OPENED_CELL;
	}
}

void clic_on_cell(game_t *game, SDL_MouseButtonEvent *button)
{
	int x = button->x / CELL_SIZE;
	int y = button->y / CELL_SIZE;

	if(button->button == SDL_BUTTON_LEFT) {
		open_cell(game, x, y);
	} else if(button->button == SDL_BUTTON_RIGHT) {
		mark_cell(game, x, y);
	}
}

void randomize_field(game_t *game)
{
	unsigned int randseed = time(NULL);
	srand(randseed);

	for(int i = 0; i < COLUMNS * ROWS; ++i) {
		int res = rand() % 3;
		game->field[i] = res < 2 ? CLOSED_CELL : CLOSED_BOMB_CELL;
	}
}
