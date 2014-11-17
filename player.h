#include <iostream>
class Player {

private:
		Room* r;
		linkedList* invItems;

public:
		Player(Room* lo);
		~Player(){}
		linkedList* inventory(){return invItems;}
		void inventory(linkedList* items){invItems=items;}
		Room* currentR(){return room;}
		void currentR(Room* nw){r=nw;}
		void doAction(string verb, string noun);
};