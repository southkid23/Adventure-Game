
#include <iostream>
#include <string>
using namespace std;


class Room
{
private:
	Room** doors;//int nDoors;//rooms adjoining with current
	string name,inHouse,description;//description & name of building
	//Item** listItems;int nItems;//list of uncollected/unusable items
	//NPC** listNPC;int nNPC;//list of live/unkillable NPC in room
	//bool hasBeen;
public:
	Room(string n,Room** listr/*,int room,Item* listi[],int items,NPC* listn[],int NPC*/,string descr);//Room constructor. Should Create room
	//ostream& roomitems(ostream&);//List of items contained in room Eg. Furniture
	//ostream& roomNPC(ostream&);//List of non-playable characters in room
	//bool entered();//Check if room has been discovered
	//virtual void enter();//When player enters the room
	string getDescription(){return description;}
	Room* getDoors(int i){return doors[i];}

};

Room::Room(string n,Room** listr/*,int room,Item* listi[],int items,NPC* listn[],int NPC*/,string descr)
{
	//hasBeen = false;
	name = n;
	doors = listr;
	/*nDoors = room;
	listItems = listi;
	nItems = items;
	listNPC = listn;
	nNPC = NPC;*/
	description = descr;
}

/*ostream& Room::roomitems(ostream& out)
{
	out << "Items in the room:";
	for(int i = 0;i < nItems;i++)
	{
		listItems[i]->render(out);out<<"";
		out << "(" << i << ")" << endl;
	}
}

ostream& Room::roomNPC(ostream& out)
{
	out << "People in the room:";
	for(int i = 0;i < nItems;i++)
	{
		listNPC[i]->render(out);out<<"";
		out << "(" << i << ")" << endl;
	}
}

bool Room::entered()
{
	return hasBeen;
}

void Room::enter()
{
	if(!entered)
	{
		cout << "You are in " << name << ". " << description << endl << roomNPC(cout) << roomitems(cout);
		hasBeen = true;
	}
	else
		cout << "You are back in " << name << "." << endl << roomNPC(cout) << roomitems(cout);
}
*/

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
		if(noun == "NORTH")
		{
			r = r->getDoors(0);
			cout << "You moved North.\n" << endl << r->getDescription() << endl;
		}
		else if(noun == "SOUTH")
		{
			r = currentR()->getDoors(1);
			cout << "You moved South.\n" << endl << currentR()->getDescription() << endl;
		}
		else if(noun == "EAST")
		{
			r = currentR()->getDoors(2);
			cout << "You moved East.\n" << endl << currentR()->getDescription() << endl;
		}
		else
		{
			r = currentR()->getDoors(3);
			cout << "You moved West.\n" << endl << currentR()->getDescription() << endl;
		}
	}
	else
		cout << "Sorry but I don't understand." << endl;
}
