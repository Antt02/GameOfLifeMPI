#ifndef GAME_H_
#define GAME_H_

#define TICKS 50000
#define SIZE 2
#define SCREEN_WIDTH (SIZE * 640)
#define SCREEN_HEIGHT (SIZE * 480)
#define COL_NUM (SIZE * 40)
#define ROW_NUM ( 3*COL_NUM / 4 )
#define CELL_WIDTH ( SCREEN_WIDTH / COL_NUM )
#define CELL_HEIGHT ( SCREEN_HEIGHT / ROW_NUM )
#define ALIVE 1
#define DEAD 0

#define RUNNING_STATE 0
#define PAUSE_STATE 1

typedef struct {
  int cell_state[COL_NUM][ROW_NUM];
  int game_state;
} board_t;

#endif // GAME_H_
