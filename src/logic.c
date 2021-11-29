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
