#include "classes.h"
#include <iostream>
#include <string>
using namespace std;

Room::Room(string n/*,int room,Item* listi[],int items,NPC* listn[],int NPC*/,string descr)
{
	//hasBeen = false;
	name = n;
	
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
		if(noun == "NORTH")
		{
			if (currentR()->getNorth() != NULL)
			{
				currentR(currentR()->getNorth());
				cout << "You moved North.\n" << endl << currentR()->getDescription() << endl << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
		else if(noun == "SOUTH")
		{
			if (currentR()->getSouth() != NULL)
			{
				currentR(currentR()->getSouth());
				cout << "You moved South.\n" << endl << currentR()->getDescription() << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
		else if(noun == "EAST")
		{
			if (currentR()->getEast() != NULL)
			{
				currentR(currentR()->getEast());
				cout << "You moved East.\n" << endl << currentR()->getDescription() << endl << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
		else
		{
			if (currentR()->getWest() != NULL)
			{
				currentR(currentR()->getWest()); 
				cout << "You moved West.\n" << endl << currentR()->getDescription() << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
	
	}
	else if (verb == "HELP")
	{
		cout << "You don't get any help. Help yourself."  << endl;
	}
	else
		cout << "Sorry but I don't understand." << endl;
}