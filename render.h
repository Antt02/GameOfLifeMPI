#ifndef RENDER_H_
#define RENDER_H_

#include <stdbool.h>

extern bool Graphical_Mode;
extern int rows, M;

void render_board(SDL_Renderer* renderer, boardRowInfo *board,
                  unsigned char neighbors[rows][M], board_t* fullBoard);

void render_running_state(SDL_Renderer *renderer, boardRowInfo *board, board_t *fullBoard);

void render_square(SDL_Renderer *renderer, int pos_x, int pos_y,
                  board_t* board);

void render_pause_state(SDL_Renderer *renderer, boardRowInfo *board, board_t *fullBoard);

void pause_square(SDL_Renderer *renderer, int pos_x, int pos_y,
                  board_t* board);

#endif // RENDER_H_

