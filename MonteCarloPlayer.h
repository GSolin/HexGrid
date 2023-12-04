// Final
/* George Solinareos - 19563448 */

#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_


#include <random>
#include <iostream>
#include <sstream>
#include <limits>
#include <list>
#include <stack>
#include <queue>
#include <iomanip>
using namespace std;
#include "Cell.h"
#include "Board.h"

class MonteCarloPlayer : public Player {
private:
public:
	MonteCarloPlayer(int t, string name = "MonteCarlo") :
		Player(t, name) {
	}

	bool getMove(Board* board, int& x, int& y) {
		priority_queue<Cell> moves;
		// Goes through every available Cell on the board to test there score
		for (int i = 0; i < board->getBoardSize(); i++) {
			for (int j = 0; j < board->getBoardSize(); j++) {
				if (board->getGrid(i, j) != 0) {
					cout << "  x   ";
					continue;
				}
				Board tempBoard(*board);
				int player = board->getTurn();
				tempBoard.addMoveSimulate(i, j);
				if (tempBoard.checkWinningStatus(player) == player) {
					cout << endl;
					x = i;
					y = j;
					return true;
				}

				double utility = simulation(tempBoard);

				Cell c(i, j, utility);
				moves.push(c);
				cout << setw(5) << c.heuristic << " ";
			}
			cout << endl;
		}

		// Using priority queue and an operator overloader for Cell, 
		// the move with the highest score will be played
		if (!moves.empty()) {
			x = moves.top().row;
			y = moves.top().col;
		}

		return true;
	}

	double simulation(Board board) {
		// Simulate player and enemy move 50 times
		// The higher the steps, the more accurate we can
		// narrow down the move with the best score
		int times = 50;
		double winning = 0.0;
		int player = board.getTurn();
		for (int i = 0; i < times; i++) {
			Board tempBoard(board);
			player *= -1;
			winning += expansion(player, tempBoard);
		}
		// Return the score of the Cell played in the simulated move
		return (winning / (double)times);
	}

	double expansion(int player, Board board) {
		if (board.checkWinningStatus(player) == player) {
			return 1.0;
		}
		else if (board.isBoardFull()) { //draw game
			return 0.5;
		}
		else if (board.checkWinningStatus(player) != 0) { //No player is winning; continue.
			return 0.0;
		}

		//If no winning move is found, add a rand() move 
		int x, y;
		board.listMove(x, y);
		board.addMove(x, y);

		player = board.getTurn();
		// and branch recursively to expansion again
		return expansion(player, board);
	}
};

#endif
