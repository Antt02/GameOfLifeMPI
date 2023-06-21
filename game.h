#ifndef GAME_H_
#define GAME_H_

#define D_COL_NUM 4000 // size of game universe, only windowed is shown.
#define D_ROW_NUM 4000
#define ALIVE 1
#define DEAD 0

#define RUNNING_STATE 0
#define PAUSE_STATE 1

//#define GRAPHICAL_MODE
typedef struct {
  unsigned char cell_state[D_COL_NUM][D_ROW_NUM];
  int game_state;
  int COL_NUM;
  int ROW_NUM;  
  int CELL_WIDTH;
  int CELL_HEIGHT;
} board_t;

typedef struct {
  unsigned char cell_state[D_COL_NUM][D_ROW_NUM]; //submatrix with our scope of the real board to calculate
  unsigned char upper[D_ROW_NUM], under[D_ROW_NUM]; //arrays containing extra rows needed
  int game_state; 
  int COL_NUM; //nº of columns (always the same)
  int ROW_NUM; //nº of rows assigned
  int startingRow; //first row from which to check
  int finalRow; //last row to check
  int rank;
} boardRowInfo;

#endif // GAME_H_
