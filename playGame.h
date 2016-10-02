//
//  playGame.h
//  Minesweeper
//
//  Created by Jonathan Wapman on 3/10/15.
//  Copyright (c) 2015 Jonathan Wapman. All rights reserved.
//

#ifndef __Minesweeper__playGame__
#define __Minesweeper__playGame__

#include <stdio.h>
#include <stdbool.h>
#include "board.h"

//Handles the gameplay
void playGame();

//Checks to see if the board has any # tiles left on it
bool clearBoard();

//Asks the user to enter their input
void userPrompt();

//Reveals the tiles
void reveal();

//Ends the game
void gameOver();

//Make the current tile a ?
void question();

//Makes the current tile a !
void mark();

//Checks to see if the game is a win or a loss
void checkWin();

//Cancels the move
void cancel();

//Checks to see if the move is a valid move
bool isValidMove();


#endif /* defined(__Minesweeper__playGame__) */
