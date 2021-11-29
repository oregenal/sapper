#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>

#define CELL_SIZE 50
#define COLUMNS 10
#define ROWS 10
#define SCREEN_WIDTH CELL_SIZE * COLUMNS
#define SCREEN_HEIGHT CELL_SIZE * ROWS

enum state {
	RUNING_STATE = 0,
	GAME_OVER_STATE,
	WIN_STATE,
	QUIT_STATE
};

typedef struct {
	int field[COLUMNS * ROWS];
	int state;
} game_t;

void game_render(SDL_Renderer *, const game_t *);

#endif //GAME_H_
