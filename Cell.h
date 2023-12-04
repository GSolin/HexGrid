// Final
/* George Solinareos - 19563448 */

#ifndef CELL_H_
#define CELL_H_

struct Cell {
	int row, col;
	double heuristic;
	int index;
	// The 4 main variables, when heuristic isn't being utilised by 
	// a SmartPlayer or MonteCarlo player, it defaults to 0
	// Every Cell in the main board object, that is used for the game,
	//	is given an index using the formula: x * boardSize + y;
	Cell(int r, int c, double h = 0, int i = 0) {
		row = r;
		col = c;
		heuristic = h;
		index = (r*i)+c;
	}

	bool operator<(const Cell& c) const {
		return heuristic < c.heuristic;
	}

	bool operator==(const Cell& c) const {
		return (row == c.row) && (col == c.col);
	}

	double getHeuristic() {
		return heuristic;
	}
};

#endif
