// Final
/* George Solinareos - 19563448 */

#include<iostream>
#include<string>
#include<time.h>
using namespace std;

#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"
#include "MonteCarloPlayer.h"
#include "HexGame.h"

int main() {
	srand(time(NULL));
	int boardSize = 5;
	cout <<"Input the size of board:" << endl;
    cin >> boardSize;
	if (boardSize < 3)
		boardSize = 3;

	// Create player pointers and initialise with a default so HexGame can function
	Player* p1 = new HumanPlayer(1, "Random (Red)");
	Player* p2 = new HumanPlayer(-1, "MonteCarlo (Blue)");

	Board *board = new Board(boardSize);
	int pt1 = 0; int pt2 = 0;

	// Choose Player 1
	cout << "Choose Player type for Red:\n"
		 << "---------------------------\n"
		 << "	1. Human			\n"
		 << "	2. Random			\n"
		 << "	3. Smart		    \n"
		 << "	4. MonteCarlo       \n"
		 << "---------------------------\n";
	
	while (pt1 < 1 || pt1 > 4) {
		cin >> pt1;
		if		(pt1 == 1) p1 = new HumanPlayer(1, "Human (Red)");
		else if (pt1 == 2) p1 = new RandomPlayer(1, "Random (Red)");	
		else if (pt1 == 3) p1 = new SmartPlayer(1, "Smart (Red)");	 
		else if (pt1 == 4) p1 = new MonteCarloPlayer(1, "MonteCarlo (Red)");
		else cout << "Invalid input\n";
	}

	cout << endl;

	// Choose player 2
	cout << "Choose Player type for Blue:\n"
		<< "---------------------------\n"
		<< "	1. Human			\n"
		<< "	2. Random			\n"
		<< "	3. Smart		    \n"
		<< "	4. MonteCarlo       \n"
		<< "---------------------------\n";
	
	while (pt2 < 1 || pt2 > 4) {
		cin >> pt2;
		if		(pt2 == 1) p2 = new HumanPlayer(-1, "Human (Blue)");
		else if (pt2 == 2) p2 = new RandomPlayer(-1, "Random (Blue)");
		else if (pt2 == 3) p2 = new SmartPlayer(-1, "Smart (Blue)");
		else if (pt2 == 4) p2 = new MonteCarloPlayer(-1, "MonteCarlo (Blue)");
		else cout << "Invalid input\n";
	}

	// Initiate the game
	HexGame game(board, p1, p2);
	game.play();

	delete board;
	delete p1;
	delete p2;

	return 0;
}

