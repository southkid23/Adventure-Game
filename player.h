#include <iostream>
#include "Locations.h"
class Player {

private:
		Room* r;
		List* invItems;

public:
		Player(Room* lo);
		~Player(){}
		List* inventory(){return invItems;}
		void inventory(linkedList* items){invItems=items;}
		Room* currentR(){return r;}
		void currentR(Room* nw){r=nw;}
		void doAction(string verb, string noun);
};