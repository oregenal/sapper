#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>

#define CELL_SIZE 25
#define COLUMNS 30
#define ROWS 30
#define SCREEN_WIDTH CELL_SIZE * COLUMNS
#define SCREEN_HEIGHT CELL_SIZE * ROWS

#define MARKED 0x80 //10000000b
#define MARK_MASK 0x7f //01111111b

enum state {
	RUNING_STATE = 0,
	GAME_OVER_STATE,
	WIN_STATE,
	QUIT_STATE
};

enum field {
	CLOSED_CELL = 0,
	OPENED_CELL,
	CLOSED_BOMB_CELL,
	OPENED_BOMB_CELL
};

typedef struct {
	int field[COLUMNS * ROWS];
	int state;
} game_t;

void game_render(SDL_Renderer *, const game_t *);

#endif //GAME_H_
