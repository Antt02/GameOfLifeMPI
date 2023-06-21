#include <SDL2/SDL.h>

#include "./game.h"
#include "./render.h"
#include "./logic.h"

bool Graphical_Mode = false;
int rows, M;

void render_board(SDL_Renderer* renderer, boardRowInfo *board,
                  unsigned char neighbors[rows][M], board_t* fullBoard)
{ 
  switch(fullBoard->game_state) { 
    case RUNNING_STATE:
      if (Graphical_Mode&&board->rank==0){
      	render_running_state(renderer, board, fullBoard);
      }
      count_neighbors(board, neighbors);
      evolve(board, neighbors);
      break;
    case PAUSE_STATE:
      if (Graphical_Mode&&board->rank==0)
        render_pause_state(renderer, board, fullBoard);
      break;
    default: {}
  }
}

void render_running_state(SDL_Renderer *renderer, boardRowInfo *board, board_t *fullBoard)
{
  int pos_x = 0;
  int pos_y = 0;

  for (int i = 0; i < board->COL_NUM; i++) {
    for (int j = 0; j < board->ROW_NUM; j++) {
      pos_x = i * fullBoard->CELL_WIDTH;
      pos_y = j * fullBoard->CELL_HEIGHT;
      if (board->cell_state[i][j] == ALIVE &&board->rank==0)
        render_square(renderer, pos_x, pos_y, fullBoard);
    }
  }
}

void render_pause_state(SDL_Renderer *renderer, boardRowInfo *board, board_t *fullBoard)
{
  int pos_x = 0;
  int pos_y = 0;

  for (int i = 0; i < board->COL_NUM; i++) {
    for (int j = 0; j < board->ROW_NUM; j++) {
      pos_x = i * fullBoard->CELL_WIDTH;
      pos_y = j * fullBoard->CELL_HEIGHT;
      if (board->cell_state[i][j] == ALIVE&&board->rank==0)
        pause_square(renderer, pos_x, pos_y, fullBoard);
    }
  }
}

void render_square(SDL_Renderer *renderer, int pos_x, int pos_y, board_t* board)
{
  SDL_Rect cell;
  cell.x = pos_x;
  cell.y = pos_y;
  cell.w = board->CELL_WIDTH - 1;
  cell.h = board->CELL_HEIGHT - 1;
  SDL_SetRenderDrawColor(renderer, 142, 192, 124, 1);
  SDL_RenderFillRect(renderer, &cell);
}

void pause_square(SDL_Renderer *renderer, int pos_x, int pos_y, board_t* board)
{
  SDL_Rect cell;
  cell.x = pos_x;
  cell.y = pos_y;
  cell.w = board->CELL_WIDTH - 1;
  cell.h = board->CELL_HEIGHT - 1;
  SDL_SetRenderDrawColor(renderer, 146, 131, 116, 1);
  SDL_RenderFillRect(renderer, &cell);
}


