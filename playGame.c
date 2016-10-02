//Jonathan Wapman
//This c file handles functions related to the gameplay

#include "playGame.h"
#include "board.h"


//Runs the game's gameplay and UI
void playGame(mineBoard board){
	
	board.minesLeft = board.numMines; //The number of mines left on the board is the number of mines. None have been revealed
	board.foundMines = 0;
	
	
	board.playOpt = 0;
	
	//loops until won
	do{
	
		if(board.playOpt >=0 && board.playOpt <= 2){
			printf("There are %d mines left\n", board.minesLeft);
			printBoard(board); //Prints the board
			
			printf("\n"); //Prints a newline
		}
	
		//Loops until it recieves a valid input
		
		printf("Enter row a row between 0-%d and a column between 0-%d: ", (board.rows) - 1, (board.cols) - 1);
			
			
		scanf("%d %d", &board.playRow, &board.playCol);
		
		while(isValidMove(&board) == false){
			printf("Enter row a row between 0-%d and a column between 0-%d: ", (board.rows) - 1, (board.cols) - 1);
			
			
			scanf("%d %d", &board.playRow, &board.playCol);
		}
			
		
		
		printf("Enter Action\n");
		
		if(board.grid[board.rows - board.playRow - 1][board.playCol] == '#'){ //If the picked tile is #
			printf("0. Reveal\n1. Question\n2. Mark\n3. Cancel\n");
		}
		
		if(board.grid[board.rows - board.playRow - 1][board.playCol] == '?'){ //If the picked tile is ?
			printf("0. UnQuestion\n1. Cancel\n");
		}
		
		if(board.grid[board.rows - board.playRow - 1][board.playCol] == '!'){ //If the picked tile is !
			printf("0. UnMark\n1. Cancel\n");
		}
		
		
		printf("Action: ");
		
		
		
		scanf("%d", &board.playOpt); //Scans the user's action
		
		
	
	//If the selected tile is a #
	if(board.grid[board.rows - board.playRow - 1][board.playCol] == '#'){ //If the current tile has not been modified
		switch(board.playOpt){
			case 0:
				reveal(&board, 0, 0); //Reveals the adjacent tiles
				break;
			case 1:
				board.grid[board.rows - board.playRow - 1][board.playCol] = '?'; //Makes the tile a ?
				break;
			case 2:
				board.grid[board.rows - board.playRow - 1][board.playCol] = '!'; //Makes the tile a !
				board.minesLeft--; //Decrements the number of mines the user has left to find
				
				if(board.isMine[board.rows - board.playRow - 1][board.playCol] == 0){ //Cancels the move and asks again
					board.foundMines++; //If the ! tile is actually a mine, increment the number of foundMines
				}
				
				
				if(board.minesLeft == 0){ //If there are 0 mines left to find
					if(board.foundMines == board.numMines){ //If all the mines have been found
						if(clearBoard(&board) == true){ //If the board is clear of all #
							gameOver(&board); //The game is over
							board.gameOver = true;
							board.win = true; //The game has been won
							return;
						}
					}
				}
			

				
				//printf("There are %d mines left\n", board.minesLeft);
				//printf("Found Mines: %d\n", board.foundMines); //REMOVE
				//printf("Mines Left: %d\n", board.minesLeft); //REMOVE
				break;
			case 3:
				break; //Cancels the move and asks again
			
		}
	}
	
	//If the selected tile is a ?
	else if(board.grid[board.rows - board.playRow - 1][board.playCol] == '?'){ //If the current tile has been questioned
		switch(board.playOpt){
			case 0:
				board.grid[board.rows - board.playRow - 1][board.playCol] = '#'; //unquestions tile
				break;
			case 1:
				board.playOpt = -1;
				break; //cancels move and asks again
		}
	}
	
		//If the selected tile is a !
	else if(board.grid[board.rows - board.playRow - 1][board.playCol] == '!'){ //If the current tile has been marked
		switch(board.playOpt){
			case 0:
				board.grid[board.rows - board.playRow - 1][board.playCol] = '#';
				
				if(board.isMine[board.rows - board.playRow - 1][board.playCol] == 0){ //If unmarking and the tile is a mine, decrement the number of found mines
					
					board.foundMines--;
				}
				board.minesLeft++; //Incremenet the numver of mines left to find
				//printf("Found Mines: %d\n", board.foundMines);
				//printf("Mines Left: %d\n", board.minesLeft);
				
				break;
			case 1:
				board.playOpt = -1;
				break; //Cancels
		}
	}

		if(board.minesLeft == 0){ //If there are 0 mines left to find
			if(board.foundMines == board.numMines){ //If all the mines have been found
				if(clearBoard(&board) == true){ //If the board is clear of all #
					gameOver(&board); //The game is over
					board.gameOver = true;
					board.win = true; //The game has been won
					return;
				}
			}
		}
	
	}while(board.gameOver == false);
	
	gameOver(&board); //Ends game
	
	return;
	
	
}

//This function checks to see if the entire board is clear of #
bool clearBoard(mineBoard* board){
	int i = 0;
	int j = 0;//Counter variavles
	
	for(i = 0; i < board->rows; ++i){
		for(j = 0; j < board->cols; ++j){
			if(board->grid[i][j] == '#' || board->grid[i][j] == '?'){ //If any of the tiles are # or ?, the board is not clear and the game is not over
				return false;
			}
		}
	}
	
	return true;
}

//This function ends the game and determines the winner
void gameOver(mineBoard* board){
	int i;
	int j;//Counter variables
	
	for(i = 0; i < board->rows; ++i){
		for(j = 0; j < board->cols; ++j){
			board->scanned[i][j] = 1; //Makes the current tile unscanned
		}
	}
	
	
	//Reveal entire board once won
	for(i = 0; i < board->rows; ++i){
		for(j = 0; j < board->cols; ++j){
			board->playCol = j;
			board->playRow = i;
			reveal(board, 0, 0); //Reveals the entire board
			
			
		}
	}

	
	
	
	
	//Changes ! to *
	for(i = 0; i < board->rows; ++i){
		for(j = 0; j < board->cols; ++j){
			if(board->grid[i][j] == '!'){
				board->grid[i][j] = '*';
			}
		}
	}
	
	//Prints the board
	printBoard(*board);
	
	
	
	if(board->minesLeft == 0){ //If there are 0 mines left to be found
		if(board->foundMines == board->numMines){ //If the number of mines found is the number of mines on the board, the game has been won

			board->gameOver = true; //The game is over
			board->win = true; //The game has been won
			
		}
	}
	
	if(board->win == true){
		printf("\nYou Won!!"); //If the game has been won
	}
	else{
		printf("\nYou Lost :("); //If the game was lost
	}
	
	return;
}

//This function checks to see if the the game has been won
void checkWin(mineBoard board){
	if(board.minesLeft == 0 && board.gameOver == true){ //If the number of mines leftt is 0 and the game is over
		board.win = true; //The game has been won
	}
	
	return;
}


/* 
 This function reveals the adjacent tiles. There is a ton of code there because the corners and edges are all special cases. Each case requires different areas to scan to avoid segmentation error. For example, tiles in the leftmost row cannot scan the tile to their left because there is no tile there, so they have a special case that tells them not to scan there.
 */
void reveal(mineBoard* board, int i, int j){
	
	int foundMines = 0; //Variable to store the number of mines found
	char foundMinesChar = '0'; //Variable to print number of mines found THIS WORKS
	
	
	//If the current piece is not an edge piece.
	
	if(board->playCol + j > 0 &&
	   board->playCol + j < board->cols - 1 &&
	   board->rows - board->playRow - 1 - i > 0 &&
	   board->rows - board->playRow - 1 - i < board->rows - 1 //Checks to see if it is not an edge piece
	   ){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			
			
		
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0; //Sets the tile to scanned
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false; //If a mine is picked, the game is over and has been lost
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine, scans the adjacent tiles
				
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol - 1 + j] == 0){ //1 below
					foundMines++; //Increments the number of found mines
				}
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol - 1 + j] == 0){ //Center
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol - 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){ //Recursively scans the adjacent tiles
					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				
				
				
			}
			
		}
		else{
			return;
		}
	}
	
	
	//If on left edge
	if(board->playCol + j == 0 && //If col is 0
	   board->rows - board->playRow - 1 - i > 0 && //Not top corner
	   board->rows - board->playRow - 1 - i < board->rows - 1 //Not bottom corner
	   ){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine
				
				
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + j] == 0){ //1 below
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + 1 + j] == 0){ //1 below
					foundMines++;
				}
				
				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){
					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				
				
				
			}
			
			
			
			
			
		}
		else{
			return;
		}
		
	}
	
	
	//If on right edge
	if(board->playCol + j == board->cols - 1 && //If col is the last column
	   board->rows - board->playRow - 1 - i > 0 && //Not top corner
	   board->rows - board->playRow - 1 - i < board->rows - 1){ //Not bottom corner
		
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine
				
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol - 1 + j] == 0){ //1 below
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol - 1 + j] == 0){ //Center
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol - 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){

					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				
				
				
			}
			
		}
		else{
			return;
		}
		
	}
	
	
	
	//If on top row
	if(board->playCol + j > 0 &&
	   board->playCol + j < board->cols - 1 &&
	   board->rows - board->playRow - 1 - i == 0 //Bottom row
	   ){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine
				
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol - 1 + j] == 0){ //1 below
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol - 1 + j] == 0){ //Center
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}

				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){
					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				
			}
			
		}
		else{
			return;
		}
		
	}
	
	
	//If on bottom row
	if(board->playCol + j > 0 &&
	   board->playCol + j < board->cols - 1 &&
	   board->rows - board->playRow - 1 - i == board->rows - 1 //Bottom row
	   ){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine
				

				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol - 1 + j] == 0){ //Center
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol - 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){

					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				
				
			}
			

		}
		else{
			return;
		}
		
	}
	
	
	//If top left corner
	if(board->playCol + j == 0 &&
	   
	   

	   board->rows - board->playRow - 1 - i == 0
	   ){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine

				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}

				if(board->rows != 1){
					
					if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + 1 + j] == 0){
						foundMines++;
					}
					if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + j] == 0){
						foundMines++;
					}

				}

				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){
					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);

				}
				
			}
			
		}
		else{
			return;
		}
		
	}
	
	
	
	//If top right corner
	if(board->playCol + j == board->cols - 1 &&
	   board->rows - board->playRow - 1 - i == 0
	   ){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine
				
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol - 1 + j] == 0){ //1 below
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 + 1 - i][board->playCol + j] == 0){
					foundMines++;
				}

				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol - 1 + j] == 0){ //Center
					foundMines++;
				}


				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){
					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				
				
			}
			
		}
		else{
			return;
		}
		
	}
	
	//If bottom left corner
	if(board->playCol + j == 0 &&
	   board->rows - board->playRow - 1 - i == board->rows - 1
	   ){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine
				


				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + 1 + j] == 0){
					foundMines++;
				}
				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){
					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				
			}
			
		}
		else{
			return;
		}
		
	}
	
	//If bottom right corner
	if (board->playCol + j == board->cols - 1 &&
		board->rows - board->playRow - 1 - i == board->rows - 1
		){
		
		//If ! or ?
		
		if(board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '!' || board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] == '?'){
			return;
		}
		//If not yet scanned
		if(board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] == 1){ //If scanned = false
			
			board->scanned[board->rows - board->playRow - 1 - i][board->playCol + j] = 0;
			//If the selected tile is a mine, exit function
			if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol + j] == 0){ //If the tile is a mine
				board->gameOver = true;
				board->win = false;
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = '*'; //Changes the tile to a mine
				return; //Exit function
			}
			
			else{ //If the selected tile is not a mine
				

				if(board->isMine[board->rows - board->playRow - 1 - i][board->playCol - 1 + j] == 0){ //Center
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol - 1 + j] == 0){
					foundMines++;
				}
				if(board->isMine[board->rows - board->playRow - 1 - 1 - i][board->playCol + j] == 0){
					foundMines++;
				}
				
				//Sets the current tile to have the number of adjacent mines. THIS WORKS
				if(foundMines > 0) {
					foundMinesChar = (char)(((int)'0')+foundMines);
					
				}
				else{
					foundMinesChar = '0';
				}
				
				board->grid[board->rows - board->playRow - 1 - i][board->playCol + j] = foundMinesChar;
				//board->scanned[board->rows - board->playRow - 1 - i][board->playCol - j] = 0; //Sets scanned to true
				
				if(foundMines == 0){
					reveal(board, i + 1, j + 1);
					reveal(board, i + 1, j);
					reveal(board, i + 1, j - 1);
					reveal(board, i, j + 1);
					reveal(board, i, j - 1);
					reveal(board, i - 1, j + 1);
					reveal(board, i - 1, j);
					reveal(board, i - 1, j - 1);
				}
				

			}
			
		}
		else{
			return;
		}
		
	}
	

	return;
}

//This function checks to see if the current move is a valid move
bool isValidMove(mineBoard* board){
	
	
	if(board->playCol < 0 || board->playCol > board->cols - 1){ //If outside the column bounds, it is not a valid move
		return false;
	}
	
	if(board->playRow < 0 || board->playRow > board->rows - 1){ //If it is outside the row bounds, it is not a valid move
		return false;
	}
	
	if(board->grid[board->rows - board->playRow - 1][board->playCol] != '!' && //If the tile is not ! # or ? it has already been revealed
	   board->grid[board->rows - board->playRow - 1][board->playCol] != '#' &&
	   board->grid[board->rows - board->playRow - 1][board->playCol] != '?'
	   ){
		printf("This tile is already revealed.\n");
		return false;
	}
	
	
	
	return true; //If if gets past all those conditions, it is a valid move
	
}




