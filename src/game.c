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

void game_render(SDL_Renderer *renderer, const game_t *game)
{
	render_greed(renderer);
}
