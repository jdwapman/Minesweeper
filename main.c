//Jonathan Wapman
//No Partners
//This program runs a game of minesweeper. The user must pick tiles and either reveal their contents or choose them as mines.
//If the tile picked is a mine, the user loses the game. If the tile is not a mine, it either displays how many adjacent tiles are
//Mines, or reveals any adjacent tiles that do not have mines touching

#include <stdio.h>
#include "board.h"
#include "playGame.h"

int main(int argc, const char** argv) {
	mineBoard board; //Makes the minefield
	board.randSeed = 0; //Sets the seed to 0
	
	
	
	readArgs(argc, argv, &board); //Reads the command line arguements
	
	makeBoard(&board); //Makes the board
	
	scannedArray(&board); //Makes an array of whether the tile has been scanned
	
	mineArray(&board); //Makes an array to store the mines
	
	fillMines(argc, &board); //Fills the array with randomly-generated mines
	
	playGame(board); //Plays the game
	
	checkWin(board); //Checks to see if the game was won or lost
	
	freeMemory(&board);
	
    return 0; //Ends program
}
