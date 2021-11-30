#include "game.h"

SDL_Point one[] = {
	{  CELL_SIZE / 2, 5 },
	{  CELL_SIZE / 2, CELL_SIZE - 5 }
};

SDL_Point two[] = {
	{ 5, 5 },
	{ CELL_SIZE - 5, 5 },
	{ CELL_SIZE - 5, CELL_SIZE / 2 },
	{ 5, CELL_SIZE - 5 },
	{ CELL_SIZE - 5, CELL_SIZE - 5 }
};

SDL_Point three[] = {
	{ 5, 5 },
	{ CELL_SIZE - 5, 5 },
	{ CELL_SIZE / 2, CELL_SIZE / 2 },
	{ CELL_SIZE - 5, CELL_SIZE - 5 },
	{ 5, CELL_SIZE - 5 }
};

SDL_Point four[] = {
	{ 5, 5 },
	{ 5, CELL_SIZE / 2 },
	{ CELL_SIZE - 5 , CELL_SIZE / 2 },
	{ CELL_SIZE - 5, 5 },
	{ CELL_SIZE - 5, CELL_SIZE - 5 }
};

SDL_Point five[] = {
	{ CELL_SIZE - 5, 5 },
	{ 5, 5 },
	{ 5 , CELL_SIZE / 2 },
	{ CELL_SIZE - 5 , CELL_SIZE / 2 },
	{ CELL_SIZE - 5, CELL_SIZE - 5 },
	{ 5, CELL_SIZE - 5 }
};

SDL_Point six[] = {
	{ CELL_SIZE - 5, 5 },
	{ 5, 5 },
	{ 5 , CELL_SIZE - 5 },
	{ CELL_SIZE - 5 , CELL_SIZE - 5 },
	{ CELL_SIZE - 5, CELL_SIZE / 2 },
	{ 5, CELL_SIZE / 2 }
};

SDL_Point seven[] = {
	{  5 , 5 },
	{  CELL_SIZE - 5, 5 },
	{  CELL_SIZE / 2, CELL_SIZE - 5 }
};

SDL_Point eight[] = {
	{ CELL_SIZE - 5, CELL_SIZE / 2 },
	{ CELL_SIZE - 5, 5 },
	{ 5, 5 },
	{ 5 , CELL_SIZE - 5 },
	{ CELL_SIZE - 5 , CELL_SIZE - 5 },
	{ CELL_SIZE - 5, CELL_SIZE / 2 },
	{ 5, CELL_SIZE / 2 }
};

void draw_number(SDL_Renderer *renderer, int i, SDL_Point number[], int size)
{
	SDL_Point result[size];
	for(int j = 0; j < size; ++j) {
		result[j].x = number[j].x + i % COLUMNS * CELL_SIZE;
		result[j].y = number[j].y + i / COLUMNS * CELL_SIZE;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(renderer, result, size);
}

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

void render_marked_cell(SDL_Renderer *renderer, int i)
{
	SDL_Rect rect = {
		.x = i % COLUMNS * CELL_SIZE + 5,
		.y = i / COLUMNS * CELL_SIZE + 5,
		.w = CELL_SIZE - 10,
		.h = CELL_SIZE - 10
	};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);
}

void render_open_cell(SDL_Renderer *renderer, int i, const game_t *game)
{
	SDL_Rect rect = {
		.x = i % COLUMNS * CELL_SIZE + 1,
		.y = i / COLUMNS * CELL_SIZE + 1,
		.w = CELL_SIZE - 2,
		.h = CELL_SIZE - 2
	};
	SDL_SetRenderDrawColor(renderer, 191, 191, 191, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);

	int neibours = 0;
	int x = i % COLUMNS;
	int y = i / COLUMNS;

	for(int col = 0; col < 3; ++col) {
		for(int row = 0; row < 3; ++row) {
			int cell_status = game->field[(x - 1 + col) + (y - 1 + row) * COLUMNS];
			if(cell_status == CLOSED_BOMB_CELL || (MARK_MASK & cell_status) == CLOSED_BOMB_CELL)
				++neibours;
		}
	}

	switch(neibours) {
		case 0:
			break;
		case 1:
			draw_number(renderer, i, one, sizeof(one) / sizeof(one[0]));
			break;
		case 2:
			draw_number(renderer, i, two, sizeof(two) / sizeof(two[0]));
			break;
		case 3:
			draw_number(renderer, i, three, sizeof(three) / sizeof(three[0]));
			break;
		case 4:
			draw_number(renderer, i, four, sizeof(four) / sizeof(four[0]));
			break;
		case 5:
			draw_number(renderer, i, five, sizeof(five) / sizeof(five[0]));
			break;
		case 6:
			draw_number(renderer, i, six, sizeof(six) / sizeof(six[0]));
			break;
		case 7:
			draw_number(renderer, i, seven, sizeof(seven) / sizeof(seven[0]));
			break;
		case 8:
			draw_number(renderer, i, eight, sizeof(eight) / sizeof(eight[0]));
		default: {}
	}

}

void game_render(SDL_Renderer *renderer, const game_t *game)
{
	render_greed(renderer);

	for(int i = 0; i < COLUMNS * ROWS; ++i) {
		switch(game->field[i]) {
			case MARKED:
				render_marked_cell(renderer, i);
				break;
			case (MARKED | CLOSED_BOMB_CELL):
				render_marked_cell(renderer, i);
				break;
			case CLOSED_CELL:
				break;
			case CLOSED_BOMB_CELL:
				break;
			case OPENED_CELL:
				render_open_cell(renderer, i, game);
				break;
			default: {}
		}
	}
}
