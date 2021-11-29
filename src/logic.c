#include "logic.h"

void mark_cell(SDL_MouseButtonEvent *button) {
	int x = button->x / CELL_SIZE;
	int y = button->y / CELL_SIZE;
	printf("Mark cell: {%d,%d} ass minen.\n", x, y);
}

void open_cell(SDL_MouseButtonEvent *button) {
	int x = button->x / CELL_SIZE;
	int y = button->y / CELL_SIZE;
	printf("Open {%d,%d} cell.\n", x, y);
}

void clic_on_cell(game_t *game, SDL_MouseButtonEvent *button)
{
	if(button->button == SDL_BUTTON_LEFT) {
		open_cell(button);
	} else if(button->button == SDL_BUTTON_RIGHT) {
		mark_cell(button);
	}
}

void randomize_field(game_t *game)
{
	unsigned int randseed = time(NULL);
	srand(randseed);

	for(int i = 0; i < COLUMNS * ROWS; ++i) {
		int res = rand() % 2;
		game->field[i] = res < 1 ? CLOSED_CELL : CLOSED_BOMB_CELL;
	}
}
