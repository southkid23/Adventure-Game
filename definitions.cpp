#include "classes.h"
#include <iostream>
#include <string>
using namespace std;

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

void Player::doAction(string verb, string noun)
{
	if(verb == "GO")
	{
		cout << verb << " ";
		if(noun == "NORTH")
		{
			cout << noun;
			r = r->getDoors()[0];
			cout << "You moved North.\n" << endl;
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