#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <mpi.h>

#ifndef NO_SDL
#include <SDL2/SDL.h>
#endif

#include "./game.h"
#include "./logic.h"
#include "./render.h"

void usage(void)
{
	printf("\nUsage: conway [-g] [-w weight] [-h heigt] [-i input_board_file] [-o output_board_file] [-e End_time] [-t ticks] [-c cell_size] \n\n-t\tSet number of ticks in microseconds.\n\t");
	printf("\n -g\tEnable graphical mode.\n\n");
	printf("\n -w\tSet board weight.\n\n");
	printf("\n -h\tSet board height.\n\n");
	printf("\n -i\tInput board file.\n\n");
	printf("\n -o\tOutput board file.\n\n");
	printf("\n -e\tNumber of simulation iterations.\n\n");
	printf("Enter extremely low values at own peril.\n\tRecommended to stay in 30000-100000 range.\n\tDefaults to 50000.\n\n");
	printf("\n -c\tSet cell size to tiny, small, medium or large.\n\tDefaults to small.\n\n");
}

int main(int argc, char** argv)
{
	// Set default rate of ticks.
	int TICKS = 50000;
	bool LoadFile = false, SaveFile = false; 
	int EndTime=-1;
	char input_file[256],output_file[256];
	
#ifndef NO_SDL	
	// Graphics.
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int PEEPER_SIZE;
	int PEEPER_OFFSET;	
	SDL_Event e;
	SDL_Rect peeper; // In future may take values from event loop.
	SDL_Window *window;
	SDL_Renderer *renderer;

	// Set initial window scaling factor
	float SCALE = 0.5;

	// This will store window dimension information.
	int window_width;
	int window_height;
#endif

	board_t *board = (board_t*) malloc(sizeof(board_t));
	if (board==NULL) {
		fprintf(stderr,"Error reserving board memory %lf Kbytes",sizeof(board_t)/1024.0);
		exit(1);
	}
	// Configure board initial state.
	board->game_state = RUNNING_STATE;
	board->CELL_WIDTH = 4; // Reasonable default size
	board->CELL_HEIGHT = 4;
	board->COL_NUM = D_COL_NUM;
	board->ROW_NUM = D_ROW_NUM;

	for (int i = 0; i < board->COL_NUM; i++) {
		for (int j = 0; j < board->ROW_NUM; j++){
			board->cell_state[i][j] = DEAD;
		}	
	}

	// Command line options.
	int opt;
	while((opt = getopt(argc, argv, "t:c:h:i:o:w:H:e:g")) != -1) {
		switch (opt) {
			case 't':
				TICKS = atoi(optarg);
				break;
			case 'i':
				strcpy(input_file,optarg);
				LoadFile = true;
				break;
			case 'o':
				SaveFile=true;
				strcpy(output_file,optarg);
				printf("Output Board file %s.\n",optarg);
				break;
			case 'w':
				board->COL_NUM = atoi(optarg);
				printf("Board width %d.\n",board->COL_NUM);
				break;	
			case 'h':
				board->ROW_NUM = atoi(optarg);
				printf("Board height %d.\n",board->ROW_NUM);
				break;	
			case 'e':
				printf("End Time: %s.\n",optarg);
				EndTime = atoi(optarg);
				break;	 	
			case 'g':
				Graphical_Mode = true;
				break;
			case 'c':
				if (strcmp(optarg,"tiny") == 0) {
					board->CELL_WIDTH = 2;
					board->CELL_HEIGHT = 2;
				}	
				else if (strcmp(optarg,"small") == 0) {
					board->CELL_WIDTH = 5;
					board->CELL_HEIGHT = 5;
				}	
				else if (strcmp(optarg,"medium") == 0) {
					board->CELL_WIDTH = 10;
					board->CELL_HEIGHT = 10;
				}
				else if (strcmp(optarg,"large") == 0) {
					board->CELL_WIDTH = 25;
					board->CELL_HEIGHT = 25;	
				}
				break;
			case 'H':
				usage();
				exit(EXIT_SUCCESS);
				break;
			case '?':
				if ((optopt == 't' || optopt == 's' || optopt == 'c' || optopt == 'i' || optopt == 'o' || optopt == 'w' || optopt == 'h' || optopt == 'e' ))
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				printf("Setting default options.\n");
				usage();
				break;
			default:
				printf("Setting default options.\n");
				usage();
				break;
		}
	}

	if (LoadFile) 	
	{
		printf("Loading Board file %s.\n",input_file);
		life_read(input_file, board);
	}
	else
	{ // Rando, init file
			printf("Init Cells\n");fflush(stdout);
			double prob = 0.20;
			int seed = 123456789;
			life_init(board, prob, &seed);
	}
	//iniciem MPI
	int rank, size;
	MPI_Init(&argc, &argv);
	//MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN); // -> for -debug option
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

#ifndef NO_SDL 
	if (Graphical_Mode&&rank==0) 
	{
		// Initialize SDL subsystem
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
			return EXIT_FAILURE;
		}

		// Grab display dimensions.
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);

		// Set and scale window dimensions.
		SCREEN_WIDTH = DM.w;
		SCREEN_HEIGHT = DM.h;
		SCREEN_WIDTH = SCREEN_WIDTH * SCALE ;
		SCREEN_HEIGHT = SCREEN_HEIGHT * SCALE ;

		// An SDL_Rect type called peeper whose scale is fed into
		// SDL_RenderSetViewport() very shortly must also include
		// an offset to ensure boundary conditions along x=0 and
		// y=0 are sufficiently out of frame.
		PEEPER_SIZE = 10 * SCREEN_WIDTH; // Should be sufficient.
		PEEPER_OFFSET = PEEPER_SIZE / 4;
		
		PEEPER_SIZE = 10 * SCREEN_WIDTH; // Should be sufficient.
		PEEPER_OFFSET = PEEPER_SIZE / 4;

		// Create window
		window = SDL_CreateWindow("Conway's Game",
											1, 1,
											SCREEN_WIDTH, SCREEN_HEIGHT,
											SDL_WINDOW_SHOWN);
		if (window == NULL) {
			fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
			return EXIT_FAILURE;
		}

		// Create renderer
		renderer = SDL_CreateRenderer(window, -1,
													SDL_RENDERER_ACCELERATED |
													SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			SDL_DestroyWindow(window);
			fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
			return EXIT_FAILURE;
		}
	}
#endif
	if(rank==0){printf("Start Simulation.\n");fflush(stdout);}
	bool quit = false;
	int Iteration=0;
	
	
	//repartició de rows: a cadascú se li assigna un tròs, i en cas que estigui desbalancejat, el restant s'assigna al final
	int M = board->COL_NUM;
	int chunk = M/size;
	int startRow=rank*chunk;
	int finalRow=startRow+chunk;
	if (rank == size-1){
		finalRow += M%size; 
	}
	
	//dades necessaries per que cadascú es generi el seu tròs de board
	boardRowInfo *myBoard = (boardRowInfo*) malloc(sizeof(boardRowInfo));
	int rows=finalRow-startRow;
	unsigned char neighbors[rows][M];
	int x, y;
	printf("Rank %i: from %i to %i (%i rows)\n", rank, startRow, finalRow, rows);
	
	myBoard->ROW_NUM = rows;
	myBoard->COL_NUM = M;
	myBoard->startingRow = startRow;
	myBoard->finalRow = finalRow-1;
	myBoard->game_state=board->game_state;
	myBoard->rank=rank;
	
	//definició objecte tipus vector per enviar les rows extra
	MPI_Datatype boardRow;
	MPI_Status st;
	MPI_Type_vector(1, M, sizeof(unsigned char)*M, MPI_UNSIGNED_CHAR, &boardRow); //matriz
	MPI_Type_commit(&boardRow);
	MPI_Datatype boardRows;
	MPI_Type_vector(rows, M, sizeof(unsigned char)*M*rows, MPI_UNSIGNED_CHAR, &boardRows); //matriz
	MPI_Type_commit(&boardRows);
	//s'agafa el tros de board a calcular
	for(x=0;x<rows;x++){
		for(y=0;y<M;y++){
			neighbors[x][y]= DEAD;
			myBoard->cell_state[x][y] = board->cell_state[startRow+x][y];
		}
	}	
	
	while (quit==false && (EndTime<0 || Iteration<EndTime)) 
	{

#ifndef NO_SDL 
		if (Graphical_Mode&&rank==0) 
		{	
		//Poll event and provide event type to switch statement
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				// For keydown events, test for keycode type. See Wiki SDL_Keycode.
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					if (board->game_state == RUNNING_STATE) {
						board->game_state = PAUSE_STATE;
						if(rank==0){printf("Game paused: editing enabled.\n");}
						break;
					}
					else if (board->game_state == PAUSE_STATE) {
						board->game_state = RUNNING_STATE;
						if(rank==0){printf("Game running.\n");}
						break;
					}
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					for (int i = 0; i < board->COL_NUM; i++) {
						for (int j = 0; j < board->ROW_NUM; j++)
							board->cell_state[i][j] = DEAD;
					}
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				click_on_cell(board,
							(e.button.y + PEEPER_OFFSET) / board->CELL_HEIGHT,
							(e.button.x + PEEPER_OFFSET) / board->CELL_WIDTH);
				if(rank==0){printf("%d, %d\n", e.button.x, e.button.y);}
				break;
			default: {}
			}
		}

		// Assignment to viewport
		peeper.x = -PEEPER_OFFSET;
		peeper.y = -PEEPER_OFFSET;
		peeper.w = PEEPER_SIZE;
		peeper.h = PEEPER_SIZE;
		if(rank==0){SDL_RenderSetViewport(renderer, &peeper);}

		// printf("Peeper OFFSET: (%d, %d).\n",-PEEPER_OFFSET, -PEEPER_OFFSET); fflush(stdout);	 
		// printf("Peeper position: (%d, %d).\n",peeper.x, peeper.y); fflush(stdout); 
		// printf("Peeper size: (%d, %d).\n",peeper.w, peeper.h); fflush(stdout);	 

		// Calculate upper left hand corner and then find domain of array used.
		const int origin_x = PEEPER_OFFSET / board->CELL_WIDTH;
		const int origin_y = PEEPER_OFFSET / board->CELL_HEIGHT;
		const int domain_x = D_COL_NUM - origin_x;
		const int domain_y = D_ROW_NUM - origin_y;
		
		// printf("Origin: (%d, %d).\n",origin_x, origin_y); fflush(stdout); 
		// printf("Domain: (%d, %d).\n",domain_x, domain_y); fflush(stdout); 

		// Use cell size to determine maximum possible window size without allowing
		// array overflow. This will be tested against SDL window size polls.
		// There be dragons here.
		const int maximum_width = domain_x * board->CELL_WIDTH;
		const int maximum_height = domain_y * board->CELL_HEIGHT;

	 
		// Get window measurements in real time.
		SDL_GetWindowSize(window, &window_width, &window_height);
		 
		// printf("Maximun window: (%d, %d).\n",maximum_width, maximum_height); fflush(stdout); 
		// printf("Window Size: (%d, %d).\n",window_width, window_height); fflush(stdout); 
		 
		// Don't allow overflow.
		if (window_width > maximum_width) {
			printf("WARNING: Attempting to exceed max window size in x (win width: %d - win max width: %d).\n",window_width, maximum_width);
			SDL_SetWindowSize(window, maximum_width, window_height);
		}
		if (window_height > maximum_height) {
			printf("WARNING: Attempting to exceed max window size in y (win height: %d - win max height: %d).\n", window_height, maximum_height);
			SDL_SetWindowSize(window, window_width, maximum_height);
		}

		// Draw
		if(rank==0){
			SDL_SetRenderDrawColor(renderer, 40, 40, 40, 1);
			SDL_RenderClear(renderer);
		}
	}
#endif
			
		//es comparteixen les files que falten per fer el calcul
		if (rank==0) { //FIRST NODE
			//send my last row -> upper for the next
			MPI_Send(&myBoard->cell_state[rows-1], M, boardRow, 1, 1, MPI_COMM_WORLD);
			//recieve my upper from previous
			MPI_Recv(&myBoard->upper, M, boardRow, size-1, 1, MPI_COMM_WORLD, &st);
			//send my first row -> under for the previous
			MPI_Send(&myBoard->cell_state[0], M, boardRow, size-1, 2, MPI_COMM_WORLD);
			//recieve my under from next
			MPI_Recv(&myBoard->under, M, boardRow, 1, 2, MPI_COMM_WORLD, &st);
		}else if(rank==size-1){ //LAST NODE
			//recieve my upper from previous
			MPI_Recv(&myBoard->upper, M, boardRow, size-2, 1, MPI_COMM_WORLD, &st);
			//send my last row -> upper for the next
			MPI_Send(&myBoard->cell_state[rows-1], M, boardRow, 0, 1, MPI_COMM_WORLD);
			//recieve my under from next
			MPI_Recv(&myBoard->upper, M, boardRow, 0, 2, MPI_COMM_WORLD, &st);
			//send my first row -> under for the previous
			MPI_Send(&myBoard->cell_state[0], M, boardRow, size-2, 2, MPI_COMM_WORLD);
		}else{ //INTERMEDIUM NODE
			//recieve my upper from previous
			MPI_Recv(&myBoard->upper, M, boardRow, rank-1, 1, MPI_COMM_WORLD, &st);
			//send my last row -> upper for the next
			MPI_Send(&myBoard->cell_state[rows-1], M, boardRow, rank+1, 1, MPI_COMM_WORLD);
			//recieve my under from next
			MPI_Recv(&myBoard->under, M, boardRow, rank+1, 2, MPI_COMM_WORLD, &st);
			//send my first row -> under for the previous
			MPI_Send(&myBoard->cell_state[rows-1], M, boardRow, rank-1, 2, MPI_COMM_WORLD);
		}

		//es realitza el calcul de la nova iteració
#ifdef NO_SDL 
		render_board(myBoard, neighbors, board);
#else
		render_board(renderer, myBoard, neighbors, board);
#endif
		//s'actualitzen els valors de la board per la següent iteració
		/*
		int sendcounts[size];
		int tmp=D_COL_NUM*rows;
		MPI_Allgather(&tmp, 1, MPI_INT, &sendcounts, size, MPI_INT, MPI_COMM_WORLD);
		
		int displ[size];
		for (int i=0;i<size;i++){
			displ[i]=i*D_COL_NUM*rows;
		}
		MPI_Allgather(&myBoard->cell_state, D_COL_NUM*rows, MPI_INT, &board->cell_state, D_COL_NUM*M, MPI_INT, MPI_COMM_WORLD);
		//MPI_Gatherv(&myBoard->cell_state, D_COL_NUM*rows, MPI_INT, board->cell_state, sendcounts, displ, MPI_INT, 0, MPI_COMM_WORLD);
		if(rank==1){
			printf("\ncalculated by rank 1:\n");
			for(x=0;x<rows;x++){
				for(y=0;y<M;y++){
					//board->cell_state[startRow][y] = myBoard->cell_state[x][y];
					printf("%i, ", myBoard->cell_state[x][y]);
				}
				printf("\n");
			}
		}
		printf("POSTGATHER\n");
		for(x=0;x<M;x++){
			for(y=0;y<M;y++){
				//board->cell_state[startRow][y] = myBoard->cell_state[x][y];
				if(rank==1)printf("%i, ", board->cell_state[x][y]);
			}
			if(rank==1)printf("\n");
		}	
		*/
		if (Graphical_Mode && rank==0) 
		{ 
#ifndef NO_SDL 
			SDL_RenderPresent(renderer);
#endif
			usleep(TICKS);
		}
		
		//Iteration++;
		if(rank==0){printf("[%05d] Life Game Simulation step.\r",++Iteration); fflush(stdout);}
		else{Iteration++;};
	}
	if(rank==0)printf("\nEnd Simulation.\n");
	printf("POSTSIMULATION\n");
	for(x=0;x<rows;x++){
		for(y=0;y<M;y++){
			//board->cell_state[startRow][y] = myBoard->cell_state[x][y];
			if(rank==0)printf("%i, ", myBoard->cell_state[x][y]);
		}
		if(rank==0)printf("\n");
	}	
	MPI_Barrier(MPI_COMM_WORLD);
	for(x=0;x<rows;x++){
		for(y=0;y<M;y++){
			//board->cell_state[startRow][y] = myBoard->cell_state[x][y];
			if(rank==1)printf("%i, ", myBoard->cell_state[x][y]);
		}
		if(rank==1)printf("\n");
	}	
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank==0){
		for (int a=0;a<rows;a++){
			for (int b = 0; b<M;b++){
				board->cell_state[a][b] = myBoard->cell_state[a][b];
			}
		}
		MPI_Status stat;
		for(int x=1; x<size;x++){
			int measure = rows;
			if(x+1==size){
				measure+=M%size;
			}
			unsigned char recvBuff[M];
			unsigned char recieved[measure][M];
			MPI_Request rq;
			for(int abc=0;abc<measure;abc++){
				MPI_Irecv(&recvBuff, measure, boardRow, x, x+1 , MPI_COMM_WORLD, &rq);
				MPI_Wait(&rq, &stat);
				for (int d=0;d<M;d++){
					recieved[abc][d] = recvBuff[d];
				}
			}
			
			int recvRank = stat.MPI_SOURCE;
			for (int y=0;y<measure;y++){
				for (int z = 0; z<M;z++){
					board->cell_state[recvRank*measure + y][z] = recieved[y][z];
				}
			}
		}
	}else{
		MPI_Request rq;
		MPI_Status stat;
		int measure = rows;
			if(x+1==size){
				measure+=M%size;
			}
		printf("BEFORE SENDING IT, I HAVE: ");
		for (int y=0;y<measure;y++){
			MPI_Isend(&myBoard->cell_state[y], 1, boardRow, 0, rank+1, MPI_COMM_WORLD, &rq);
			MPI_Wait(&rq, &stat);
			/*for (int z = 0; z<M;z++){
				printf("%i, ", myBoard->cell_state[y][z]);
			}
			printf("\n");*/
		}
		
	}
	
	
	
#ifndef NO_SDL 
	if (Graphical_Mode&&rank==0) 
	{ 
		// Clean up
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

#endif 

	// Save board
	// Hem de recolectar tots els resultats abans!
	if (SaveFile&&rank==0) {
	 	printf("Writting Board file %s.\n",output_file); fflush(stdout);	
	 	life_write(output_file, board);
	}
	free(board);
	free(myBoard);
	MPI_Finalize();
	return EXIT_SUCCESS;
}
