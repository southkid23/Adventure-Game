#include "player.h"
#include <string>
using namespace std;

void Player::doAction(string verb, string noun)
{
	if(verb == "GO")
		if(noun == "NORTH")
			r = currentR()->doors[0];
			cout << "You moved North./n" << currentR()->description << endl;
		else if(noun == "SOUTH")
			r = currentR()->doors[2];
			cout << "You moved South./n" << currentR()->description << endl;
		else if(noun == "EAST")
			r = currentR()->doors[1];
			cout << "You moved East./n" << currentR()->description << endl;
		else
			r = currentR()->doors[3];
			cout << "You moved West./n" << currentR()->description << endl;
}