
class Player {

private:
		Location* l;
		linkedList* invItems;

public:
		Player(Location* lo);
		~Player(){}
		linkedList* inventory(){return invItems;}
		void inventory(linkedList* items){invItems=items;}
		Location* currentL(){return l;}
		void currentL(Location* nw){l=nw;}
		void doAction(string verb, string noun);
};