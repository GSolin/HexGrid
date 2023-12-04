// Final
/* George Solinareos - 19563448 */

#include <list>
#include <stack>
#include "Cell.h"

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

using namespace std;

class HumanPlayer: public Player {
public:
	HumanPlayer(int t, string name = "Human") :
			Player(t, name) {
	}
	bool getMove(Board*, int&, int&);
};

bool HumanPlayer::getMove(Board *board, int &x, int &y) {
	// Asks the HumanPlayer for Row and Col input
	// Repeats until a valid move has been made
	bool flag = false;
	int bs = board->getBoardSize();

	while (!flag) {
		cout << "Input row and column (x, y) between 1 to " << bs << " for "
				<< name << " player:" << endl;
		int row, col;
		cin >> row >> col;
		x = row - 1;
		y = col - 1;
		flag = board->validInput(x, y);
	}

	return true;
}

#endif /* HUMANPLAYER_H_ */
