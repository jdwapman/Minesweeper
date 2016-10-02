//Jonathan Wapman
//This C file stores functions that handle the structure of the board

#include "board.h"
#include <stdlib.h>
#include <time.h>

//This function checks to see if the user entered the correct amount of command line arguements and gets the number of rows, cols, mines, and an optional random seed
void readArgs(int argc, char* argv[], mineBoard* board){
	
	//If the user passes too few arguements
	if(argc < 4){
		printf("Not enough arguments. Usage:\n");
		printf("./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0); //Exits program
	}
	
	
	//If the user passes too many arguements
	if(argc > 5){
		printf("Too many arguments. Usage:\n");
		printf("./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0); //Exits program
	}
	//If the user passes 4 arguements, not including a random seed
	if(argc == 4){
		board->rows = atoi((argv[1]));
		board->cols = atoi((argv)[2]);  //Stores the command line args into the row, column, and piece variables
		board->numMines = atoi((argv)[3]);
        board->minesLeft = board->numMines; //The number of mines left is the number of mines on the board
	}
	//If the user passes 5 arguements, including a random seed
	if(argc == 5){
		board->rows = atoi((argv[1]));
		board->cols = atoi((argv)[2]);  //Stores the command line args into the row, column, and piece variables
		board->numMines = atoi((argv)[3]);
		board->randSeed = atoi((argv)[4]); //Sets the random seed to the 4th arguement
		board->minesLeft = board->numMines; //The number of mines left is the number of mines on the board
		
	}
	
	return; //Exits function
	
}

//This function dynamically allocates an array for the board and fills it with *
void makeBoard(mineBoard* board){
	int i = 0; //Counter variable for 1st loop
	int j = 0; //Counter variable for 2nd loop
	
	board->grid = malloc(board->rows * sizeof(char *)); //Makes 1D array
	
	for(i = 0; i < board->rows; i++)
	{
		board->grid[i] = malloc(board->cols * sizeof(char)); //Makes 2D array
	}
	
	
	//Loop fills 2D matrix with '*'
	for(i = 0; i < board->rows; ++i){ //Loops through rows
		for(j = 0; j < board->cols; ++j){ //Initializes matrix with astericks, loops through columns
			board->grid[i][j] = '#';		//Makes current location be *
		}
	}
	
	return;
}

//This function prints the board
void printBoard(mineBoard board){
	int i = 0; //Counter variable for 1st loop
	int j = 0; //Counter variable for 2nd loop
	
	
	//Loop prints board
	for(i = 0; i < board.rows ; ++i){
		
		printf("%d ", board.rows - 1 - i); //Prints row indexes
		
		for(j = 0; j < board.cols; ++j){
			
			printf("%c", board.grid[i][j]); //Prints the board
			
			if(j < board.cols - 1){
				printf(" "); //Prints a space if it is not the last column
			}
		}
		if(i < board.rows){
			printf("\n"); //Prints a newline after every row
		}
	}
	
	
	//Prints bottom row index
	printf("  "); //Prints left buffer space
	for(j = 0; j < board.cols; ++j){
		printf("%d ", j); //Prints numbers
	}
	
	return;
	
}

//This function dynamically allocates an array for the board and fills it with wether the tile is a mine
void mineArray(mineBoard* board){
	int i = 0; //Counter variable for 1st loop
	int j = 0; //Counter variable for 2nd loop
	
	board->isMine = malloc(board->rows * sizeof(int *)); //Makes 1D array
	
	for(i = 0; i < board->rows; i++)
	{
		board->isMine[i] = malloc(board->cols * sizeof(int)); //Makes 2D array
	}
	
	
	//Loop fills 2D matrix with false
	for(i = 0; i < board->rows; ++i){ //Loops through rows
		for(j = 0; j < board->cols; ++j){ //Initializes matrix with astericks, loops through columns
			board->isMine[i][j] = 1;		//Makes current location be false
		}
	}
	
	return;
}

//This function makes a 2D array within the struct to store whether the tile has been scanned or not
void scannedArray(mineBoard* board){
	int i = 0; //Counter variable for 1st loop
	int j = 0; //Counter variable for 2nd loop
	
	board->scanned = malloc(board->rows * sizeof(int *)); //Makes 1D array
	
	for(i = 0; i < board->rows; i++)
	{
		board->scanned[i] = malloc(board->cols * sizeof(int)); //Makes 2D array
	}
	
	
	//Loop fills 2D matrix with false
	for(i = 0; i < board->rows; ++i){ //Loops through rows
		for(j = 0; j < board->cols; ++j){ //Initializes matrix with astericks, loops through columns
			board->scanned[i][j] = 1;		//Makes current scan be false
		}
	}
	
	return;
}

//This function fills the mine array with randomly generated mines
void fillMines(int argc, mineBoard* board){
	int i = 0; //Loop counter
	bool validRand = false; //Checks whether the move is valid
	int randRow = 0;
	int randCol = 0;
	//int numTiles = 0;
	
	if(argc == 4){ //if there is no random seed give, use the system time
		srand((int)time(0));
	}
	
	else{
		srand(board->randSeed); //If there is a seed given, use that seed
	}
	
	
	for (i = 0; i < board->numMines; ++i){
		while(validRand == false){ //While you are not allowed to place a mine there
			randRow = rand() % (board->rows);
			randCol = rand() % board->cols;
			
			if(board->isMine[board->rows - randRow - 1][randCol] == 1){ //1 is false and 0 is true
				validRand = true; //If there is not already a mine there
				board->isMine[board->rows - randRow - 1][randCol] = 0;
				//printf("Placing mine at %d, %d\n", randRow, randCol); //Uncomment this line for debugging
			}
			else{
				validRand = false;
			}
		}
		validRand = false;
	}

	
	return;
}

void freeMemory(mineBoard* board){
	int i = 0;
	
	for(i = 0; i < board->rows; ++i){
		free(board->grid[i]);
		free(board->isMine[i]);
		free(board->scanned[i]);
	}
	
	
	
	return;
}

