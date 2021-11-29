#include "game.h"

static void render_greed(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 171, 171, 171, SDL_ALPHA_OPAQUE);
	for(int i = 0; i < SCREEN_WIDTH + 1; i += CELL_SIZE) {
		SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
	}
	for(int i = 0; i < SCREEN_HEIGHT + 1; i += CELL_SIZE) {
		SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
	}
}

void render_bomb_cell(SDL_Renderer *renderer, int i)
{
	SDL_Rect rect = {
		.x = i % COLUMNS * CELL_SIZE + 5,
		.y = i / COLUMNS * CELL_SIZE + 5,
		.w = CELL_SIZE - 10,
		.h = CELL_SIZE - 10
	};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);
}

void game_render(SDL_Renderer *renderer, const game_t *game)
{
	render_greed(renderer);

	for(int i = 0; i < COLUMNS * ROWS; ++i) {
		switch(game->field[i]) {
			case CLOSED_CELL:
				break;
			case CLOSED_BOMB_CELL:
				render_bomb_cell(renderer, i);
				break;
			default: {}
		}
	}
}
