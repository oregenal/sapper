#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Fail to initialise SDL: %s.\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *window = SDL_CreateWindow("sapper", SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED, 
											SCREEN_WIDTH, 
											SCREEN_HEIGHT, 
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

	SDL_Event e;
	int quit = 0;
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					quit = 1;
					break;
				default: {}
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
