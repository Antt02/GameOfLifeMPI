#include <stdio.h>
#include "./game.h"
#include "./logic.h"
#include <mpi.h>

void click_on_cell(board_t* board, int row, int column)
{
  if (board->game_state == PAUSE_STATE) {
    if (board->cell_state[column][row] == DEAD) {
      board->cell_state[column][row] = ALIVE;
      printf("Cell (%d,%d) set to ALIVE.\n", column, row);
    }
    else if (board->cell_state[column][row] == ALIVE) {
      board->cell_state[column][row] = DEAD;
      printf("Cell (%d,%d) set to DEAD.\n", column, row);
    }
  }
  else if (board->game_state == RUNNING_STATE)
    printf("Game is running, hit space to pause and edit.\n");
}

void count_neighbors(boardRowInfo* board, unsigned char neighbors[rows][M])
{
	count_neighbors_spherical_world(board, neighbors);
}

void count_neighbors_spherical_world(boardRowInfo* board, unsigned char pop[rows][M])
{
	int i_prev, i_next, j_prev, j_next;
  // Clear neighbors
  for (int i = 0; i < board->ROW_NUM; i++) {
    for (int j = 0; j < board->COL_NUM; j++) {
      board->neighbors[i][j] = DEAD;
    }
  }
  // Inner cells
  //ara mateix això fa el càlcul de TOTES les rows de la sub board, hauriem de fer que en cas de ser fila 0 o COL_NUM - 1 ho miri
  //no de cell_state, sino de board->under/board->upper
  for (int i = 1; i < board->finalRow - board->startingRow-1; i++) {
    for (int j = 0; j < (board->COL_NUM); j++) {
      i_prev = (0 < i) ? i - 1 : board->finalRow - board->startingRow;;
      i_next = (i < board->finalRow - board->startingRow) ? i + 1 : 0;
      j_prev = (0 < j) ? j - 1 : board->COL_NUM-1;
      j_next = (j <  board->COL_NUM-1) ? j + 1 : 0;  
      
      //printf("[1]Calculating %i (%i, %i),  Searching(%i)(%i)(%i)(%i)",board->rank ,i+board->rank*5, j,i_prev+board->rank*5,i_next+board->rank*5,j_prev,j_next);
       


      if (board->cell_state[i_prev][j_prev] == ALIVE) {
        board->neighbors[i][j]++;
      }
      if (board->cell_state[i][j_prev] == ALIVE) {
        board->neighbors[i][j]++;
      }
      if (board->cell_state[i_next][j_prev] == ALIVE) {
        board->neighbors[i][j]++;
      }
      if (board->cell_state[i_prev][j] == ALIVE) {
        board->neighbors[i][j]++;
      }
      if (board->cell_state[i_next][j] == ALIVE) {
        board->neighbors[i][j]++;
      }
      if (board->cell_state[i_prev][j_next] == ALIVE) {
        board->neighbors[i][j]++;
      }
      if (board->cell_state[i][j_next] == ALIVE) {
        board->neighbors[i][j]++;
      }
      if (board->cell_state[i_next][j_next] == ALIVE) {
        board->neighbors[i][j]++;
      }
      //printf(" %i \n",board->neighbors[i][j]);
    }
  }

  for (int j = 0; j < (board->COL_NUM); j++) {
    int i=0;
    i_prev = (0 < i) ? i - 1 : board->finalRow - board->startingRow;;
    i_next = (i < board->finalRow - board->startingRow) ? i + 1 : 0;
    j_prev = (0 < j) ? j - 1 : board->COL_NUM-1;
    j_next = (j <  board->COL_NUM-1) ? j + 1 : 0;  
    //printf("[2]Calculating %i (%i, %i),  Searching(%i)(%i)(%i)(%i)",board->rank ,i+board->rank*board->ROW_NUM, j,i_prev+board->rank*board->ROW_NUM,i_next+board->rank*board->ROW_NUM,j_prev,j_next);
    

    if (board->upper[j_prev] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 1[%i,%i]",i,j);
    }
    if (board->cell_state[i][j_prev] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 2[%i,%i]",i,j_prev);
    }
    if (board->cell_state[i_next][j_prev] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 3[%i,%i]",i_next,j_prev);
    }
    if (board->upper[j] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 4[%i,%i]",i,j);
    }
    if (board->cell_state[i_next][j] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 5[%i,%i]",i_next,j);
    }
    if (board->upper[j_next] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 6[%i]",j_next);
    }
    if (board->cell_state[i][j_next] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 7[%i,%i]",i,j_next);
    }
    if (board->cell_state[i_next][j_next] == ALIVE) {
      board->neighbors[i][j]++;
      //printf(" 8[%i,%i]",i_next,j_next);
    }
    //printf(" %i \n",board->neighbors[i][j]);
      
  }
  for (int j = 0; j < (board->COL_NUM); j++) {
    
    int i = board->finalRow-board->startingRow-1;
    i_prev = (0 < i) ? i - 1 : board->finalRow - board->startingRow;;
    i_next = (i < board->finalRow - board->startingRow) ? i + 1 : 0;
    j_prev = (0 < j) ? j - 1 : board->COL_NUM-1;
    j_next = (j <  board->COL_NUM-1) ? j + 1 : 0;  
    //printf("[3]Calculating %i (%i, %i),  Searching(%i)(%i)(%i)(%i)",board->rank ,i+board->rank*5, j,i_prev+board->rank*5,i_next+board->rank*5,j_prev,j_next);
    

    
    if (board->cell_state[i_prev][j_prev] == ALIVE) {
      board->neighbors[i][j]++;
    }
    if (board->cell_state[i][j_prev] == ALIVE) {
      board->neighbors[i][j]++;
    }
    if (board->under[j_prev] == ALIVE) {
      board->neighbors[i][j]++;
    }
    if (board->cell_state[i_prev][j] == ALIVE) {
      board->neighbors[i][j]++;
    }
    if (board->under[j] == ALIVE) {
      board->neighbors[i][j]++;
    }
    if (board->cell_state[i_prev][j_next] == ALIVE) {
      board->neighbors[i][j]++;
    }
    if (board->cell_state[i][j_next] == ALIVE) {
      board->neighbors[i][j]++;
    }
    if (board->under[j_next] == ALIVE) {
      board->neighbors[i][j]++;
    }
    //printf(" %i \n",board->neighbors[i][j]);
  }
  return;
  
}

void count_neighbors_flat_world(board_t* board, unsigned char neighbors[D_COL_NUM][D_ROW_NUM])
{
  // Clear neighbors
  for (int i = 0; i < board->COL_NUM; i++) {
    for (int j = 0; j < board->ROW_NUM; j++) {
      neighbors[i][j] = DEAD;
    }
  }

  // Inner cells
  for (int i = 1; i < (board->COL_NUM - 1); i++) {
    for (int j = 1; j < (board->ROW_NUM - 1); j++) {
      if (board->cell_state[i-1][j-1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i][j-1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i+1][j-1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i-1][j] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i+1][j] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i-1][j+1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i][j+1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i+1][j+1] == ALIVE) {
        neighbors[i][j]++;
      }
    }
  }

  // Top cells
  for (int i = 1; i < (board->COL_NUM - 1); i++) {
    if (board->cell_state[i-1][0] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i-1][1] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i][1] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i+1][1] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i+1][0] == ALIVE) {
      neighbors[i][0]++;
    }
  }
  
  // Left cells
  for (int j = 1; j < (board->ROW_NUM - 1); j++) {
    if (board->cell_state[0][j-1] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[1][j-1] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[1][j] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[1][j+1] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[0][j+1] == ALIVE) {
      neighbors[0][j]++;
    }
  }

  // Bottom cells
  for (int i = 1; i < (board->COL_NUM - 1); i++) {
    if (board->cell_state[i-1][board->ROW_NUM - 1] == ALIVE) {
      neighbors[i][board->ROW_NUM - 1]++;
    }
    if (board->cell_state[i-1][board->ROW_NUM - 2] == ALIVE) {
      neighbors[i][board->ROW_NUM - 1]++;
    }
    if (board->cell_state[i][board->ROW_NUM - 2] == ALIVE) {
      neighbors[i][board->ROW_NUM - 1]++;
    }
    if (board->cell_state[i+1][board->ROW_NUM - 2] == ALIVE) {
      neighbors[i][board->ROW_NUM - 1]++;
    }
    if (board->cell_state[i+1][board->ROW_NUM - 1] == ALIVE) {
      neighbors[i][board->ROW_NUM - 1]++;
    }
  
  }
  // Right cells
  for (int j = 1; j < (board->ROW_NUM - 1); j++) {
    if (board->cell_state[board->COL_NUM - 1][j-1] == ALIVE) {
      neighbors[board->COL_NUM - 1][j]++;
    }
    if (board->cell_state[board->COL_NUM - 2][j-1] == ALIVE) {
      neighbors[board->COL_NUM - 1][j]++;
    }
    if (board->cell_state[board->COL_NUM - 2][j] == ALIVE) {
      neighbors[board->COL_NUM - 1][j]++;
    }
    if (board->cell_state[board->COL_NUM - 2][j+1] == ALIVE) {
      neighbors[board->COL_NUM - 1][j]++;
    }
    if (board->cell_state[board->COL_NUM - 1][j+1] == ALIVE) {
      neighbors[board->COL_NUM - 1][j]++;
    }
  }

  // Top left corner
  if (board->cell_state[1][0] == ALIVE)
    neighbors[0][0]++;
  if (board->cell_state[1][1] == ALIVE)
    neighbors[0][0]++;
  if (board->cell_state[0][1] == ALIVE)
    neighbors[0][0]++;

  // Bottom left corner
  if (board->cell_state[1][board->ROW_NUM - 1] == ALIVE)
    neighbors[0][board->ROW_NUM - 1]++;
  if (board->cell_state[1][board->ROW_NUM - 2] == ALIVE)
    neighbors[0][board->ROW_NUM - 1]++;
  if (board->cell_state[0][board->ROW_NUM - 2] == ALIVE)
    neighbors[0][board->ROW_NUM - 1]++;

  // Bottom right corner
  if (board->cell_state[board->COL_NUM - 2][board->ROW_NUM - 1] == ALIVE)
    neighbors[board->COL_NUM - 1][board->ROW_NUM - 1]++;
  if (board->cell_state[board->COL_NUM - 1][board->ROW_NUM - 2] == ALIVE)
    neighbors[board->COL_NUM - 1][board->ROW_NUM - 1]++;
  if (board->cell_state[board->COL_NUM - 2][board->ROW_NUM - 2] == ALIVE)
    neighbors[board->COL_NUM - 1][board->ROW_NUM - 1]++;

  // Top left corner
  if (board->cell_state[board->COL_NUM - 1][1] == ALIVE)
    neighbors[board->COL_NUM - 1][0]++;
  if (board->cell_state[board->COL_NUM - 2][1] == ALIVE)
    neighbors[board->COL_NUM - 1][0]++;
  if (board->cell_state[board->COL_NUM - 2][0] == ALIVE)
    neighbors[board->COL_NUM - 1][0]++;
}

void evolve(boardRowInfo* board, const unsigned char pop[rows][M]){
  for (int i = 0; i < board->ROW_NUM; i++) {
      for (int j = 0; j < board->COL_NUM; j++) {
        // underopulation case
        if (board->neighbors[i][j] < 2)
          board->cell_state[i][j] = DEAD;
        // birth case
        else if (board->neighbors[i][j] == 3)
          board->cell_state[i][j] = ALIVE;
        // overpopulation case
        else if (board->neighbors[i][j] > 3)
          board->cell_state[i][j] = DEAD;
        // survival case is implicit, as only cells with 2 or 3 neighbors will
        // survive.
        //printf(" [%i,%u,(%i,%i)] ",board->neighbors[i][j],board->cell_state[i][j],i,j);
      }
      //printf("\n");
  }
}
  


/******************************************************************************/

void life_read (char *filename, board_t* board)

/******************************************************************************/
/*
  Purpose:
    LIFE_READ reads a file to a grid.

  Parameters:

    Input, char *OUTPUT_FILENAME, the input file name.

*/

{
  FILE *input_unit;
/*
  input the file.
*/
  input_unit = fopen ( filename, "rt" );
  if (input_unit==NULL)
    perror("Reading input file:");
/*
  Read the data.
*/
  for (int i = 0; i < board->COL_NUM; i++) {
    for (int j = 0; j < board->ROW_NUM; j++) {
      fscanf ( input_unit, "%hhu", &(board->cell_state[i][j]) );
    }
  }
/*
  Close the file.
*/
  fclose ( input_unit );

  return;
}


/******************************************************************************/

void life_write ( char *output_filename, board_t* board)

/******************************************************************************/
/*
  Purpose:

    LIFE_WRITE writes a boad to a file.

  Parameters:

    Input, char *OUTPUT_FILENAME, the output file name.

*/
{
  FILE *output_unit;
/*
  Open the file.
*/
  output_unit = fopen ( output_filename, "wt" );
/*
  Write the data.
*/
  for (int i = 0; i < board->COL_NUM; i++) {
    for (int j = 0; j < board->ROW_NUM; j++) {
      fprintf ( output_unit, " %hhu", board->cell_state[i][j] );
    }
    fprintf ( output_unit, "\n" );
  }
/*
  Close the file.
*/
  fclose ( output_unit );

  return;
}
/******************************************************************************/

double r8_uniform_01 ( int *seed )

/******************************************************************************/
/*
  Purpose:

    R8_UNIFORM_01 returns a pseudorandom R8 scaled to [0,1].

  Discussion:

    This routine implements the recursion

      seed = 16807 * seed mod ( 2^31 - 1 )
      r8_uniform_01 = seed / ( 2^31 - 1 )

    The integer arithmetic never requires more than 32 bits,
    including a sign bit.

    If the initial seed is 12345, then the first three computations are

      Input     Output      R8_UNIFORM_01
      SEED      SEED

         12345   207482415  0.096616
     207482415  1790989824  0.833995
    1790989824  2035175616  0.947702

  Parameters:

    Input/output, int *SEED, the "seed" value.  Normally, this
    value should not be 0.  On output, SEED has been updated.

    Output, double R8_UNIFORM_01, a new pseudorandom variate, strictly between
    0 and 1.
*/
{
  int i4_huge = 2147483647;
  int k;
  double r;

  k = *seed / 127773;

  *seed = 16807 * ( *seed - k * 127773 ) - k * 2836;

  if ( *seed < 0 )
  {
    *seed = *seed + i4_huge;
  }

  r = ( ( double ) ( *seed ) ) * 4.656612875E-10;

  return r;
}

/******************************************************************************/

void life_init (board_t* board, double prob, int *seed )

/******************************************************************************/
/*
  Purpose:

    LIFE_INIT initializes the life grid.

  Parameters:

    Input, double PROB, the probability that a grid cell
    should be alive.

    Input/output, int *SEED, a seed for the random
    number generator.

*/
{
  double r;

  for (int i = 0; i < board->COL_NUM; i++) {
    for (int j = 0; j < board->ROW_NUM; j++) {
         board->cell_state[i][j] = 0;
    }
  }

  for (int i = 0; i < board->COL_NUM; i++) {
    for (int j = 0; j < board->ROW_NUM; j++) 
    {
        r = r8_uniform_01 ( seed );
        if ( r <= prob )
        {
           board->cell_state[i][j] = 1;
        }
    } 
  }
}
