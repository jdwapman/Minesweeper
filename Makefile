mine_sweeper.out: main.o playGame.o board.o
	gcc -g -Wall -o mine_sweeper.out main.o playGame.o board.o

main.o: main.c playGame.h board.h
	gcc -g -Wall -c main.c

playGame.o: playGame.c playGame.h
	gcc -g -Wall -c playGame.c

board.o: board.c board.h
	gcc -g -Wall -c board.c