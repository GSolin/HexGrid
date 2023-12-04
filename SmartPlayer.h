// Final
/* George Solinareos - 19563448 */

#ifndef SMARTPLAYER_H_
#define SMARTPLAYER_H_

#include <random>
#include <iostream>
#include <sstream>
#include <limits>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include "Cell.h"
#include "Board.h"

class SmartPlayer : public Player {
public:
	SmartPlayer(int t, string name = "Smart") :
		Player(t, name) {
	}
	bool getMove(Board*, int&, int&);
	//bool branchPoint(Board*, int, int, int, stack<Cell>, queue<Cell>&);
	//bool findConnection(Board*, int, int, int);
};

bool SmartPlayer::getMove(Board* board, int& x, int& y) {
	//Get the list of available moves
	vector<Cell> validCells = board->returnEmptyCells(validCells);
	// Create a priority queue which will put the highest scoring Cell first
	priority_queue<Cell> moves;

	// Create iterator index to go through all Cells in the vector
	for (Cell index : validCells) {
		int i = index.row;
		int j = index.col;
		Board tempBoard(*board);
		//If the move is valid:
		if (tempBoard.validInput(i, j)) {
			tempBoard.addMove(i, j);
			vector<Cell> neighbours;
			// Function which returns the score of the move
			Cell c(i, j, tempBoard.heuCheckNeighbours(board->getTurn(), i, j, neighbours));
			// Add it to the queue
			moves.push(c);
		}
	}

	// Using priority queue and an operator overloader for Cell, 
	// the move with the highest score will be played
	if (moves.size() > 0) {
		x = moves.top().row;
		y = moves.top().col;
	}

	cout << "Heuristic = " << moves.top().heuristic << " at ("
		<< (x + 1) << "," << (y + 1) << ")" << endl;

	return true;

	/* Below is old code to show the progression of how the current function came to be */

}



////////////////////////////////////

	/*steps = 10;
	random_shuffle(validCells.begin(), validCells.end());
	for (Cell index : validCells) {

		int i = index.getRow();
		int j = index.getCol();
		Board tempBoard(*board);
		tempBoard.addMoveSimulate(i, j);

		if (tempBoard.isBoardFull()) {
			if (tempBoard.checkWinningStatus(tempBoard.getTurn()) == tempBoard.getTurn()) {
				x = i;
				y = j;
				return;
			}
			else {
				continue;
			}
		}
		double minUtility = minMove(tempBoard);
		Cell c(i, j, minUtility);
		moves.push(c);
	}

	if (moves.size() > 0) {
		Cell next = moves.top();
		x = next.getRow();
		y = next.getCol();
		cout << moves.size() << " MiniMax Utility = " << next.getHeuristic()
			<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}

	return;*/

	/*
	Board* tempBoard = new Board(*board);
	stack<Cell> visited;
	queue<Cell> validMoves;
	bool startingBranch = false;
	int turn = board->getTurn();

	for (int i = 0; i < tempBoard->getBoardSize(); i++) {
		if (tempBoard->getGrid(i, 0) == turn) {
			startingBranch = branchPoint(tempBoard, i, 0, turn, visited, validMoves);
		}
	}

	if (!startingBranch) {
		board->listMove(x, y);
	}
	else {
		Cell next = validMoves.front();
		x = next.getRow();
		y = next.getCol();
	} */

//bool SmartPlayer::branchPoint(Board* temp, int x, int y, int pt, stack<Cell> visited, queue<Cell>& valid) {
//	for (int i = -1; i <= 1; i++) {
//		// Check cells above player
//		// Prac 4: Simulating moves, Best First
//		if (i == -1 && x > 0) {
//			if (temp->getGrid(x + i, y + 1) == pt) {
//				Cell occ(x + i, y + 1);
//				visited.push(occ);
//				return branchPoint(temp, x + i, y + 1, pt, visited, valid);
//			}
//			/*else if (temp->getGrid(x + i, y + 1) == 0) {
//				if (findConnection(temp, x + i, y + 1, pt)) {
//					Cell occ(x + i, y + 1);
//					visited.push(occ);
//					branchPoint(temp, x + i, y + 1, pt, visited);
//				}
//			}*/
//				
//		}
//		// Check cells beside player
//		else if (i == 0) {	
//			if (temp->getGrid(x + i, y + 1) == pt) {
//				Cell occ(x + i, y + 1);
//				visited.push(occ);
//				return branchPoint(temp, x + i, y + 1, pt, visited, valid);
//			}
//			/*else if (temp->getGrid(x + i, y + 1) == 0) {
//				if (findConnection(temp, x + i, y + 1, pt)) {
//					Cell occ(x + i, y + 1);
//					visited.push(occ);
//					branchPoint(temp, x + i, y + 1, pt, visited);
//				}
//			}*/
//
//		}
//		// Check cells below player
//		else if (i == 1 && x < temp->getBoardSize() - 1) {		
//			if (temp->getGrid(x + i, y) == pt) {
//				Cell occ(x + i, y);
//				visited.push(occ);
//				return branchPoint(temp, x + i, y, pt, visited, valid);
//			}
//			/*else if (temp->getGrid(x + i, y) == 0) {
//				if(findConnection(temp, x + i, y, pt)) {
//					Cell occ(x + i, y);
//					visited.push(occ);
//					branchPoint(temp, x + i, y, pt, visited);
//				}
//			}*/
//				
//		}
//	}
//
//	for (int i = 0; i <= 2; i++) {
//		// Check cells above player
//		if (i == 1 && x > 0) {
//			if (temp->getGrid(x - 1, y + 1) == 0) {
//				Cell occ(x - 1, y + 1);
//				valid.push(occ);
//				return true;
//			}
//		}
//		// Check cells beside player
//		if (i == 0) {
//			if (temp->getGrid(x, y + 1) == 0) {
//				Cell occ(x, y + 1);
//				valid.push(occ);
//				return true;
//			}
//		}
//		// Check cells below player
//		if (i == 2 && x < temp->getBoardSize() - 1) {
//			if (temp->getGrid(x + 1, y) == pt) {
//				Cell occ(x + 1, y);
//				valid.push(occ);
//				return true;
//			}
//		}
//	}
//}
//
//bool SmartPlayer::findConnection(Board* temp, int x, int y, int pt) {
//	for (int i = -1; i <= 1; i++) {
//		// Check cells above player
//		if (i == -1 && x > 0) {
//			if (temp->getGrid(x + i, y) == pt) {
//				temp->addMove(pt, x, y);
//				return true;
//			}
//			if (temp->getGrid(x + i, y + 1) == pt) {
//				temp->addMove(pt, x, y);
//				return true;
//			}
//		}
//		// Check cells beside player
//		else if (i == 0) {
//			if (temp->getGrid(x + i, y - 1) == pt && y >= 0) {
//				temp->addMove(pt, x, y);
//				return true;
//			}
//			if (temp->getGrid(x + i, y + 1) == pt) {
//				temp->addMove(pt, x, y);
//				return true;
//			}
//		}
//		// Check cells below player
//		else if (i == 1 && x < temp->getBoardSize() - 1) {
//			if (temp->getGrid(x + i, y - 1) == pt) {
//				temp->addMove(pt, x, y);
//				return true;
//			}
//			if (temp->getGrid(x + i, y) == pt) {
//				temp->addMove(pt, x, y);
//				return true;
//			}
//		}
//	}
//}
#endif /* SMARTPLAYER_H_ */
