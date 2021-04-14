Conway's Game of Life implemented with SDL2 in C

To install make sure you have requisite SDL2 libraries, make and clang (if you prefer gcc simply amend the CC line of Makefile). My inclusion of gfxPrimitives is unnecessary and should probably be removed but most package managers include it in their standard repos; it's typically named SDL2_gfx.

git clone https://github.com/9ziggy9/gol.git

cd gol

make

./conway

Space will run/pause the time evolution and allow you to populate the grid. Escape to exit.

NOTES: I know the implementation of boundary conditions in count_neighbors() are very clunky. Perhaps it would be better to increase the field of the game outside the boundaries of the window and deal with them there.
