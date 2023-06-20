#ifndef LOGIC_H_
#define LOGIC_H_
extern int rows, M;

void click_on_cell(board_t* board, int row, int column);

void count_neighbors(boardRowInfo* board, unsigned char neighbors[rows][M]);

void count_neighbors_spherical_world(boardRowInfo* board, unsigned char neighbors[rows][M]);

void count_neighbors_flat_world(board_t* board, unsigned char neighbors[D_COL_NUM][D_ROW_NUM]);

void evolve(boardRowInfo* board, const unsigned char neighbors[rows][M]);

void life_read ( char *filename, board_t* board);

void life_write ( char *output_filename, board_t* board);

double r8_uniform_01 ( int *seed );

void life_init (board_t* board, double prob, int *seed );

#endif // LOGIC_H_
