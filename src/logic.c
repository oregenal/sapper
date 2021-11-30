#include "logic.h"

int bomb_counter;

static void mark_cell(game_t *game, int x, int y) {
	if(game->field[x + y * COLUMNS] != OPENED_CELL)
		game->field[x + y * COLUMNS] ^= MARKED;
}

static void open_cell(game_t *game, int x, int y) {
	switch(game->field[x + y * COLUMNS]) {
		case CLOSED_CELL:
			game->field[x + y * COLUMNS] = OPENED_CELL;
			break;
		case CLOSED_BOMB_CELL:
			game->state = GAME_OVER_STATE;
			break;
		default: {}
	}
}

void clic_on_cell(game_t *game, SDL_MouseButtonEvent *button)
{
	int x = button->x / CELL_SIZE;
	int y = button->y / CELL_SIZE;

	switch(game->state) {
		case RUNING_STATE:
			if(button->button == SDL_BUTTON_LEFT) {
				open_cell(game, x, y);
			} else if(button->button == SDL_BUTTON_RIGHT) {
				mark_cell(game, x, y);
			}
			break;
		case GAME_OVER_STATE:
			game->state = RUNING_STATE;
			randomize_field(game);
			break;
		case WIN_STATE:
			game->state = RUNING_STATE;
			randomize_field(game);
			break;
		default: {}
	}
}

void randomize_field(game_t *game)
{
	unsigned int randseed = time(NULL);
	srand(randseed);
	bomb_counter = 0;

	for(int i = 0; i < COLUMNS * ROWS; ++i) {
		int res = rand() % 5;
		if(res < 4) {
			game->field[i] = CLOSED_CELL;
			++bomb_counter;
		} else {
			game->field[i] = CLOSED_BOMB_CELL;
		}
	}
}
