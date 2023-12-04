// Final
/* George Solinareos - 19563448 */

#include <list>
#include <stack>
#include "Cell.h"

#ifndef PLAYER_H_
#define PLAYER_H_
class Player {
protected:
	int type;
	string name;
public:
	// Parent class for all Player types
	Player(int t, string i) :
			type(t), name(i) {
	}

	string getPlayerName() {
		return name;
	}

	int getType() {
		return type;
	}

	virtual bool getMove(Board *board, int &x, int &y) = 0;

	virtual ~Player() {
	}
};

#endif /* PLAYER_H_ */
