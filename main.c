#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to init SDL: %s.\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Surface *screen_surface = NULL;
	SDL_Window *window = NULL;

	window = SDL_CreateWindow("Sapper", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	if(window == NULL)
		exit(EXIT_FAILURE);

	screen_surface = SDL_GetWindowSurface(window);

	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format,
				255, 0, 0));
	SDL_UpdateWindowSurface(window);

	SDL_Delay(2000);

	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
