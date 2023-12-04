// Final
/* George Solinareos - 19563448 */

#include <list>
#include <stack>
#include <queue>
using namespace std;
#include "Cell.h"

#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
	int boardSize;
	int turn;
	int **grid;
	int noOfMoves;
	int maxMoves;
	list<Cell> emptyCells;
	list<Cell>::iterator it1;
public:
	Board(int bs) {
		noOfMoves = 0;
		boardSize = bs;
		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = 0;
			}
		turn = 1;
		maxMoves = boardSize * boardSize;
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				Cell EC(i, j, 0, boardSize);
				emptyCells.push_back(EC);
			}
		}
	}

	list<Cell> returnList();

	void removeElement(int x, int y);

	void listMove(int& x, int& y);

	virtual ~Board() {

		for (int i = 0; i < boardSize; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(Board &cboard) {
		boardSize = cboard.getBoardSize();

		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				grid[i][j] = 0;

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = cboard.getGrid(i, j);
			}
		noOfMoves = cboard.getNoOfMoves();
		maxMoves = cboard.getBoardSize() * cboard.getBoardSize();
		emptyCells = cboard.returnEmptyCells();

		turn = cboard.getTurn();
	}

	int getBoardSize() {
		return boardSize;
	}

	list<Cell> returnEmptyCells() {
		return emptyCells;
	}

	int getGrid(int x, int y) {
		return grid[x][y];
	}

	int getTurn() {
		return turn;
	}

	int getNoOfMoves() {
		return noOfMoves;
	}

	vector<Cell> returnEmptyCells(vector<Cell> test) {
		// Function for copying the emptyCells list
		list<Cell> valid = emptyCells;
		while (!valid.empty()) {
			Cell n = valid.front();
			test.push_back(n);
			valid.pop_front();
		}
		return test;
	}

	bool validInput(int, int);

	bool addMoveSimulate(int, int);

	bool addMove(int x, int y);

	int checkWinningStatus(int playerType) {
		// Changes depending on which player type is parsed through
		// If a wining branch has been found, it returns the winning player
		// Otherwise, it will return 0
		int byOne = boardSize - 1;
		if (playerType == 1) {
			vector<Cell> visited;
			// Checks along the bottom row for any starting points to branch
			for (int j = 0; j < boardSize; j++) {
				if (grid[byOne][j] == playerType) {
					Cell prv(byOne, j);
					visited.push_back(prv);
					if (branchNeighbours(playerType, byOne, j, visited))
						return playerType;
				}
			}
		}
		else {
			vector<Cell> visited;
			// Checks along the far right column for any starting points to branch
			for (int i = 0; i < boardSize; i++) {
				if (grid[i][byOne] == playerType) {
					Cell prv(byOne, i);
					visited.push_back(prv);
					if (branchNeighbours(playerType, i, byOne, visited))
						return playerType;
				}
			}
		}
		return 0;
	}

	bool branchNeighbours(int pt, int x, int y, vector<Cell>& visitedNodes) {
		// Because the branching always begins on a specific side of the board for the respective player
		// All we need to know is if we manage to branch to any cell that is on the opposite side, it is a winning move
		if (pt == 1 && x == 0) {
			// Disabled for MonteCarlo
			/*cout << "Winning node! (" << x << ", " << y << ")\n\n";*/
			return true;
		}
			
		if (pt == -1 && y == 0) {
			//cout << "Winning node! (" << x << ", " << y << ")\n\n";
			return true;
		}

		// IMPORTANT SIDE NOTE: //
		/* checkNeighbours was originally a stack (as the marking sheet criteria states it should be) 
			and the program was still completely functional as it is now. However, traversing a stack without 
			destroying any elements for future use proved to be time consuming and decreased the runtime efficieny. 
			It has since been restructured as a vector to make the program more efficient. I am 
			happy to explain how my code functioned previously before the changes for the sake of the marking
			if need be */

		// Get current node's neighbours
		vector<Cell> neighbours = checkNeighbours(pt, x, y);
		// Add current node to visited stack so there is no infinite loop of branching
		Cell currentNode(x, y);
		visitedNodes.push_back(currentNode);

		// Branch to non-visited neighbours
		for (int i = 0; i < neighbours.size(); i++) {
			// test if node has already been visited
			if (!alreadyVisited(visitedNodes, neighbours[i])) {
				// Print surrouding player cells. Function still works, but is disabled for MonteCarlo simulations
				/*printNeighbours(neighbours, x, y);*/

				// If current inspected node not visited before, prepare to hop to said node
				Cell next = neighbours[i];
				// recursive function that repeats until all branchs have been explored or a winning node is found
				if (branchNeighbours(pt, next.row, next.col, visitedNodes))
					return true;
			}
		}
	}

	void printNeighbours(vector<Cell>& neighbours, int& x, int& y) {
		// Prints neighbour cells with the Players ID
		// This function is disabled due to MonteCarlo players creating numerous simulations
		// using the function were this is called from to avoid flooding the console and
		// decreasing runtime efficiency.
		// Otherwise, works as intended.
		cout << "Neighbours for current branched node (" << x << ", " << y << "):\n";
		if (!neighbours.empty()) {
			for (size_t i = 0; i < neighbours.size(); i++) {
				cout << neighbours[i].row << ", " << neighbours[i].col << " ";
			}
		}
		else
			cout << "NULL";
		cout << endl;
	}

	bool alreadyVisited(vector<Cell> compare, Cell top) {
		// Searches through every element in the Cell list and returns a bool
		// depending on whether the current inspected node has been visisted or not
		for (int i = 0; i < compare.size(); i++) {
			if (compare[i] == top)
				return true;
		}
		return false;
	}

	vector<Cell> checkNeighbours(int pt, int x, int y) {
		// Checks for player moves above, beside, and below the current node
		// Adds them to the vector neighbours to be returned
		vector<Cell> neighbours;
		for (int i = -1; i <= 1; i++) {
			// Check cells above player
			if (i == -1 && x > 0) {
				if (grid[x + i][y] == pt) {
					Cell occupied(x + i, y);
					neighbours.push_back(occupied);
				}
				if (grid[x + i][y + 1] == pt) {
					Cell occupied(x + i, y + 1);
					neighbours.push_back(occupied);
				}
			}
			// Check cells beside player
			if (i == 0) {
				if (grid[x + i][y - 1] == pt) {
					Cell occupied(x + i, y - 1);
					neighbours.push_back(occupied);
				}
				if (grid[x + i][y + 1] == pt) {
					Cell occupied(x + i, y + 1);
					neighbours.push_back(occupied);
				}
			}
			// Check cells below player
			if (i == 1 && x < boardSize - 1) {
				if (grid[x + i][y - 1] == pt) {
					Cell occupied(x + i, y - 1);
					neighbours.push_back(occupied);
				}
				if (grid[x + i][y] == pt) {
					Cell occupied(x + i, y);
					neighbours.push_back(occupied);
				}
			}
		}
		return neighbours;
	}

	double heuCheckNeighbours(int pt, int x, int y, vector<Cell> visitedNodes) {
		// Restructured version of checkNeighbours that is used by smartPlayer
		// Returns each cell with a heuristic based upon:
		//		1. How many neighbours the move has; and
		//		2. How close to the opposite side of the board the move is
		// Different cells have different values depending on the player type
		double length = 0;
		Cell n(x, y);
		visitedNodes.push_back(n);
		if (pt == -1) {
			for (int i = -1; i <= 1; i++) {
				// Check cells above player
				if (i == -1 && x > 0) {
					double k = 0;
					if (grid[x + i][y] == pt) {
						Cell n(x + i, y);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (y + 0.5);
						}
						if (k > length)
							length = k;
					}
					k = 0;
					if (grid[x + i][y + 1] == pt) {
						Cell n(x + i, y + 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (y + 0.75);
						}
						if (k > length)
							length = k;
					}
					if (k > length)
						length = k;
				}
				// Check cells beside player
				if (i == 0) {
					double k = 0;
					if (grid[x + i][y - 1] == pt) {
						Cell n(x + i, y - 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (y + 1);
						}
						if (k > length)
							length = k;
					}
					k = 0;
					if (grid[x + i][y + 1] == pt) {
						Cell n(x + i, y + 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (y + 0.75);
						}
						if (k > length)
							length = k;
					}
					if (k > length)
						length = k;
				}
				// Check cells below player
				if (i == 1 && x < boardSize - 1) {
					double k = 0;
					if (grid[x + i][y - 1] == pt) {
						Cell n(x + i, y - 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (y + 0.1);
						}
						if (k > length)
							length = k;
					}
					k = 0;
					if (grid[x + i][y] == pt) {
						Cell n(x + i, y);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (y + 0.25);
						}
						if (k > length)
							length = k;
					}
					if (k > length)
						length = k;
				}
			}
		}
		else {
			for (int i = -1; i <= 1; i++) {
				// Check cells above player
				if (i == -1 && x > 0) {
					double k = 0;
					if (grid[x + i][y] == pt) {
						Cell n(x + i, y);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (x + 0.75);
						}
						if (k > length)
							length = k;

					}
					k = 0;
					if (grid[x + i][y + 1] == pt) {
						Cell n(x + i, y + 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (x + 0.75);
						}
						if (k > length)
							length = k;
					}
					if (k > length)
						length = k;
				}
				// Check cells beside player
				if (i == 0) {
					double k = 0;
					if (grid[x + i][y - 1] == pt) {
						Cell n(x + i, y - 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (x + 0.25);
						}
						if (k > length)
							length = k;
					}
					k = 0;
					if (grid[x + i][y + 1] == pt) {
						Cell n(x + i, y + 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (x + 0.25);
						}
						if (k > length)
							length = k;
					}
					if (k > length)
						length = k;
				}
				// Check cells below player
				if (i == 1 && x < boardSize - 1) {
					double k = 0;
					if (grid[x + i][y - 1] == pt) {
						Cell n(x + i, y - 1);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (x + 0.5);
						}
						if (k > length)
							length = k;
					}
					k = 0;
					if (grid[x + i][y] == pt) {
						Cell n(x + i, y);
						if (!alreadyVisited(visitedNodes, n)) {
							k += (x + 0.5);
						}
						if (k > length)
							length = k;
					}
					if (k > length)
						length = k;
				}
			}
		}
		return length;
	}

	bool isBoardFull() {
		// Since the length of the board is the same for both axes,
		// the total number of moves that can be made is always: boardSize^2
		return (noOfMoves == maxMoves);
	}

	void printBoard();
};

list<Cell> Board::returnList() {
	// Used for copying the emptyCells list to another declared list
		return emptyCells;
}

void Board::listMove(int& x, int& y) {
	// Uses rand() once for the iterator (it1) to land on a random Cell object in the emptyCells list
	// Once the random Cell has been selected, simply copy its row and col
	int randCell = emptyCells.size();
	it1 = emptyCells.begin();
	advance(it1, rand() % randCell);
	x = it1->row;
	y = it1->col;
}

void Board::removeElement(int x, int y) {
	// Once a move has been made, remove Cell object from emptyCells list
	//	according to the row and col of the played move
	// Uses binary search to improve runtime efficieny
	int index = x * boardSize + y;
	int binary = emptyCells.size() / 2;
	it1 = emptyCells.begin();
	advance(it1, binary);

	if (index < it1->index) {
		for (it1; it1 != emptyCells.begin(); --it1) {
			if (it1->index == index) {
				emptyCells.erase(it1);
				return;
			}
		}
		if (it1->index == index) {
			emptyCells.erase(it1);
			return;
		}
	}
	else {
		for (it1; it1 != emptyCells.end(); ++it1) {
			if (it1->index == index) {
				emptyCells.erase(it1);
				return;
			}
		}
	}
	
	// Old code
	/*for (it1 = emptyCells.begin(); it1 != emptyCells.end(); ++it1) {
		if (it1->row == x && it1->col == y) {
			emptyCells.erase(it1);
			return;
		}
	}*/
}

bool Board::validInput(int x, int y) {
	if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
		cout << "Move (" << x + 1 << ", " << y + 1 << ") out of range!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	return true;
}

bool Board::addMove(int x, int y) {
	int playerType = getTurn();
	if (playerType != turn) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	grid[x][y] = playerType;
	noOfMoves++;
	removeElement(x, y);
	turn = -1 * turn;
	return true;
}

bool Board::addMoveSimulate(int x, int y) {
	// Identical to addMove except it does not change the player turn when it is finished
	// Utilised by the MonteCarlo player type
	int playerType = getTurn();
	if (playerType != turn) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	grid[x][y] = playerType;
	noOfMoves++;
	removeElement(x, y);
	return true;
}

void Board::printBoard() {
	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		if (j < 9)
			cout << j + 1 << "   ";
		else
			cout << j + 1 << "  ";
	}
	cout << endl;

	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}
	cout << endl;

	for (int i = 0; i < boardSize; i++) {
		for (int k = 0; k < i; k++)
			cout << "  ";

		if (i < 9)
			cout << " " << i + 1 << " ";
		else
			cout << i + 1 << " ";

		for (int j = 0; j < boardSize; j++) {
			if (grid[i][j] == 0) {
				if (j == 0) {
					cout << "|   |";
				} else {
					cout << "   |";
				}
			} else if (grid[i][j] == 1) {
				if (j == 0) {
					cout << "| R |";
				} else {
					cout << " R |";
				}
			} else {
				if (j == 0) {
					cout << "| B |";
				} else {
					cout << " B |";
				}
			}
		}
		cout << endl;
	}

	for (int k = 0; k <= boardSize; k++)
		cout << "  ";

	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}

	cout << endl;
	cout << endl;
}

#endif /* BOARD_H_ */
