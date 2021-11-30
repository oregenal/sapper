#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "logic.h"

int main(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Fail to initialise SDL: %s.\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *window = SDL_CreateWindow("sapper", SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED, 
											SCREEN_WIDTH + 1, 
											SCREEN_HEIGHT + 1, 
											SDL_WINDOW_SHOWN);
	if(window == NULL) {
		SDL_Log("SDL_CeateWindow fail: %s.\n" , SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
												SDL_RENDERER_ACCELERATED | 
												SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL) {
		SDL_Log("SDL_Renderer fail: %s.\n" , SDL_GetError());
		SDL_DestroyWindow(window);
		exit(EXIT_FAILURE);
	}

	game_t game;
	randomize_field(&game);
	game.state = RUNING_STATE;

	SDL_Event e;
	while(game.state != QUIT_STATE) {
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					game.state = QUIT_STATE;
					break;
				case SDL_MOUSEBUTTONDOWN:
					clic_on_cell(&game, &e.button);
					break;
				default: {}
			}
		}

		SDL_SetRenderDrawColor(renderer, 56, 53, 53, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		game_render(renderer, &game);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
