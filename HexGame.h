// Final
/* George Solinareos - 19563448 */

#include <list>
#include <stack>
using namespace std;
#include "Cell.h"

#ifndef HEXGAME_H_
#define HEXGAME_H_

class HexGame {
private:
	Board *board;
	Player *player[2];
	stack<Cell> p1Moves;
	stack<Cell> p2Moves;
	list<Cell> validMoves;
	list<Cell>::iterator advc;
public:
	HexGame(Board *b, Player *p1, Player *p2) {
		board = b;
		player[0] = p1;
		player[1] = p2;
	}

	void play();
};

void HexGame::play() {
	int won = 0;
	bool full = false;
	board->printBoard();

	// Two factors that determine when a game is finished:
	//			1. If a wining move has been made; and
	//			2. If the board is full
	while (!won && !full) {

		int playerType = board->getTurn();
		int playerIndex = (playerType == player[0]->getType()) ? 0 : 1;
		int x = -1;
		int y = -1;

		if (!player[playerIndex]->getMove(board, x, y)) {
			cout << "No available move" << endl;
			return;
		}

		cout << player[playerIndex]->getPlayerName() << " plays " << " ("
				<< x + 1 << ", " << y + 1 << "):" << endl;

		if (!board->addMove(x, y))
			return;

		board->printBoard();
		won = board->checkWinningStatus(playerType);
		// Test if the board is full an no more moves can be made
		full = board->isBoardFull();
		if (won == playerType)
			cout << "--------------------------" << endl
				 << player[playerIndex]->getPlayerName() << " player wins!" << endl
				 << "--------------------------" << endl; 
		else if (full)
			cout << "--------------------------------" << endl
				 << "Maximum number of moves reached!" << endl
				 << "--------------------------------" << endl;	

	}
}

#endif /* HEXGAME_H_ */
