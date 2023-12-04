// Final
/* George Solinareos - 19563448 */

#include <list>
#include <stack>
#include "Cell.h"

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

using namespace std;

class RandomPlayer : public Player {
public:
	RandomPlayer(int t, string name = "Random") :
		Player(t, name) {
	}
	bool getMove(Board*, int&, int&);
};

bool RandomPlayer::getMove(Board* board, int& x, int& y) {
	// Goes into board class to access its emptyCells list and return a valid row/col input
	board->listMove(x, y);
	return true;
}

#endif /* RANDOMPLAYER_H_ */
