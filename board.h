//Jonathan Wapman
//Header file for board.c

#ifndef __Minesweeper__board__
#define __Minesweeper__board__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "playGame.h"
#include <time.h>

typedef struct board_struct{ //DO WE NEED A SEPARATE STRUCT FOR EACH TILE?
	
	int rows; //number of rows for minefield
	int cols; //Number of columns for minefield
	int numMines; //Number of mines on board
	int** isMine; //Stores whether the tile is a mine
	char** grid; //Stores the grid of characters
	int playRow; //Stores the currently played row
	int playCol; //Stores the currently played col
	int playOpt; //Stores which play option the user picks
	int randSeed; //Stores the random seed for the mines
	int minesLeft; //Stores the number of mines left to be found
	int** scanned; //Stores the state of whether the board has been scanned or not
	bool gameOver; //Stores whether the game is over or not
	bool win; //Stores whether the game has been won
	int foundMines; //Stores the number of mines the user has found
	bool shouldPrint; //Stores whether the move has been canceled
	
}mineBoard;


//Reads the command line arguements
void readArgs();

//Makes the grid of characters
void makeBoard();

//Makes the array of whether the tile has been scanned
void scannedArray();

//Prints the board in its current state
void printBoard();

//Fills an array with whether the corresponding grid tile is a mine
void mineArray();

//Fills the array with randomly-generated mines
void fillMines();

//Frees allocated memory
void freeMemory();

#endif
