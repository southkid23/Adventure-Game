
#include "Locations.h"
#include <iostream>
using namespace std;


class Player {

private:
		Room* r;
		//List* invItems;

public:
		Player(Room* lo){r=lo;}
		~Player(){}
		//List* inventory(){return invItems;}
		//void inventory(List* items){invItems=items;}
		Room* currentR(){return r;}
		void currentR(Room* nw){r=nw;}
		void doAction(string verb, string noun);
};


void Player::doAction(string verb, string noun)
{
	if(verb == "GO")
	{
		cout << verb << " ";
		if(noun == "NORTH")
		{
			cout << noun;
			r = currentR()->getDoors()[0];
			cout << "You moved North./n" << endl << currentR()->getDescription() << endl;
		}
		else if(noun == "SOUTH")
		{
			r = currentR()->getDoors()[2];
			cout << "You moved South./n" << endl << currentR()->getDescription() << endl;
		}
		else if(noun == "EAST")
		{	
			r = currentR()->getDoors()[1];
			cout << "You moved East./n" << endl << currentR()->getDescription() << endl;
		}
		else
		{
			r = currentR()->getDoors()[3];
			cout << "You moved West./n" << endl << currentR()->getDescription() << endl;
		}
	}
	else
		cout << "Sorry but I don't understand." << endl;
}
