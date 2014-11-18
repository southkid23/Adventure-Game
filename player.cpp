#include <string>
using namespace std;

void Player::doAction(string verb, string noun)
{
	if(verb == "GO")
		if(noun == "NORTH")
			r = currentR()->doors[0];
			cout << "You moved North./n" << endl << currentR()->getDescription << endl;
		else if(noun == "SOUTH")
			r = currentR()->doors[2];
			cout << "You moved South./n" << endl <<currentR()->getDescription << endl;
		else if(noun == "EAST")
			r = currentR()->doors[1];
			cout << "You moved East./n" << endl << currentR()->getDescription << endl;
		else
			r = currentR()->doors[3];
			cout << "You moved West./n" << endl << currentR()->getDescription << endl;
}
